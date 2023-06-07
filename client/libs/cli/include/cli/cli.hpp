#pragma once
#include <iostream>
#include "../src/tsvCleaner.hpp"
#include "../src/annotater.hpp"

static void DisplayHelp(std::string command) {

    if (command == "clean-tsv") {

        fputs(
            "\n\tusage: nerternary clean-tsv [options] <path/to/input.tsv> <path/to/outfile.txt>\n\n"
            "\toptions: -c (REQUIRED)       Column of the tsv with the desired words to build the ternary tree with (e.g. -c 4)\n"
            "\t\t -s (OPTIONAL)       Include this option to shuffle the cleaned words, if omitted the words will be stored in alphabetical order (e.g. -s)\n",
            stderr);

    } else if (command == "annotate") {

        fputs(
            "\n\tusage: nerternary annotate <string_to_annotate>\n\n"
            "\toptions: -f (OPTIONAL)       A path to a local file to annotate [For an s3 path you MUST supply the -a flag].\n"
            "\t\t -d (OPTIONAL)       A path to a local directory to annotate [For an s3 path you MUST supply the -a flag].\n"
            "\t\t -a (OPTIONAL)       This flag implies that the provided file or directory is located in an s3 bucket.",
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
                cleantsv(&options.tsvFile, &options.outputFile, options.targetColumns, options.shuffleFlag);
            }

        } else if (command == "annotate"){

            if (argc == 3 && (strcmp(argv[2], "-h") == 0 || strcmp(argv[2], "--help") == 0)) {

                DisplayHelp(command);

            } else {
                annotaterOpts options;
                options = annotaterCheckCommandOptions(argc, argv);

                annotate(options);
            }

        } else {

            std::cout << "\tCommand not found: " << std::endl;
            DisplayHelp(command);

        }

    } else {

        DisplayHelp("default");

    }
};
