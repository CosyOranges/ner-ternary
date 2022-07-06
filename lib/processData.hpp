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
#include "node.hpp"

void cleanProductData();
std::vector<std::string> tokenize(std::string sentence);
void writeAnnotationOut(std::string file_name, std::string file_path, std::string out_path, std::map<std::string, std::vector<int> > annotations);
void processFile(std::string file_name, std::string file_path, std::string out_path, Node* root);
