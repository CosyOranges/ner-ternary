#include <iostream>

static void DisplayHelp() {
    fputs("nerternary \n\n"
        "  usage: nerternary [options] <smarts> <db.atdb> [<outfile>]\n"
        "         nerternary [options] <queries.sma> <db.atdb> [<outfile>]\n"
        "         nerternary [options] - <db.atdb> [<outfile>]\n"
        "    options: -d           Path to the tree data\n"
        "             -i           Path to the input directory of .txt files\n"
        "             -o           Path to the output directory\n",
        stderr);
    exit(1);
}

static void ProcessCommandLine(int argc, char* argv[]) {
    if (argc == 0) {
        DisplayHelp();
    }
};
