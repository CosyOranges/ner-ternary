#include "annotater.hpp"

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
            case 'f':
                i++;
                if (i < argc && !options.directory){
                    std::cout << "The file to annotate is: " << argv[i] << std::endl;
                    if (!std::filesystem::exists(argv[i])) {
                        std::string path = argv[i];
                        fprintf(stderr, "\nError: Could not open '%s'.", path.c_str());
                        exit(1);
                    } else {
                        options.inputFile = argv[i];
                    }
                    j++;
                    options.single_file = true;
                } else if (options.directory) {
                    fprintf(stderr, "\nError: Can not specify a file after a directory has been specified.");
                } else {
                    std::cout << "Missing file to annotate.\n";
                }
                break;

            case 'd':
                i++;
                if (i < argc && !options.single_file){
                    if (!std::filesystem::exists(argv[i])) {
                        std::string path = argv[i];
                        fprintf(stderr, "\nError: Could not open '%s'.", path.c_str());
                        exit(1);
                    } else {
                        options.inputFile = argv[i];
                    }
                    j++;
                    options.directory = true;
                } else if (options.single_file) {
                    fprintf(stderr, "\nError: Can not specify a directory after a file has been specified.");
                } else {
                    std::cout << "Missing directory to annotate.\n";
                }
                break;

            case 'a':
                options.aws_s3 = true;
                break;

            default:
                break;
            }
        } else switch(j++) {
            case 0:
                options.adhoc = argv[i];
                break;
            case 1:
                throw std::invalid_argument("Cannot supply a string to annotate with other arguments.");
                break;
        }
    }

    if (j < 1) {
        fprintf(stderr, "\nToo few Arguments supplied.\n\nFor help: nerternary [command] --help\n");
        exit(1);
    }

    return options;
}


void annotate(annotaterOpts options) {
    std::string server_address{"0.0.0.0:50051"};
    SearchTreeClient client{grpc::CreateChannel(server_address, grpc::InsecureChannelCredentials())};

    std::cout << "Current Annotation Options are:\n";
    std::cout << "\tAWS s3: " << options.aws_s3 << '\n';
    std::cout << "\tsingle_file: " << options.single_file << '\n';
    std::cout << "\tdirectory: " << options.directory << '\n';
    std::cout << "\tadhoc: " << options.adhoc << '\n';
    std::cout << "\tinputFile: " << options.inputFile << '\n';
    std::cout << "\tinputDirector: " << options.inputDir << '\n';

    if (options.single_file && !options.aws_s3) {
        // we are annotating a file
        std::cout << "Annotating a local file" << std::endl;
        client.AnnotateFile();
    } else if (options.directory) {
        // we are processing multiple files
    } else {
        // we are processing an adhoc string annotation request
        // Request is submitted with an ID of -1 to indicate an adhoc annotation request.
        client.Annotate(options.adhoc, -1);
    }
    // while (!treedata->eof()) {
    //     std::getline(*treedata, line);
    //     if (line.length() > 0) {
    //         words.push_back(line);
    //     }
    // }

    // tree::TernaryTree root;
    // root.BuildFromVec(words);

    // std::ifstream f("/Users/calvindavies/data/pubmed/abstracts/pubmed22n0001.abs");
    // nlohmann::json j;
    // line = "";
    // int count = 0;
    // while (!f.eof()) {
    //     std::getline(f, line);
    //     if (line.size() > 0)
    //         j.push_back(nlohmann::json::parse(line));
    // }

    // std::cout << j[0]["text"].dump() << "\n";
    // std::cout << j.size() << "\n";

    // int count = 0;
	// std::chrono::duration<double, std::ratio<1, 1>> dbDuration;
	// auto start = std::chrono::high_resolution_clock::now();

    // for (const auto &entry : std::filesystem::directory_iterator(inputTextDir)) {
    //     std::string file_path = entry.path();
    //     std::string file_name = entry.path().filename();

    //     utils::ProcessFile(file_name, file_path, outputJsonDir, &root);
    //     std::cout << "PATH: " << file_path << " | FILE_NAME: " << file_name << "\n";
    //     count++;
    // }

    // auto finish = std::chrono::high_resolution_clock::now();
	// dbDuration = std::chrono::duration_cast<std::chrono::duration<double>>(finish - start);

	// std::cout.precision(5);
	// std::cout << "\n----------------------------" << std::endl;
	// std::cout << "Processed: " << count << " files." << std::endl;
	// std::cout << "Time Elapsed: " << dbDuration.count() << "s" << std::endl;
    // std::cout << "\n----------------------------" << std::endl;
    // std::cout << "Written to: " << outputJsonDir <<"/annotations/" << std::endl;
}

// nlohmann::json PrepFileStream(std::string local_file) {
//     nlohmann::json texts;

// }
