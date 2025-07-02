#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

#define WHITESPACE " \t\n\r"

// Struttura nodo dell'albero prefisso
typedef struct Node {
    char value;
    int number_of_childs;
    struct Node** child_nodes;
} Node;

// Struttura dell'albero prefisso
typedef struct Prefix_Tree {
    Node* root;
} Prefix_Tree;

// Crea un nuovo nodo con il valore specificato
Node* addNode(char value);

// Stampa ricorsivamente un nodo (funzione interna)
void printNodeHelper(Node* node, int depth, int* has_more_siblings);
void printNode(Node* node, int depth, int is_last);
void printTree(Prefix_Tree* tree);

// Inserisce una stringa nell'albero prefisso
int insertString(Prefix_Tree* tree, char* text);

// Inizializza un albero prefisso vuoto
Prefix_Tree* initEmptyTree();
Prefix_Tree* initTree(char* text, char* split_char);

// delete tree
bool deleteNode(Node** node);
bool deleteTree(Prefix_Tree** tree);

// lookup 
bool lookup(Prefix_Tree* tree, char* search_query);

#ifdef __cplusplus
}
#endif

#endif // PREFIX_TREE_H
