#pragma once
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <nlohmann/json.hpp>
#include <random>
#include <sstream>
#include <string>
#include <vector>

struct tsvOpts {
    int targetColumns;
    bool shuffleFlag;
    std::fstream tsvFile;
    std::fstream outputFile;
};

tsvOpts cleanTsvCheckCommandOptions(int argc, char* argv[]);

void cleantsv(std::fstream *tsvFile, std::fstream *outPutFile, int targetColumn, bool shuffle);
