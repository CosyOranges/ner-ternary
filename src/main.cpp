
#include <chrono>
#include <filesystem>
#include <map>
#include <random>

// --------------- local includes --------------- //
#include <lib/node.hpp>
#include <lib/processData.hpp>
#include <src/cli/cli.hpp>
#include <mpi.h>

/*
	MAIN
*/
int main(int argc, char* argv[]) {
	// Initialise variables and fill with input values, this has 0 error handling
	// and so will break if input is not supplied in the following:
	// ./ternary -d './path/to/disease.tsv' -i './path/to/input/data' -o './path/to/output'
	ProcessCommandLine(argc, argv);
	/*
	SUCCESSFULLY REFACTORED TO tsvCleaner.hpp
	std::string productDataDir = argv[2];
	std::string textDataDir = argv[4];
	std::string outPutDir = argv[6];

	std::cout << "-----------------------------------------------------------\n\t\t\tPROGRAM START\n-----------------------------------------------------------\n" << std::endl;
	std::cout << "Reading Tree Data from: " << productDataDir << std::endl;
	std::cout << "Reading Papers to be tagged from: " << textDataDir << std::endl;
	std::cout << "\n-----------------------------------------------------------\n" << std::endl;
	std::cout << "Building and Shuffling Tree Data...";

	std::fstream writeTreeDataFile;
	std::fstream readTreeDataFile;
	writeTreeDataFile.open(outPutDir + "/treeData.txt", std::ios::out);
	cleanProductData(productDataDir, &writeTreeDataFile);
	writeTreeDataFile.close();
	*/
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

