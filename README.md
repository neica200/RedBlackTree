# Red-Black Tree (C++ Implementation)

This repository contains a full implementation of a **Red-Black Tree** in C++, closely following the algorithmic principles and structure described in *Introduction to Algorithms* by Cormen, Leiserson, Rivest, and Stein (CLRS).

## Description

A **Red-Black Tree** is a self-balancing binary search tree in which each node has an extra bit for denoting the color (either red or black). This ensures the tree remains approximately balanced during insertions and deletions, and operations like search, insert, and delete take `O(log n)` time.

This implementation:
- Supports insertion and deletion with balancing.
- Implements all key rotations and fix-ups as per the CLRS textbook.
- Uses an explicit sentinel `nil` node to represent leaf nodes.
- Includes basic `search`, `insert`, and `delete` operations.

## Based on

This code is based on Chapter 13: *Red-Black Trees* from the book:

**"Introduction to Algorithms"**  
by Cormen, Leiserson, Rivest, and Stein  
(MIT Press, 3rd edition)

## Features

- Fully object-oriented C++ code.
- Maintains Red-Black Tree properties automatically.
- Custom enum-based color representation.
- Memory-managed using pointers (no STL).
- Easy to extend with additional functionality (like traversal or visualization).

## Usage

1. Clone the repository:
    ```bash
    git clone https://github.com/your-username/red-black-tree-cormen.git
    cd red-black-tree-cormen
    ```

2. Compile the code:
    ```bash
    g++ -std=c++17 -o rb_tree main.cpp
    ```

3. Run the program:
    ```bash
    ./rb_tree
    ```

> **Note:** Replace `main.cpp` with your file name if different.

## Example (Minimal Main Function)

```cpp
int main() {
    RedBlackTree tree;
    tree.Insert(10);
    tree.Insert(20);
    tree.Insert(15);

    tree.delete_node(20);

    Node* found = tree.search_key(15);
    if (found != tree.get_nil()) {
        cout << "Found key: " << found->get_key() << endl;
    }
}
