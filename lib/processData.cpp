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
	// Initialise needed variables
	int lineCounter = 0;
	nlohmann::json j;
    std::string line;
    std::vector<std::string> tokenizedLine;
	std::fstream inFile;
	std::fstream outFile;
	std::string new_file_name, out_put_path;

	// Create sub directory for the annotations
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
	outFile.open(out_put_path + new_file_name + ".json", std::ios::out);
	inFile.open(file_path, std::ios::in);

	while (!inFile.eof()) {
        // Read in the file
        std::getline(inFile, line);

        // Tokenize the line and strip punctuation
        tokenizedLine = tokenize(line);

		int startChar = 0;
		int endChar = 0;
        // Loop through the tokenized line, search for each string in the TST
        for (int i=0; i<tokenizedLine.size(); i++) {

			if (i != 0) {
				startChar = endChar + 2;
			}
			endChar = startChar + tokenizedLine[i].length() - 1;

            if (searchTST(root, tokenizedLine[i])) {
				j["annotations"]["tokens"][tokenizedLine[i]]["lines"][std::to_string(lineCounter+1)].push_back({startChar, endChar});
            }
        }

        // Increment line counter
        lineCounter++;
	}

	outFile << j.dump(4) << std::endl;
	outFile.close();
}
