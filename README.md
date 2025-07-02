# Basic Prefix Tree (Trie) Library

This project provides a simple and efficient implementation of a prefix tree (trie) in C. The library allows you to store, search, and manage collections of strings with shared prefixes, making it ideal for applications such as autocomplete, spell checking, and dictionary management.

## Features
- Insert strings into the prefix tree
- Search for strings (lookup)
- Print the tree structure
- Initialize an empty tree or from a list of words
- Proper memory management (deletion of nodes and tree)

## Files
- `prefix_tree.h` — Header file with all public data structures and function declarations
- `prefix_tree.c` — Implementation of the prefix tree library
- `main.c` — Example usage and test file
- `makefile` — For easy compilation

## How to Use in Your Project
1. **Copy the files** `prefix_tree.h` and `prefix_tree.c` into your project directory.
2. **Include the header** in your source file:
   ```c
   #include "prefix_tree.h"
   ```
3. **Link the implementation** when compiling. For example, if your main file is `myapp.c`:
   ```sh
   gcc myapp.c prefix_tree.c -o myapp
   ```
4. **Use the API** to create and manipulate prefix trees. Example:
   ```c
   Prefix_Tree* tree = initEmptyTree();

   insertString(tree, "hello");

   if (lookup(tree, "hello")) {
       printf("Found!\n");
   }

   deleteTree(&tree);
   ```

## How to Compile
This project includes a `makefile` for convenience. To build the example program:

```sh
make
```

This will produce an executable (usually named `main` or `main.exe` on Windows) in the project directory.

To clean up compiled files:
```sh
make clean
```

## Example Usage
See `main.c` for a complete example of how to use the prefix tree library.

## License
This project is licensed under the Creative Commons Attribution-NonCommercial 4.0 International (CC BY-NC 4.0).

You are free to share and adapt the code for non-commercial purposes, provided that you give appropriate credit. Commercial use is **not permitted**.

Full license text: https://creativecommons.org/licenses/by-nc/4.0/legalcode