#pragma once
#include <string>
#include <vector>
/*
 * A ternary tree each node can have at most 3 children nodes
 * these nodes are distingished as left, mid, and right child.
 *
 * Terms:
 * 1. Directed Edge:
 * 	The link from a parent to a child.
 * 2. Root:
 * 	The node with no parent (also the entry point into the tree).
 * 3. Leaf Node:
 * 	This is a child node with no children itself (can be thought of as the end of
 * 	a branch).
 * 4. Parent Node:
 * 	The "previous" node to the current node.
 * 5. Child Node:
 * 	The "next" node to the current node.
 * 6. Depth:
 * 	The number or length of nodes between the root and a particular node.
 * 7. Height:
 * 	 Length of the path from the root to the deepest node in the tree.
 * 8. Sibling:
 * 	Nodes which share the same parent.
 *
 * Common Operations:
 * 1. Insertion
 * 	a. External Nodes:
 * 		This involves "appending" a node to the branch such that it has a parent
 * 		but no children nodes.
 * 	b. Internal Nodes:
 * 		This is more complex as the node is being inserted inbetween a parent
 * 		and a child node, meaning that the inserted node is the new child of the
 * 		original parent node and the original child is now the child of the new
 * 		node.
 * 2. Deletion
 * 	a. External Nodes:
 * 		An external node is simple to delete as it has no children and the
 * 		parents will just point to a 'null'.
 * 	b. Internal Nodes:
 * 		Follow the insertion above but in reverse, the deleted node is removed
 * 		and it's child is now the child of the parent of the deleted node
*/
// struct Node {
// 	char data;
// 	unsigned endOfString: 1;
// 	struct Node *left, *mid, *right;
// };

/*
 * A ternary tree each node can have at most 3 children nodes
 * these nodes are distingished as left, mid, and right child.
 *
 * Terms:
 * 1. Directed Edge:
 * 	The link from a parent to a child.
 * 2. Root:
 * 	The node with no parent (also the entry point into the tree).
 * 3. Leaf Node:
 * 	This is a child node with no children itself (can be thought of as the end of
 * 	a branch).
 * 4. Parent Node:
 * 	The "previous" node to the current node.
 * 5. Child Node:
 * 	The "next" node to the current node.
 * 6. Depth:
 * 	The number or length of nodes between the root and a particular node.
 * 7. Height:
 * 	 Length of the path from the root to the deepest node in the tree.
 * 8. Sibling:
 * 	Nodes which share the same parent.
 *
 * Common Operations:
 * 1. Insertion
 * 	a. External Nodes:
 * 		This involves "appending" a node to the branch such that it has a parent
 * 		but no children nodes.
 * 	b. Internal Nodes:
 * 		This is more complex as the node is being inserted inbetween a parent
 * 		and a child node, meaning that the inserted node is the new child of the
 * 		original parent node and the original child is now the child of the new
 * 		node.
 * 2. Deletion
 * 	a. External Nodes:
 * 		An external node is simple to delete as it has no children and the
 * 		parents will just point to a 'null'.
 * 	b. Internal Nodes:
 * 		Follow the insertion above but in reverse, the deleted node is removed
 * 		and it's child is now the child of the parent of the deleted node
*/

/*
	The node for a TST.
*/
struct Node {
	// It's data
	char key;

	// The "branches" to child nodes
	Node* left;
	Node* right;
	Node* mid;

	// Is this node the end of a string?
	bool endOfString;

	// Constructor to initialise the value of the node...
	// Done for ease of use can also exclude this and then creation of a new node would be
	// Node* example = new Node;
	// example->key = data;
	Node(char x);
};

Node* buildTST(std::vector<std::string> &str);
Node* insertNode(Node* root, const std::string &s, int ind);
void traverseTST(Node* root, std::string &out);
bool searchTST(Node* root, const std::string &s);
