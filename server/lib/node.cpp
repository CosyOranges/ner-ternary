#include <iostream>
#include <lib/node.hpp>

namespace tree {
	// Constructor
	TernaryTree::TernaryTree()
	{
		root_ = NULL;
		tree_size = 0;
		num_of_leaves = 0;
	}

	// Destructor
	TernaryTree::~TernaryTree() {
		DeleteNode(root_);
	}

	void TernaryTree::DeleteNode(Node* node) {
		if (node) {
			DeleteNode(node->left);
			DeleteNode(node->mid);
			DeleteNode(node->right);
			delete node;
		}
	}

	// Simple Methods
	/*
		Get the number of complete strings stored in the tree.
	*/
	int TernaryTree::size() {
		return tree_size;
	}

	/*
		Get an estimate of the size of the tree in bytes.
		This is only estimate because the size of pointers will be taken to be 64bit
		therefore this gives the "worst-case" size.
		It is simply done by number_of_nodes*(char_bytes + bool_bytes + 3*64bit_pointers)
	*/
	int TernaryTree::size_bytes() {
		return tree_size * (sizeof(char) + sizeof(bool) + 3*8);
	}

	/*
		Get the number of individual nodes stored in the tree.
	*/
	int TernaryTree::leaves() {
		return num_of_leaves;
	}

	/*
		Return the length of the longest branch in the tree.
	*/
	int TernaryTree::depth() {
		return depth(root_);
	}

	// Core Methods

	/*
		Build TernaryTree from a vector of strings.
	*/
	void TernaryTree::BuildFromVec(std::vector<std::string> &keys) {
		int count = 0;
		for(std::string key : keys) {
			root_ = InsertNode(root_, key, 0);
		}
	}

	/*
		Insert a string into the TernaryTree
	*/
	void TernaryTree::Insert(const std::string &key) {
		root_ = InsertNode(root_, key, 0);
	}

	/*
		Insert a Vector of strings
	*/
	void TernaryTree::InsertVec(const std::vector<std::string> &keys) {
		for (int i=0; i<keys.size(); i++) {
			Insert(keys[i]);
		}
	}

	bool TernaryTree::Search(const std::string &key){
		return Search(root_, key, 0);
	}

	/*
		Find the longest prefix stored in the tree.
	*/
	std::string TernaryTree::LongestPrefix(const std::string &key, bool true_match, int curr_idx = 0) {
		int longest_index = 0;
		int preserve_start_of_string = curr_idx;

		// If there is no dictionary to search in we will return a "None" string
		if (root_ == nullptr) {
			return "";
		}

		// Otherwise we are now interested in whether the user wants only prefixes which are "whole strings stored in the dictionary"
		// Or if the user is happy to accept matches to prefixes of strings in the dictionary
		if (true_match) {
			// User only wants matches to COMPLETE objects stored in the dictionary.
			longest_index = LongestPrefixTrueMatch(root_, key, curr_idx, 0);
		} else {
			// User will accept matches to INCOMPLETE objects stored in the dictionary.
			longest_index = LongestPrefixAnyMatch(root_, key, curr_idx, 0);
		}

		if (longest_index > 0) {
			return key.substr(curr_idx, longest_index-curr_idx);
		} else {
			return "";
		}
	}

	/*
		Find all the keys that exist in the tree of which the input is a prefix.
	*/
	std::vector<std::string> TernaryTree::CollectKeys(std::string word) {
		Node* node = GetNode(root_, word, 0);

		std::vector<std::string> prefixes;

		if (node) {
			CollectKeys(node->mid, prefixes, word);
		}

		return prefixes;
	}

// PRIVATE METHODS

	/*
		Find the longest prefix (where the full string in the ternary tree matches).
	*/
	int TernaryTree::LongestPrefixTrueMatch(Node* node, const std::string &key, int current, int longest_index) {
		// Handle the case of current index being the end of the string
		if (current == key.length() || node == NULL) {
			// If this is the case then we return the longest matching integer.
			return longest_index;
		}
		if (key[current] < node->key) {
			// We traverse down the left branch
			return LongestPrefixTrueMatch(node->left, key, current, longest_index);
		} else if (key[current] > node->key) {
			// We traverse the right branch
			return LongestPrefixTrueMatch(node->right, key, current, longest_index);
		} else {
			// We have found a matching char because this method only values true matches, we only increment
			// the longest_index if the key is the end of a string stored in the tree
			if (node->endOfString) {
				longest_index = current+1;
			}
			// Then we move down the middle branch and increment the current index
			return LongestPrefixTrueMatch(node->mid, key, current+1, longest_index);
		}
	}

	/*
		Find the longest prefix.
	*/
	int TernaryTree::LongestPrefixAnyMatch(Node* node, const std::string &key, int current, int longest_index) {
		// Handle the case of current index being the end of the string
		if (current == key.length() - 1 || node == NULL) {
			// If this is the case then we return the longest matching integer.
			return longest_index;
		}
		if (key[current] < node->key) {
			// We traverse down the left branch
			return LongestPrefixAnyMatch(node->left, key, current, longest_index);
		} else if (key[current] > node->key) {
			// We traverse the right branch
			return LongestPrefixAnyMatch(node->right, key, current, longest_index);
		} else {
			// We have found a matching char because this method only values true matches, we only increment
			// the longest_index if the key is the end of a string stored in the tree
			longest_index = current+1;
			// Then we move down the middle branch and increment the current index
			return LongestPrefixAnyMatch(node->mid, key, current+1, longest_index);
		}
	}

	/*
		Create a new node
	*/
	Node* TernaryTree::CreateNode(char c) {
		Node *node = new Node();
		node->endOfString = false;
		node->key = c;
		node->left=nullptr;
		node->mid=nullptr;
		node->right=nullptr;
		num_of_leaves++;
		return node;
	}

	/*
		Return the length of the longest branch in the tree.
	*/
	int TernaryTree::depth(Node *node) {
		if (node == nullptr) {
			return 0;
		}
		else {
			int leftDepth = depth(node->left);
			int midDepth = depth(node->mid);
			int rightDepth = depth(node->right);

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

	/*
		Search for a key in the String.
	*/
	bool TernaryTree::Search(Node* node, const std::string &s, int ind) {
		// If we've reached the end of the string then we don't need to search
		if (node == NULL || ind == s.length()) {
			return false;
		}

		if (s[ind] < node->key) {
			return Search(node->left, s, ind);
		} else if (s[ind] > node->key) {
			return Search(node->right, s, ind);
		} else {
			if (ind == s.length()-1) {
				return node->endOfString;
			}
			return Search(node->mid, s, ind+1);
		}
	}


	/*
		Insert an individual node into the TernaryTree
	*/
	Node* TernaryTree::InsertNode(Node* root, const std::string &s, int ind) {
		// Allocate a new node if needed
		if (root == nullptr) {
			root = CreateNode(s[ind]);
		}
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
				root->left = InsertNode(root->left, s, ind);
			} else if (s[ind] > root->key) {
				// Handle the case of the next char being greater than the parent
				root->right = InsertNode(root->right, s, ind);
			} else {
				// Handle the case of the next char being equal to the parent
				root->mid = InsertNode(root->mid, s, ind+1);
			}
		} else {
			// If we are here then we reached the end of the string
			root->endOfString = true;
			tree_size++;
		}
		return root;
	}

	/*
		Same as the Search function but return a Node instead.
	*/
	Node* TernaryTree::GetNode(Node* node, std::string &key, int ind) {
		if (node == NULL || ind >= key.length()) {
			return NULL;
		}

		if (key[ind] < node->key) {
			return GetNode(node->left, key, ind);
		} else if (key[ind] > node->key) {
			return GetNode(node->right, key, ind);
		} else if (ind < key.length()-1) {
			return GetNode(node->mid, key, ind+1);
		} else {
			return node;
		}
	}

	/*
		Find all the keys that exist in the tree of which the input is a prefix.
	*/
	void TernaryTree::CollectKeys(Node* node, std::vector<std::string> &prefixes, std::string word) {
		if (!node) {
			return;
		}

		if (node->endOfString) {
			prefixes.push_back(word+node->key);
		}

		CollectKeys(node->left, prefixes, word);

		// We only want to add the current node's key to the word if we are traversing the middle
		// otherwise we will pollute the true prefix with characters that were "in the way"
		CollectKeys(node->mid, prefixes, word+node->key);
		CollectKeys(node->right, prefixes, word);

		return;
	}

	void TernaryTree::TraverseTree(Node* node, char* buffer, int depth) {

		if (node) {
			TraverseTree(node->left, buffer, depth);

			buffer[depth] = node->key;

			if (node->endOfString) {
				buffer[depth+1] = '\0';
				std::cout << buffer << std::endl;
			}

			TraverseTree(node->mid, buffer, depth+1);

			TraverseTree(node->right, buffer, depth);
		}
	}

	void TernaryTree::Print() {
		char buffer[100];

		TraverseTree(root_, buffer, 0);
	}
}
