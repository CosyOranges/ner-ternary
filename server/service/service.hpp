#pragma once
#include <algorithm>
#include <cctype>
#include <chrono>
#include <thread>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <SearchTree/searchtree.grpc.pb.h>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <grpc++/grpc++.h>
#include <lib/processor.hpp>
#include <nlohmann/json.hpp>

using std::chrono::system_clock;

class SearchTreeServiceImpl final : public searchtree::SearchTree::Service {
public:
    void Initialize() {
        BOOST_LOG_TRIVIAL(info) << "Building out the Search Tree";

        std::string home = std::getenv("HOME");
        home = home + "/treesearcher/data/default/diseases.tsv";

        if (!std::filesystem::exists(home)) {
            BOOST_LOG_TRIVIAL(warning) << home << " not found. The default Search Tree will be empty, please supply new terms to populate it.";
        } else {
            std::vector<std::string> terms = CleanTsv(home, 3);
            searchTree.BuildFromVec(terms);
        }
    }

    grpc::Status ReplaceTree(grpc::ServerContext* context, const searchtree::TempTreeRequest* request,
                                searchtree::TempTreeResponse* response) override {
        // Register Request
        boost::uuids::uuid tmp_uuid = uuid_generator();
        const std::string tree_uuid = boost::uuids::to_string(tmp_uuid);

        std::vector<std::string> terms = StringToVec(request->tree_terms());

        response->set_tree_id(tree_uuid);

        BOOST_LOG_TRIVIAL(info) << "Creating Temporary Tree with id: " << tree_uuid;

        usersTree.BuildFromVec(terms);

        if (usersTree.size_bytes() < 52428800) {
            AddTreeToForest(tree_uuid, terms);
            BOOST_LOG_TRIVIAL(info) << "Added tree[" << tree_uuid << "] of size [" << usersTree.size_bytes() << "] to Forest";
            response->set_success(true);
            return grpc::Status::OK;
        } else {
            response->set_success(false);
            return grpc::Status::CANCELLED;
        }
    }

    /*
        User can add new terms to the ROOT_TREE.
    */
    grpc::Status InsertToTree(grpc::ServerContext* context, const searchtree::InsertTreeRequest* request,
                                searchtree::InsertTreeResponse* response) override {
        // Register Request
        std::string temp = request->tree_terms();

        std::vector<std::string> terms = StringToVec(request->tree_terms());

        BOOST_LOG_TRIVIAL(info) << "Inserting " << terms.size() << " new terms into the Search Tree";

        // Perform the insertion into the permanent tree
        searchTree.InsertVec(terms);

        response->set_ready("READY");
        return grpc::Status::OK;
    }

    /*
        User can supply a Document as string and specify which tree to use (through it's uuid) to annotate
        the document.

        If no uuid is given the ROOT_TREE will be used as default.
    */
    grpc::Status Annotate(grpc::ServerContext* context, const searchtree::AnnotateRequest* request,
                            searchtree::AnnotateResponse* response) override {
        // Register Request
        // BOOST_LOG_TRIVIAL(info) << "Received Document with ID: " << request->test();

        BOOST_LOG_TRIVIAL(info) << "Annotating Document: " << request->document();
        // Perform annotation
        process::Processor Annotater(&searchTree);
        nlohmann::json annotations = Annotater.Annotate(request->document(), request->test());

        // TODO: Remove after testing multiple clients
        // std::this_thread::sleep_for(std::chrono::seconds(10));
        // Return annotations to user
        BOOST_LOG_TRIVIAL(info) << "Annotations: " << annotations.dump();
        response->set_annotations(annotations.dump());

        return grpc::Status::OK;
    }

    grpc::Status AnnotateFile(grpc::ServerContext* context, grpc::ServerReader<searchtree::AnnotateRequest>* reader,
                                searchtree::AnnotateResponse* response) override {
        searchtree::AnnotateRequest document;
        int document_cntr;
        system_clock::time_point start_time = system_clock::now();
        while(reader->Read(&document)) {
            document_cntr++;
            BOOST_LOG_TRIVIAL (info) << "Processed " << document_cntr << " documents.";
        }

        std::stringstream resp;
        resp << "Dummy Annotations for " << document_cntr << " documents.";
        response->set_annotations(resp.str());
        return grpc::Status::OK;
    }

private:
    /*
        Add the user supplied terms to the Forest.
    */
    void AddTreeToForest(std::string uuid, std::vector<std::string> tree_data) {
        if (forest.count(uuid) == 0) {
            forest[uuid] = tree_data;
        } else {
            BOOST_LOG_TRIVIAL(warning) << "Tree with UUID[" << uuid << "] already exists in the Forest";
        }
    }

    std::vector<std::string> StringToVec(std::string terms) {
        std::vector<std::string> vec;

        // First strip any trailing whitespaces from commas seperating terms
        while( true ) {
            auto pos = terms.find( ", " );
            if( pos == std::string::npos )
                break;
            terms.replace( pos, 2, "," );
        }

        std::stringstream ss(terms);
        std::string term;
        while(std::getline(ss, term, ',')) {
            vec.push_back(term);
        }

        return vec;
    }

    std::vector<std::string> CleanTsv(std::string tsvFile, int columnIndex) {
        // Initialise a map to hold the terms to be inserted into the Search Tree
        std::set<std::string> terms;
        std::vector<std::string> termsShuffler;

        // Read in the file
        if (std::filesystem::exists(tsvFile)) {
            std::fstream tsvFileStream;
            tsvFileStream.open(tsvFile, std::ios::in);

            // Temporary line string
            std::string line;
            while(!tsvFileStream.eof()) {
                // Initialise a vector for columns and temporary string
                std::vector<std::string> columns;
                std::string temp;

                // Get current row of the TSV
                std::getline(tsvFileStream, line);
                std::stringstream buffer(line);

                // Read the tab seperated column into a vector
                while (std::getline(buffer, temp, '\t')) {
                    columns.push_back(temp);
                }

                // Now we can extract the desired column by indexing into the vector
                if (columns.size() >= columnIndex) {
                    std::string lowerCaseVersion = columns[columnIndex];

                    std::for_each(lowerCaseVersion.begin(), lowerCaseVersion.end(), [](char & c) {
                        c = ::tolower(c);
                    });

                    // If the value of the column doesn't exist add it to the map of terms
                    if (!terms.count(columns[columnIndex])) {
                        // The set here is only used to ensure uniqueness
                        terms.insert(columns[columnIndex]);
                        termsShuffler.push_back(columns[columnIndex]);
                        termsShuffler.push_back(lowerCaseVersion);
                    }
                }
            }
        } else {
            std::cout << "DID NOT FIND THE FILE" << std::endl;
        }

        // Now create a randomized vector
        std::random_device rd;
        std::mt19937 g(rd());
        std::shuffle(termsShuffler.begin(), termsShuffler.end(), g);

        return termsShuffler;
    }

    // Private members
    tree::TernaryTree searchTree;
    tree::TernaryTree usersTree;
    // The Forest can be used to reconstruct Trees with their uuids
    std::map<std::string, std::vector<std::string>> forest;
    boost::uuids::random_generator uuid_generator;
};
