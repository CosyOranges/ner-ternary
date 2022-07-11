#include <lib/node.hpp>
#include <iostream>


Node::Node(char x){
		key = x;

		left = nullptr;
		right = nullptr;
		mid = nullptr;

		endOfString = false;
};

Node* buildTST(std::vector<std::string> &str) {
	Node *root = nullptr;
	int count = 0;
	for(std::string s : str) {
		root = insertNode(root, s, 0);
	}
	return root;
}

Node* insertNode(Node* root, const std::string &s, int ind) {
	// Allocate a new node if needed
	if (root == nullptr)
		root = new Node(s[ind]);


	/*
		Check to see if we've reached the end of the string
		This algorithm works by:
			1. we have a string made up of chars

				a. if the current char is less than or greater than the current node
				   then we follow to the appropriate child and check there

				b. if the current char is equal to the current node, then it already exists along
				   that subtree and does not need to be added so we follow to the next child and
				   increment our position in the string

			2. Once we come across a nullptr we can assign the new node it's value/key which is
			   the current index in the string
	*/
	if (ind < s.length()-1) {

		if (s[ind] < root->key) {
			// Handle the case of the next char being less than the parent
			root->left = insertNode(root->left, s, ind);
		} else if (s[ind] > root->key) {
			// Handle the case of the next char being greater than the parent
			root->right = insertNode(root->right, s, ind);
		} else {
			// Handle the case of the next char being equal to the parent
			root->mid = insertNode(root->mid, s, ind+1);
		}
	} else {
		// If we are here then we reached the end of the string
		root->endOfString = true;
	}
	return root;
}

int maxDepth(Node* root) {
	if (root == nullptr) {
		return 0;
	}
	else {
		int leftDepth = maxDepth(root->left);
		int midDepth = maxDepth(root->mid);
		int rightDepth = maxDepth(root->right);

		// Use the largest value
		if (leftDepth >= midDepth && leftDepth >= rightDepth) {
			return leftDepth + 1;
		} else if (midDepth >= leftDepth && midDepth >= rightDepth) {
			return midDepth + 1;
		} else {
			return rightDepth + 1;
		}
	}
}

void traverseTST(Node* root, std::string &out) {

	if (root) {
		// traverse the left subtree
		traverseTST(root->left, out);

		// Append the current character
		out.push_back(root->key);

		// If this is the end of a valid string print
		if (root->endOfString) {
			std::cout << out << std::endl;
		}

		// traverse the mid subtree
		traverseTST(root->mid, out);

		// Remove most last character
		out.pop_back();

		// traverse the right subtree
		traverseTST(root->right, out);
	}
}

bool searchTST(Node* root, const std::string &s) {
	// handle a null tree
	if (root == nullptr)
		return false;

	// Otherwise we give ourselves a previous pointer to parent node
	Node* prev = root;

	// Then for every char in the string we recursively search the tree
	for (char c: s) {
		/*
			This while loop will search down the tree
			if root->key = c then we have found the char, we can break the loop,
			and move on to the next key
			Otherwise we iterate through the left and right children until we do find
			a match or reach the end of a tree
		*/
		while (root && root->key != c) {
			prev = root;

			// check which child we should visit
			root = c < root->key ? root->left : root->right;
		}

		/*
			the above loop is broken on one of two conditions
			either:
					a. 'c' was found and so root can now be root->mid
					b. root is now a nullptr in which case we return false
		*/
		if (root) {
			prev = root;
			root = root->mid;
		} else {
			return false;
		}
	}

	/*
		if we have looped the entire string without returning false
		then the string must exist in the tree, this is where we use prev, as
		above we have set root=root->mid which will be a nullptr if this is the end of
		the tree so prev gives us a safety net.
	*/
	return prev->endOfString;

}

// bool searchTST(Node* root, const std::string &word, int index) {
// 	if (root == nullptr) {
// 		return false;
// 	}

// 	if (index < word.length()-1) {
// 		if (word[index] < root->key) {
// 			return searchTST(root->left, word, index);
// 		} else if (word[index] > root->key) {
// 			return searchTST(root->right, word, index);
// 		} else {
// 			return searchTST(root->mid, word, index+1);
// 		}
// 	} else {
// 		return root->endOfString;
// 	}
// }