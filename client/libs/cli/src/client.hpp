#pragma once
#include <SearchTree/searchtree.grpc.pb.h>
#include <grpc++/grpc++.h>
#include <thread>

class SearchTreeClient {
    public:
        SearchTreeClient(std::shared_ptr<grpc::Channel> channel) : _stub{searchtree::SearchTree::NewStub(channel)} {}

        void ReplaceTree(std::string terms) {
            // Prepare request
            searchtree::TempTreeRequest request;
            request.set_tree_terms(terms);

            // Container for the expected response
            searchtree::TempTreeResponse response;

            // Contedt for the client. It could be used to convey extra information
            // to the server and/or tweak certain RPC behaviours.
            grpc::ClientContext context;

            // The Actual RPC
            std::cout << "Submitting terms to build a temporary tree." << std::endl;
            grpc::Status status = _stub->ReplaceTree(&context, request, &response);

            // Check status of request/response
            if (status.ok()) {
                std::cout << "RESPONSE: " << response.tree_id() << std::endl;
            } else {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

        void InsertToTree(std::string terms) {
            // Prepare request
            searchtree::InsertTreeRequest request;
            request.set_tree_terms(terms);

            // Container for the expected response
            searchtree::InsertTreeResponse response;

            // Contedt for the client. It could be used to convey extra information
            // to the server and/or tweak certain RPC behaviours.
            grpc::ClientContext context;

            // The Actual RPC
            std::cout << "Inserting new terms to existing tree." << std::endl;
            grpc::Status status = _stub->InsertToTree(&context, request, &response);

            // Check status of request/response
            if (status.ok()) {
                std::cout << "RESPONSE: " << response.ready() << std::endl;
            } else {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

        void Annotate(std::string document, int ind) {
            // Prepare request
            searchtree::AnnotateRequest request;
            request.set_test(ind);
            request.set_document(document);

            // Container for the response expected
            searchtree::AnnotateResponse response;

            // Contedt for the client. It could be used to convey extra information
            // to the server and/or tweak certain RPC behaviours.
            grpc::ClientContext context;

            // The actual RPC
            std::cout << "Submitting document (ID: " << request.test() << ") for annotating.\nContents: " << request.document() << std::endl;
            grpc::Status status = _stub->Annotate(&context, request, &response);

            if (status.ok()) {
                std::cout << "RESPONSE: " << response.annotations() << std::endl;
            } else {
                std::cout << status.error_code() << ": " << status.error_message() << std::endl;
            }
        }

        void AnnotateFile() {
            grpc::ClientContext context;
            searchtree::AnnotateResponse response;
            std::unique_ptr<grpc::ClientWriter<searchtree::AnnotateRequest> > writer(
                _stub->AnnotateFile(&context, &response));

            for (int i=0; i < 10; i ++) {
                std::cout << "Submitting Document no: " << i << std::endl;
                searchtree::AnnotateRequest request;
                request.set_test(i);
                request.set_document("Test for client streaming.");
                if (!writer->Write(request)) {
                    break;
                }
                std::this_thread::sleep_for(
                    std::chrono::milliseconds(10)
                );
            }
            writer->WritesDone();

            grpc::Status status = writer->Finish();
            if (status.ok()) {
                std::cout << "Done.";
            } else {
                std::cout << "AnnotateFile rpc failed." << std::endl;
            }
        }

        // void RecordRoute() {
        //     Point point;
        //     RouteSummary stats;
        //     ClientContext context;
        //     const int kPoints = 10;
        //     unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();

        //     std::default_random_engine generator(seed);
        //     std::uniform_int_distribution<int> feature_distribution(
        //         0, feature_list_.size() - 1);
        //     std::uniform_int_distribution<int> delay_distribution(500, 1500);

        //     std::unique_ptr<ClientWriter<Point> > writer(
        //         stub_->RecordRoute(&context, &stats));
        //     for (int i = 0; i < kPoints; i++) {
        //     const Feature& f = feature_list_[feature_distribution(generator)];
        //     std::cout << "Visiting point " << f.location().latitude() / kCoordFactor_
        //                 << ", " << f.location().longitude() / kCoordFactor_
        //                 << std::endl;
        //     if (!writer->Write(f.location())) {
        //         // Broken stream.
        //         break;
        //     }
        //     std::this_thread::sleep_for(
        //         std::chrono::milliseconds(delay_distribution(generator)));
        //     }
        //     writer->WritesDone();
        //     Status status = writer->Finish();
        //     if (status.ok()) {
        //     std::cout << "Finished trip with " << stats.point_count() << " points\n"
        //                 << "Passed " << stats.feature_count() << " features\n"
        //                 << "Travelled " << stats.distance() << " meters\n"
        //                 << "It took " << stats.elapsed_time() << " seconds"
        //                 << std::endl;
        //     } else {
        //     std::cout << "RecordRoute rpc failed." << std::endl;
        //     }
        // }

    private:
        std::unique_ptr<searchtree::SearchTree::Stub> _stub;
};
