#pragma once
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <sstream>
#include <stdexcept>
#include "client.hpp"

struct annotaterOpts {
    bool aws_s3             = false;
    bool single_file        = false;
    bool directory          = false;
    std::string adhoc       = "NULL";
    std::string inputFile   = "NULL";
    std::string inputDir    = "NULL";
};

annotaterOpts annotaterCheckCommandOptions(int argc, char* argv[]);

/*
    CLI command to annotate
*/
void annotate(annotaterOpts options);
