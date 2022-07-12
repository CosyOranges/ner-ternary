#include <lib/processData.hpp>

/*
	WORKFLOW:

	1. Process the ingredients from the product-data dir
		- Create an diseases.txt file containing the diseases
		  in a shuffled format (they can't be ordered or the ternary tree
		  created will just be linked list)

	2. Read the diseasesShuffled.txt into a ternary tree, this will be used to search
	   ./text-data/PMC000xxxxxx/....txt and tag them accordingly

	3. Finally the tagging algorithm will be broken down into 4 main pieces

		a. TOKENISE LINES
			- Read the document in, it will need to be written out to the same file
			  but in a different dir.
			- Each line will need to be tokenised and punctuation stripped from it...

		b. SEARCH TOKENISED LINE
			- The tokenised line can then be looped over and each token searched for
			  in the ternary tree

		c. ADD TOKENS WHICH ARE DISEASES TO DICTIONARY<ingredient, [lines...]>
			- If the tokenised line has an "ingredient" in it, then we can add the
			  ingredient to a dict
			- This dict will be the ingredient and a list of lines that it occurs on...
				- This has the potential to be more fine grained (i.e. line number, position of starting character etc...)

		d. TAG
			- The document can then be tagged with the above dictionary...
			- Not to sure about this step yet...
			- alternatively a final data structure can be created with the following:
			{
				"documentid1":[
					{
						"ingredient1": [lines...]
					},
					{
						"ingredient2": [lines...]
					},
					etc...
				],
				"documentid2": [
					{
						"ingredient1": [lines...]
					},
					{
						"ingredient2": [lines...]
					}
				]
			}
*/

void cleanProductData(std::string inputData, std::fstream *outPutFile, int targetColumn) {
	// 1. the tsv file that will be read in
	// 2. map to hold the diseases (avoiding duplicating diseases)
	std::fstream tsvFile;
	std::map<std::string, int> diseaseMap;
	tsvFile.open(inputData, std::ios::in);

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
			if (values.size() == 7) {
				std::string key;
				std::stringstream temp(values[targetColumn]);
				std::getline(temp, key, ' ');

				// Force the key to be lowercase
				std::for_each(key.begin(), key.end(), [](char & c) {
					c = ::tolower(c);
				});

				// If the word doesn't exist add it, otherwise increase count
				if (!diseaseMap[key]) {
					diseaseMap[key] = 1;
				} else {
					diseaseMap[key]++;
				}
			}
		}

		// This will create the disease.txt file in alphabetical order, which is ideal for
		// viewing the diseases...
		// But will build a ternary tree that is essentially a linked list...
		// So we can put the keys into a vector and shuffle them
		// TODO: Consider if this can actually be brought into lines 91-93
		std::vector<std::string> shuffler;

		for (std::map<std::string, int>::iterator it = diseaseMap.begin(); it != diseaseMap.end(); it++) {
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
	tsvFile.close();
}

std::vector<std::string> tokenize(std::string sentence) {
	// First convert it entirely to lowercase
	std::for_each(sentence.begin(), sentence.end(), [](char & c) {
		c = ::tolower(c);
	});

    auto it = std::remove_if(sentence.begin(), sentence.end(), [](char const &c) {
        if (std::ispunct(c) && c != '-') {
			return true;
		} else {
			return false;
		}
    });

    sentence.erase(it, sentence.end());

    // All that's left is to tokenize the string, by using the ' ' char as a delimiter.
    std::vector<std::string> tokens;
    std::string temp;
    for (int i=0; i<sentence.length(); i++) {
        if (sentence[i] == ' ') {
            tokens.push_back(temp);
            temp = "";
        } else {
            temp += sentence[i];
        }
    }
    tokens.push_back(temp);
    return tokens;
}


void writeAnnotationOut(std::string file_name, std::string out_path, std::map<std::string, std::vector<int>> annotations) {
	// initialisations
	std::fstream outFile;
	nlohmann::json j;
	std::string new_file_name, out_put_path;

	out_put_path = out_path + "/annotations/";
	if (!std::filesystem::is_directory(out_put_path) || !std::filesystem::exists(out_put_path)) { // Check if src folder exists
    	std::filesystem::create_directory(out_put_path);
	}

	// add a number that is stored as double (note the implicit conversion of j to an object)
    // replacing .(...) file extension with .json
	for (int i=0; i < file_name.length()-1; i++) {
		if (file_name[i] == '.')
			break;
		new_file_name.push_back(file_name[i]);
	}
	outFile.open(out_path + "/annotations/" + new_file_name + ".json", std::ios::out);

	for (std::map<std::string, std::vector<int>>::iterator it = annotations.begin(); it != annotations.end(); it++) {
		std::vector<int> lines;
		for (int i=0; i<it->second.size(); i++) {
			lines.push_back(it->second[i]);
		}
		j["Diseases"][it->first] = lines;
	}
	outFile << j.dump(4) << std::endl;
	outFile.close();
}


void processFile(std::string file_name, std::string file_path, std::string out_path, Node* root) {
	/*
		This function will need to read the file in...

		It will need a counter to keep track of lines

		It will then perform a while loop until the EOF

			Inside this loop it will:

				a. Tokenize the line increment the lineCounter (so all files will start at line 1)

				b. Search for the tokens in the line in the TST

					a. Loop through each token

					b. If a token is found, add it as a key to the annotation map and add the lineCounter to the vector value...

					c. If token is not found continue

				c. Loop again
	*/

	std::fstream inFile;
	inFile.open(file_path);

    // Initialise needed variables
	int lineCounter = 0;
    std::string line;
    std::vector<std::string> tokenizedLine;
    std::map<std::string, std::vector<int>> annotationMap;

	while (!inFile.eof()) {
        // Read in the file
        std::getline(inFile, line);

        // Tokenize the line and strip punctuation
        tokenizedLine = tokenize(line);

        // Loop through the tokenized line, search for each string in the TST
        for (int i=0; i<tokenizedLine.size(); i++) {
            if (searchTST(root, tokenizedLine[i])) {
                annotationMap[tokenizedLine[i]].push_back(lineCounter);
            }
        }

        // Increment line counter
        lineCounter++;
	}

    writeAnnotationOut(file_name, out_path, annotationMap);
}
