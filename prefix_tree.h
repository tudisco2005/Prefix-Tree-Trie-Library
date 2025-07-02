#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WHITESPACE " \t\n\r"

// Structure representing a node of the prefix tree (trie)
// Each node contains a character, the number of children, and an array of pointers to child nodes.
typedef struct Node {
    char value; // Character stored in the node
    int number_of_childs; // Number of children of the node
    struct Node** child_nodes; // Array of pointers to child nodes
} Node;

// Structure representing the prefix tree itself
// Contains a pointer to the root node.
typedef struct Prefix_Tree {
    Node* root; // Root node of the tree
} Prefix_Tree;

// Creates a new node with the specified value.
// Returns a pointer to the newly allocated node.
Node* addNode(char value);

// Helper function for recursively printing a node and its children.
// Should not be used directly by the user.
void printNodeHelper(Node* node, int depth, int* has_more_siblings);

// Prints a node and its children recursively, with indentation.
void printNode(Node* node, int depth);

// Prints the entire prefix tree starting from the root.
void printTree(Prefix_Tree* tree);

// Inserts a string into the prefix tree.
// Returns the number of new nodes created during the insertion.
int insertString(Prefix_Tree* tree, char* text);

// Initializes an empty prefix tree (only root without children).
// Returns a pointer to the created tree.
Prefix_Tree* initEmptyTree();

// Initializes a prefix tree and inserts strings separated by split_char.
// Returns a pointer to the created tree.
Prefix_Tree* initTree(char* text, char* split_char);

// Recursively deallocates a node and all its children.
// Returns true if the deletion was successful.
bool deleteNode(Node** node);

// Deallocates the entire prefix tree and sets the pointer to NULL.
// Returns true if the deletion was successful.
bool deleteTree(Prefix_Tree** tree);

// Searches for a string in the prefix tree.
// Returns true if the string is present, false otherwise.
bool lookup(Prefix_Tree* tree, char* search_query);

#ifdef __cplusplus
}
#endif

#endif // PREFIX_TREE_H
