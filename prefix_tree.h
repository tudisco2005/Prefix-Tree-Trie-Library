#ifndef PREFIX_TREE_H
#define PREFIX_TREE_H

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

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
void printNode(Node* node, int depth);

// Stampa l'albero prefisso
void printTree(Prefix_Tree* tree);

// Inserisce una stringa nell'albero prefisso
int insertString(Prefix_Tree* tree, char* text);

// Inizializza un albero prefisso vuoto
Prefix_Tree* initEmptyTree();

// delete tree
bool deleteNode(Node** node);
bool deleteTree(Prefix_Tree** tree);


#ifdef __cplusplus
}
#endif

#endif // PREFIX_TREE_H
