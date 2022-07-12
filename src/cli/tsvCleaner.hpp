#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <random>

static unsigned int targetColumn;
static bool shuffleFlag;

struct tsvOpts {
    int targetColumns;
    bool shuffleFlag;
    std::string tsvFile;
    std::string outputFile;
};

tsvOpts cleanTsvCheckCommandOptions(int argc, char* argv[]) {
    char *ptr;
    tsvOpts *options = new tsvOpts;

    int i, j;
    j=0;
    for (int i=2; i<argc; i++) {
        ptr = argv[i];

        if (ptr[0] == '-' && ptr[1]) {
            ++ptr;
            switch (*ptr)
            {
            case 'c':
                options->targetColumns = atoi(argv[++i])-1;
                break;

            case 's':
                options->shuffleFlag = true;
            default:
                break;
            }
        } else switch(j++) {
            case 0:
                options->tsvFile = argv[i];
                if (!std::filesystem::exists(options->tsvFile)) {
                    fprintf(stderr, "Error: Could not open tsv file.");
                    exit(1);
                }
                break;
            case 1: options->outputFile = argv[i];  break;
            default:
                fprintf(stderr, "Error: too many arguments!");
                exit(1);
        }
    }

    return *options;
}

void cleantsv(std::string inputTsv, std::fstream *outPutFile, int targetColumn, bool shuffle) {
	// 1. the tsv file that will be read in
	// 2. map to hold the diseases (avoiding duplicating diseases)
	std::fstream tsvFile;
	std::map<std::string, int> diseaseMap;
	tsvFile.open(inputTsv, std::ios::in);
    std::vector<std::string> shuffler;

	// Read the file
	if (tsvFile.is_open()) {
		std::string line;
		std::vector<std::string> ingredients;

		while (!tsvFile.eof()) {
			std::vector<std::string> values;
			std::getline(tsvFile, line);
			std::stringstream buffer(line);
			std::string temp;

			// Split the line at tab spaces
			while (std::getline(buffer, temp, '\t')) {
				values.push_back(temp);
			}

			// TODO: Refactor to allow the user to pass down the target column
            if (values.size() >= targetColumn){
                std::string key;
                std::stringstream temp_stream(values[targetColumn]);
                std::getline(temp_stream, key, ' ');

                // Force the key to be lowercase
                std::for_each(key.begin(), key.end(), [](char & c) {
                    c = ::tolower(c);
                });

                // If the word doesn't exist add it, otherwise increase count
                if (!diseaseMap[key]) {
                    diseaseMap[key] = 1;
                    shuffler.push_back(key);
                } else {
                    diseaseMap[key]++;
                }
            }
		}

		// This will create the disease.txt file in alphabetical order, which is ideal for
		// viewing the diseases...
		// But will build a ternary tree that is essentially a linked list...
		// So we can put the keys into a vector and shuffle them
        if (shuffle) {
            // initialize random number generator
            std::random_device rd;
            std::mt19937 g(rd());
            std::shuffle(shuffler.begin(), shuffler.end(), g);

            for (int i=0; i< shuffler.size(); i++) {
                *outPutFile << shuffler[i] << std::endl;
            }
        } else {
            for (int i=0; i< shuffler.size(); i++) {
                *outPutFile << shuffler[i] << std::endl;
            }
        }
	}

	// Close files
	tsvFile.close();
}
