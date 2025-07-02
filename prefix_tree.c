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
        
        // Print the connector and character
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

void printNode(Node* node, int depth, int is_last) {
    int has_more_siblings[100] = {0}; // Assuming max depth of 100
    printNodeHelper(node, depth, has_more_siblings);
}

void printTree(Prefix_Tree* tree) {
    if (!tree || !tree->root) {
        printf("(empty tree)\n");
        return;
    }
    
    printf("<root>\n");
    printNode(tree->root, 0, 1);
    printf("\n");
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
                break; // Importante: esci dal ciclo una volta trovato
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
        return true; // Non è un errore se è già NULL
    }

    if ((*tree)->root) {
        deleteNode(&((*tree)->root));
    }
    
    free(*tree);
    *tree = NULL;
    return true;
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
    tree->root->child_nodes = NULL; // Inizializza a NULL

    return tree;
}

Prefix_Tree* initTree(char* text, char* split_char) {
    Prefix_Tree* tree = initEmptyTree();
    
    // Crea una copia della stringa perché strtok modifica l'originale
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
        printf("Inserting word: %s\n", word);
        insertString(tree, word); // Inserisci la parola nell'albero
        word = strtok(NULL, split_char);
    }
    
    free(text_copy); // Libera la memoria della copia
    return tree;
}

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