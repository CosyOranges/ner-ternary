#include "tsvCleaner.hpp"

tsvOpts cleanTsvCheckCommandOptions(int argc, char* argv[]) {
    char *ptr;
    tsvOpts options;

    int i, j;
    j=0;
    for (int i=2; i<argc; i++) {
        ptr = argv[i];

        if (ptr[0] == '-' && ptr[1]) {
            ++ptr;
            switch (*ptr)
            {
            case 'c':
                options.targetColumns = atoi(argv[++i])-1;
                break;

            case 's':
                options.shuffleFlag = true;
                break;

            default:
                break;
            }
        } else switch(j++) {
            case 0:
                if (!std::filesystem::exists(argv[i])) {
                    fprintf(stderr, "\nError: Could not open %s.", argv[i]);
                    exit(1);
                } else {
                    std::string file = argv[i];
                    options.tsvFile.open(file, std::ios::in);
                }
                break;
            case 1:
                if(!std::filesystem::exists(argv[i]))
                {
                    fprintf(stderr, "\nError: Output %s does not exist.", argv[i]);
                    exit(1);
                } else {
                    std::string file = argv[i];
                    int length = file.length();
                    if (file[length-1] != '/') {
                        options.outputFile.open(file + "/tree-data.txt", std::ios::out);
                    } else {
                        options.outputFile.open(file + "tree-data.txt", std::ios::out);
                    }
                }
                break;
            default:
                fprintf(stderr, "\nError: too many arguments!");
                exit(1);
        }
    }

    if (j < 2) {
        fprintf(stderr, "\nToo few Arguments supplied.\n\nFor help: nerternary [command] --help");
        exit(1);
    }

    return options;
}

void cleantsv(std::fstream *tsvFile, std::fstream *outPutFile, int targetColumn, bool shuffle) {
	// 1. the tsv file that will be read in
	// 2. map to hold the diseases (avoiding duplicating diseases)
	std::map<std::string, int> diseaseMap;
    std::vector<std::string> shuffler;

	// Read the file
	if (tsvFile->is_open()) {
		std::string line;
		std::vector<std::string> ingredients;

		while (!tsvFile->eof()) {
			std::vector<std::string> values;
			std::getline(*tsvFile, line);
			std::stringstream buffer(line);
			std::string temp;

			// Split the line at tab spaces
			while (std::getline(buffer, temp, '\t')) {
				values.push_back(temp);
			}

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
            for (std::map<std::string, int>::iterator it = diseaseMap.begin(); it != diseaseMap.end(); it++) {
                *outPutFile << it->first << std::endl;
            }
        }
	}

	// Close files
	tsvFile->close();
}
