#pragma once
#include <boost/log/core.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/trivial.hpp>
#include <fstream>
#include <string>
#include <vector>
#include <nlohmann/json.hpp>
#include <lib/node.hpp>

namespace process {
    class Processor {
        private:
        tree::TernaryTree *tree_;
        int longest_substr;

        int NextWord(int curr_idx, const std::string& data);

        public:
        Processor(tree::TernaryTree* tree);

        ~Processor();

        nlohmann::json Annotate(const std::string& data, int id);

        int longest_substring();

        nlohmann::json annotations;
    };
}
