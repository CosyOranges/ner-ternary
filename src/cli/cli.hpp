#pragma once
#include <iostream>
#include <src/cli/tsvCleaner.hpp>

static void DisplayHelp(std::string command) {

    if (command == "clean-tsv") {

        fputs(
            "\n\tusage: nerternary clean-tsv [options] <path/to/input.tsv> <path/to/outfile.txt>\n\n"
            "\toptions: -c (REQUIRED)       Column of the tsv with the desired words to build the ternary tree with (e.g. -c 4)\n"
            "\t\t -s (OPTIONAL)       Include this option to shuffle the cleaned words, if omitted the words will be stored in alphabetical order (e.g. -s)\n",
            stderr);

    } else if (command == "annotate") {

        fputs(
            "\n\tusage: nerternary annotate [options] <path/to/tree/words.txt> <path/to/input/dir> <path/to/output/dir>\n\n"
            "\toptions: -p (REQUIRED)       Option to run in parallel (true or false)\n"
            "\t\t\t -t (ONLY FOR PARALLEL)       Number of threads to use\n"
            "\t\t -d (OPTIONAL)       Supply a list of words to use instead of a .txt file for the ternary tree",
            stderr);

    } else {

        fputs(
            "\n\tusage:  nerternary [command] [options] [<...paths/files>]\n\n"
            "\tcommands: clean-tsv       To process a tsv file where one column contains the desired words to annotate for.\n"
            "\t\t annotate       To annotate a directory of .txt files and produce a json of where in the text the words can be found.\n",
            stderr);

    }

    exit(1);
}

static void ProcessCommandLine(int argc, char* argv[]) {
    std::string command;

    if (argc > 1) {

        command = argv[1];

        if (command == "clean-tsv") {

            if (argc == 3 && (strcmp(argv[2], "-h") || strcmp(argv[2], "--help"))) {

                DisplayHelp(command);

            } else if (argc < 6) {

                std::cout << "\tToo few arguments supplied." << std::endl;
                DisplayHelp(command);

            } else {
                // We have the minimum number of arguments now we need to validate them
                tsvOpts options;
                options = cleanTsvCheckCommandOptions(argc, argv);

                // Call the cleaner
                std::fstream writeTreeDataFile;
	            std::fstream readTreeDataFile;
	            writeTreeDataFile.open(options.outputFile + "/tree-data.txt", std::ios::out);
                cleantsv(options.tsvFile, &writeTreeDataFile, options.targetColumns, options.shuffleFlag);
            }

        } else if (command == "annotate"){

            if (argc == 3 && (strcmp(argv[2], "-h") || strcmp(argv[2], "--help"))) {

                DisplayHelp(command);

            } else if (argc < 6) {

                std::cout << "\tToo few arguments supplied." << std::endl;
                DisplayHelp(command);

            }

        } else {

            std::cout << "\tCommand not found: " << std::endl;
            DisplayHelp(command);

        }

    } else {

        DisplayHelp("default");

    }
};
