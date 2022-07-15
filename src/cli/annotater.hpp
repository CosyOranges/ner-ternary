#pragma once
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <random>
#include <lib/processData.hpp>
#include <lib/node.hpp>

struct annotaterOpts {
    bool parallel = false;
    int processors = -1;
    std::fstream treedata;
    std::string inputTextDir;
    std::string outputJsonDir;
};

annotaterOpts annotaterCheckCommandOptions(int argc, char* argv[]) {
    char *ptr;
    annotaterOpts options;

    int i, j;
    j=0;
    for (int i=2; i<argc; i++) {
        ptr = argv[i];

        if (ptr[0] == '-' && ptr[1]) {
            ++ptr;
            switch (*ptr)
            {
            case 'p':
                options.parallel = true;
                break;

            case 't':
                options.processors = atoi(argv[++i]);
                break;

            default:
                break;
            }
        } else switch(j++) {
            case 0:
                if (!std::filesystem::exists(argv[i])) {
                    std::string path = argv[i];
                    fprintf(stderr, "\nError: Could not open '%s'.", path.c_str());
                    exit(1);
                } else {
                    std::string file = argv[i];
                    options.treedata.open(file, std::ios::in);
                }
                break;

            case 1:
                if(!std::filesystem::exists(argv[i]))
                {
                    fprintf(stderr, "\nError: Input '%s' does not exist.", argv[i]);
                    exit(1);
                } else {
                    options.inputTextDir = argv[i];
                }
                break;

            case 2:
                if(!std::filesystem::exists(argv[i]))
                {
                    fprintf(stderr, "\nError: Output '%s' does not exist.", argv[i]);
                    exit(1);
                } else {
                    options.outputJsonDir = argv[i];
                }
                break;
        }
    }

    if (j < 3) {
        fprintf(stderr, "\nToo few Arguments supplied.\n\nFor help: nerternary [command] --help\n");
        exit(1);
    }

    if (options.processors != -1 && !options.parallel) {
        fprintf(stderr, "\nCannot request multiple processors without the parallel flag.\n\nFor help: nerternary [command] --help\n");
        exit(1);
    } else if (options.parallel && options.processors < 1) {
        fprintf(stderr, "\nImpossible to request less than one processor.\n\nFor help: nerternary [command] --help\n");
        exit(1);
    }

    return options;
}

void annotate(std::fstream *treedata, std::string inputTextDir, std::string outputJsonDir) {
    std::vector<std::string> words;
    std::string line;

    while (!treedata->eof()) {
        std::getline(*treedata, line);
        if (line.length() > 0) {
            words.push_back(line);
        }
    }

    Node* root = buildTST(words);

    int count = 0;
	std::chrono::duration<double, std::ratio<1, 1>> dbDuration;
	auto start = std::chrono::high_resolution_clock::now();

    for (const auto &entry : std::filesystem::directory_iterator(inputTextDir)) {
        std::string file_path = entry.path();
        std::string file_name = entry.path().filename();

        processFile(file_name, file_path, outputJsonDir, root);

        count++;
    }

    auto finish = std::chrono::high_resolution_clock::now();
	dbDuration = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start);

	std::cout.precision(5);
	std::cout << "\n----------------------------" << std::endl;
	std::cout << "Processed: " << count << " files." << std::endl;
	std::cout << "Time Elapsed: " << dbDuration.count() << "s" << std::endl;
    std::cout << "\n----------------------------" << std::endl;
    std::cout << "Written to: " << outputJsonDir <<"/annotations/" << std::endl;
}
