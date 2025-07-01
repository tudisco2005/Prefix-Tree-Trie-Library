#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

typedef struct Node Node;
typedef struct Prefix_Tree Prefix_Tree;

struct Node {
    char value;
    int number_of_childs;
    Node** child_nodes; 
};

struct Prefix_Tree {
    Node* root;
};


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

void printNode(Node* node, int depth) {
    if (!node) return;
    for (int i = 0; i < node->number_of_childs; i++) {
        for (int d = 0; d < depth; d++) printf("    ");
        printf("|->'%c'\n", node->child_nodes[i]->value);
        printNode(node->child_nodes[i], depth + 1);
    }
}

void printTree(Prefix_Tree* tree) {
    if (!tree || !tree->root) {
        printf("(empty tree)\n");
        return;
    }
    printf("root\n");
    printNode(tree->root, 1);
}

// return the number of new nodes added
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
    }
    
    int new_nodes_counter = 0;
    Node* root = tree->root;

    while (text[str_index] != '\0') {
        bool found = false;
        //search if the first letter is already present for the first node
        for (int i = 0; i<root->number_of_childs; i++) {
            if (root->child_nodes[i]->value == text[str_index]) {
                // letter is alredy present
                found = true;
                str_index += 1; 
                root = root->child_nodes[i];
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

    return tree;
}

// Prefix_Tree* initTree(char* text, char* split_char) {
    //Prefix_Tree* tree = initEmptyTree()
    // split the text in to array of strings based on the split_char
//}

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
    if (!tree || !(*tree) || !(*tree)->root) {
        perror("the tree is not valid for deletion (NULL value)");
        return false;
    }

    deleteNode(&((*tree)->root));
    free(*tree);
    *tree = NULL;
    return true;
}