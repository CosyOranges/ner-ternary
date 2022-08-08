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

// --------------- local includes --------------- //
#include <lib/node.hpp>

/*
    This will split up a sentence (or more accurately a line read from a file) into "tokenized" strings.
    This functionality is currently very basic, it will preserve hyphenated words, and force the string to
    be all lowercase in an effort to standardize between the ternary-tree data and the text data.

    ---
    Args:
    - sentence: std::string The string to be tokenized.

    Returns:
    - std::vector\<std::string> A vector of the tokenized strings.
*/
std::vector<std::string> tokenize(std::string sentence);


/*
    Read a file in, tokenise the lines and create the annotations that will be written to the output `.json`.
*/
void processFile(std::string file_name, std::string file_path, std::string out_path, Node* root);
