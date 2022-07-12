
#include <chrono>
#include <filesystem>
#include <map>
#include <random>

// --------------- local includes --------------- //
#include <lib/node.hpp>
#include <lib/processData.hpp>
#include <src/cli/cli.hpp>
#include <mpi.h>

// TODO: This should live in lib/processData, main should only be calling functions, not defining them.
void cleanProductData(std::string inputData, std::fstream *outPutFile) {
	// Create data structures needed
	// 1. fstream for the input txt file
	// 2. fstream for the processed txt file
	// 3. map to hold the diseases (avoiding duplicating diseases)
	std::fstream inFile;
	std::map<std::string, int> diseaseMap;
	inFile.open(inputData, std::ios::in);

	if (inFile.is_open()) {
		std::string line;
		std::vector<std::string> ingredients;
		while (!inFile.eof()) {
			std::vector<std::string> values;
			std::getline(inFile, line);
			std::stringstream buffer(line);
			std::string temp;
			while (std::getline(buffer, temp, '\t')) {
				values.push_back(temp);
			}

			if (values.size() == 7) {
				std::string key;
				std::stringstream temp(values[3]);
				std::getline(temp, key, ' ');

				// Force the key to be lowercase
				std::for_each(key.begin(), key.end(), [](char & c) {
					c = ::tolower(c);
				});
				if (!diseaseMap[key]) {
					diseaseMap[key] = 1;
				} else {
					diseaseMap[key]++;
				}
			}
		}

	// 	// This will create the disease.txt file in alphabetical order, which is ideal for
	// 	// viewing the diseases...
	// 	// But will build a ternary tree that is essentially a linked list...
	// 	// So we can put the keys into a vector and shuffle them
		std::vector<std::string> shuffler;
		for (std::map<std::string, int>::iterator it = diseaseMap.begin(); it != diseaseMap.end(); it++) {
			// std::cout << it->first << " : " << it->second << std::endl;
			shuffler.push_back(it->first);
		}
		// initialize random number generator
    	std::random_device rd;
    	std::mt19937 g(rd());
		std::shuffle(shuffler.begin(), shuffler.end(), g);

		for (int i=0; i< shuffler.size(); i++) {
			*outPutFile << shuffler[i] << std::endl;
		}
	}

	// Close files
	inFile.close();
}

/*
	MAIN
*/
int main(int argc, char* argv[]) {
	// Initialise variables and fill with input values, this has 0 error handling
	// and so will break if input is not supplied in the following:
	// ./ternary -d './path/to/disease.tsv' -i './path/to/input/data' -o './path/to/output'
	ProcessCommandLine(argc, argv);
	// std::string productDataDir = argv[2];
	// std::string textDataDir = argv[4];
	// std::string outPutDir = argv[6];

	// std::cout << "-----------------------------------------------------------\n\t\t\tPROGRAM START\n-----------------------------------------------------------\n" << std::endl;
	// std::cout << "Reading Tree Data from: " << productDataDir << std::endl;
	// std::cout << "Reading Papers to be tagged from: " << textDataDir << std::endl;
	// std::cout << "\n-----------------------------------------------------------\n" << std::endl;
	// std::cout << "Building and Shuffling Tree Data...";

	// std::fstream writeTreeDataFile;
	// std::fstream readTreeDataFile;
	// writeTreeDataFile.open(outPutDir + "/treeData.txt", std::ios::out);
	// cleanProductData(productDataDir, &writeTreeDataFile);
	// writeTreeDataFile.close();
	// readTreeDataFile.open(outPutDir + "/treeData.txt", std::ios::in);

	// std::cout << " Done." << std::endl;
	// std::cout << "\n-----------------------------------------------------------\n\n";

	// std::vector<std::string> diseases;
	// std::string line;

	// while (!readTreeDataFile.eof()) {
	// 	std::getline(readTreeDataFile, line);
	// 	if (line.length() > 0)
	// 		diseases.push_back(line);
	// }
	// readTreeDataFile.close();

	// std::cout << "\n-----------------------------------------------------------\n" << std::endl;
	// std::cout << "Building and Ternary Tree...";

	// Node* root = buildTST(diseases);

	// std::cout << "\n-----------------------------------------------------------\n" << std::endl;

	// std::cout << " Done." << std::endl;
	// std::cout << "\n-----------------------------------------------------------\n" << std::endl;
	// std::cout << "Searching Text Files for Diseases and Annotating..." << std::endl;

	// int count = 0;
	// std::chrono::duration<double, std::ratio<1, 1>> dbDuration;
	// auto start = std::chrono::high_resolution_clock::now();

    // for (const auto & entry : std::filesystem::directory_iterator(textDataDir)) {
	// 	std::string file_path = entry.path();
	// 	std::string file_name = entry.path().filename();
	// 	std::cout << file_path << " | NAME: " << file_name << std::endl;
	// 	processFile(file_name, file_path, outPutDir, root);
	// 	count++;
	// }

	// auto finish = std::chrono::high_resolution_clock::now();
	// dbDuration = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start);

	// std::cout.precision(5);
	// std::cout << " Done." << std::endl;
	// std::cout << "\n----------------------------\n" << std::endl;
	// std::cout << "Processed: " << count << " files." << std::endl;
	// std::cout << "Time Elapsed: " << dbDuration.count() << "s\n" << std::endl;

	// // Write timings to text file
	// std::fstream timings;
	// timings.open("./timings.txt", std::ios_base::app);
	// timings << "\n" << textDataDir << "\t" << count << "\t" << dbDuration.count() << std::endl;

	// std::cout << "--------PROGRAM FINISHED--------" << std::endl;

	return 0;
}

