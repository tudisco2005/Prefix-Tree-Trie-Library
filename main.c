#include <stdio.h>
#include "prefix_tree.h"

int main() {
    // Inizializza l'albero
    Prefix_Tree* tree = initTree("non lo so", WHITESPACE);
    if (!tree) {
        printf("Errore nell'inizializzazione dell'albero.\n");
        return 1;
    }

    // Inserisci alcune stringhe
    printf("added: %d nodes for %s\n", insertString(tree, "cane"), "cane");
    printf("added: %d nodes for %s\n", insertString(tree, "cani"), "cani");
    printf("added: %d nodes for %s\n", insertString(tree, "casa"), "casa");
    printf("added: %d nodes for %s\n", insertString(tree, "gatto"), "gatto");
    printf("added: %d nodes for %s\n", insertString(tree, "ciao"), "ciao");

    // Stampa l'albero
    printf("Stampa dell'albero prefix dopo inserimenti:\n");
    printTree(tree);


    printf("Eliminazione albero prefix\n");
    deleteTree(&tree);
    printTree(tree);

    return 0;
}