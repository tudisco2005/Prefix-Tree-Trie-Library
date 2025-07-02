#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_DEPTH  100

// Definition of main data structures (Node and Prefix_Tree)
typedef struct Node Node;
typedef struct Prefix_Tree Prefix_Tree;

// Structure representing a node of the prefix tree (trie)
struct Node {
    char value; // Character stored in the node
    int number_of_childs; // Number of children of the node
    Node** child_nodes; // Array of pointers to child nodes
};

// Structure representing the prefix tree
struct Prefix_Tree {
    Node* root; // Root node of the tree
};

// Helper function for recursively printing a node and its children
// Prints the tree visually, showing the hierarchical structure
void printNodeHelper(Node* node, int depth, int* has_more_siblings) {
    if (!node) return;
    for (int i = 0; i < node->number_of_childs; i++) {
        // Print indentation for current depth
        for (int d = 0; d < depth; d++) {
            if (has_more_siblings[d]) {
                printf(" |   ");
            } else {
                printf("     ");
            }
        }
        // Print the connector and character of the node
        printf(" +-- '%c'\n", node->child_nodes[i]->value);
        // Update the has_more_siblings array for the next depth level
        has_more_siblings[depth] = (i < node->number_of_childs - 1);
        // Recursively print child nodes
        printNodeHelper(node->child_nodes[i], depth + 1, has_more_siblings);
        // Add vertical line between siblings at the same depth (except after the last one)
        if (i < node->number_of_childs - 1) {
            for (int d = 0; d < depth; d++) {
                if (has_more_siblings[d]) {
                    printf(" |   ");
                } else {
                    printf("     ");
                }
            }
            printf(" |\n");
        }
    }
}

// Print a node and its children with indentation
void printNode(Node* node, int depth) {
    int has_more_siblings[MAX_DEPTH] = {0}; 
    printNodeHelper(node, depth, has_more_siblings);
}

// Print the entire prefix tree starting from the root
void printTree(Prefix_Tree* tree) {
    if (!tree || !tree->root) {
        printf("(empty tree)\n");
        return;
    }
    printf("<root>\n");
    printNode(tree->root, 0);
    printf("\n");
}

// Create and initialize a new node with the specified character
Node* addNode(char value) {
    Node* newNode = NULL;
    if(!(newNode = (Node*) malloc(sizeof(Node)))) {
        perror("Errror allocating space for a new node");
        exit(1);
    }
    newNode->value = value;
    newNode->number_of_childs = 0;
    newNode->child_nodes = NULL;
    return newNode;
}

// Insert a string into the prefix tree
// Returns the number of new nodes created
int insertString(Prefix_Tree* tree, char* text) {
    if (!tree) {
        perror("Tree is not valid (not allocated or NULL)");
        return 0;
    }
    if (!tree->root) {
        perror("Tree root node is not valid (not allocated or NULL)");
        return 0;
    }
    int str_size = 0;
    int str_index = 0;
    if (!text || (str_size = strlen(text)) == 0) {
        perror("The entering new string is not valid (not allocated or \"\")");
        return 0;
    }
    int new_nodes_counter = 0;
    Node* root = tree->root;
    while (text[str_index] != '\0') {
        bool found = false;
        //search if the first letter is already present for the first node
        for (int i = 0; i < root->number_of_childs; i++) {
            if (root->child_nodes[i]->value == text[str_index]) {
                // letter is already present
                found = true;
                str_index += 1; 
                root = root->child_nodes[i];
                break; // Important: exit the loop once found
            }
        }
        if(!found) {
            // not found
            root->number_of_childs += 1;
            if (root->number_of_childs == 1) {
                root->child_nodes = (Node**) malloc(sizeof(Node*) * root->number_of_childs);
            } else {
                root->child_nodes = (Node**) realloc(root->child_nodes, sizeof(Node*) * root->number_of_childs);
            }
            if (!root->child_nodes) {
                perror("Error allocating space for children nodes array");
                exit(1);
            }
            root->child_nodes[root->number_of_childs - 1] = addNode(text[str_index]);
            str_index += 1;
            new_nodes_counter += 1;
            root = root->child_nodes[root->number_of_childs - 1];
        }
    }
    return new_nodes_counter;
}

// Recursively deallocate a node and all its children
bool deleteNode(Node** node) {
    if (!(*node)) return true;
    for (int i = 0; i < (*node)->number_of_childs; i++) {
        deleteNode(&((*node)->child_nodes[i]));
    }
    free((*node)->child_nodes);
    free(*node);
    *node = NULL;
    return true;
}

// return true if the deletion completed without problems
bool deleteTree(Prefix_Tree** tree) {
    if (!tree || !(*tree)) {
        return true; // Not an error if already NULL
    }
    if ((*tree)->root) {
        deleteNode(&((*tree)->root));
    }
    free(*tree);
    *tree = NULL;
    return true;
}

// Initialize an empty prefix tree (only root without children)
Prefix_Tree* initEmptyTree() {
    Prefix_Tree* tree = NULL;
    if (!(tree = (Prefix_Tree*) malloc(sizeof(Prefix_Tree)))) {
        perror("Error allocating memory for the tree stucture");
        exit(1);
    }
    tree->root = NULL;
    if(!(tree->root = (Node*) malloc(sizeof(Node)))) {
        perror("Error allocating memory for the root node");
        free(tree);
        exit(1);
    }
    // the root node has no value
    tree->root->value = '\0';
    tree->root->number_of_childs = 0;
    tree->root->child_nodes = NULL; // Initialize to NULL
    return tree;
}

// Initialize a prefix tree and insert strings separated by split_char
Prefix_Tree* initTree(char* text, char* split_char) {
    Prefix_Tree* tree = initEmptyTree();
    // Create a copy of the string because strtok modifies the original
    char* text_copy = malloc(strlen(text) + 1);
    if (!text_copy) {
        perror("Error allocating memory for text copy");
        deleteTree(&tree);
        return NULL;
    }
    strcpy(text_copy, text);
    // split the text into array of strings based on the split_char
    char* word = strtok(text_copy, split_char);
    while (word != NULL) {
        //printf("Inserting word: %s\n", word);
        insertString(tree, word); // Insert the word into the tree
        word = strtok(NULL, split_char);
    }
    free(text_copy); // Free the memory of the copy
    return tree;
}

// Search for a string in the prefix tree
// Returns true if the string is present, false otherwise
bool lookup(Prefix_Tree* tree, char* search_query) {
    if (!tree) {
        perror("Tree is not valid (not allocated or NULL)");
        return false;
    }
    if (!tree->root) {
        perror("Tree root node is not valid (not allocated or NULL)");
        return false;
    }
    int str_size = 0;
    int str_index = 0;
    if (!search_query || (str_size = strlen(search_query)) == 0) {
        perror("The search query is not valid (not allocated or \"\")");
        return false;
    }
    Node* root = tree->root;
    bool found = false;
    while (search_query[str_index] != '\0') {
        found = false;
        for (int i = 0; i < root->number_of_childs; i++) {
            if (root->child_nodes[i]->value == search_query[str_index]) {
                str_index += 1;
                found = true;
                root = root->child_nodes[i];
                break;
            }
        }
        if (!found) return false;
    }
    return true;
}