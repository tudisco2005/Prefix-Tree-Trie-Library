#include <stdio.h>
#include "prefix_tree.h"

int main() {
    // Initialize the tree
    Prefix_Tree* tree = initTree("I don't know what to enter", WHITESPACE);
    if (!tree) {
        printf("Error initializing the tree.\n");
        return 1;
    }

    // Insert some strings
    printf("\nSingle insertions:\n");
    printf("added: %d nodes for \"%s\"\n", insertString(tree, "dog"), "dog");
    printf("added: %d nodes for \"%s\"\n", insertString(tree, "dogs"), "dogs");
    printf("added: %d nodes for \"%s\"\n", insertString(tree, "house"), "house");
    printf("added: %d nodes for \"%s\"\n", insertString(tree, "cat"), "cat");
    printf("added: %d nodes for \"%s\"\n", insertString(tree, "hello"), "hello");

    // Print the tree
    printf("\nPrefix tree after insertions:\n");
    printTree(tree);

    // Search
    printf("\nSearch:\n");
    printf(" - \"%s\" \t result: %s\n", "house", lookup(tree, "house") ? "True" : "False");
    printf(" - \"%s\" \t result: %s\n", "cat", lookup(tree, "cat") ? "True" : "False");
    printf(" - \"%s\" \t result: %s\n", "cats", lookup(tree, "cats") ? "True" : "False");
    printf(" - \"%s\" \t result: %s\n", "dog", lookup(tree, "dog") ? "True" : "False");
    printf(" - \"%s\" \t result: %s\n", "know", lookup(tree, "know") ? "True" : "False");
    printf(" - \"%s\" \t result: %s\n", "kitten", lookup(tree, "kitten") ? "True" : "False");

    // Deletion
    printf("\nDeleting prefix tree\n");
    deleteTree(&tree);
    printTree(tree);

    return 0;
}