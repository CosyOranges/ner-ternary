#include <lib/processor.hpp>
#include <iostream>

namespace process {
    Processor::Processor(tree::TernaryTree* tree) {
        tree_ = tree;
        longest_substr = tree_->depth();

    }

    Processor::~Processor() {
    }

    nlohmann::json Processor::Annotate(const std::string& data, int id) {
        BOOST_LOG_TRIVIAL (info) << "Annotating Document [" << id << "]";

        // This will be used to index to the current word
        int curr_idx = 0;

        // Empty strings for the longest true match prefix and the annotations
        std::string longest_true_prefix = "";

        // Loop from the start of the string through to the end and annotate as we go
        while (curr_idx < data.size()) {
            longest_true_prefix = tree_->LongestPrefix(data, true, curr_idx);

            if (longest_true_prefix.size() > 0) {
                // build annotation
                annotations["keys"][longest_true_prefix].push_back(1);
            }

            // Increment the index to the next word
            curr_idx = NextWord(curr_idx, data);
        }

        BOOST_LOG_TRIVIAL (info) << "Annotated Document [" << id << "].";
        return annotations;
    }

    /*
        Utility to return longest_substring to search for.
    */
    int Processor::longest_substring() {
        return longest_substr;
    }

    /*
        Find the index of the next word in a string given a starting index.
    */
    int Processor::NextWord(int curr_idx, const std::string& data) {
        for (int i=curr_idx; i<data.size(); i++) {
            if (data[i] == ' ') {
                return i +1;
            } else if (data[i] == '\t') {
                return i+1;
            } else if (data[i] == '\n') {
                return i+1;
            }
        }

        return data.size();
    }
}
