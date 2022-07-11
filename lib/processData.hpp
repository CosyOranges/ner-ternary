#pragma once
#include <algorithm>
#include <cctype>
#include <filesystem>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <map>
#include <nlohmann/json.hpp>
#include <lib/node.hpp>

/*
    TODO: Move this functionality from src/main.cpp to here
*/
void cleanProductData();

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


/*
    Writes the annotations found in a `.txt` file to a `.json` in an `annotation` directory following the path
    specified using the `--output-file` flag.


    ---
    Args:
    - file_name: std::string The name of the `.txt` file that has been processed.
    - out_path: std::string The path to the output directory as specified using the `--output-file` flag.
    - annotations: std::map<std::string, std::vector<int>> The annotations data structure to be converted into a `json` format which will be used to create the `/annotations/<...>.json` file.
*/
void writeAnnotationOut(std::string file_name, std::string out_path, std::map<std::string, std::vector<int> > annotations);
