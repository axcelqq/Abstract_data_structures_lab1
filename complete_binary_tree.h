#ifndef COMPLETE_BINARY_TREE_H
#define COMPLETE_BINARY_TREE_H

#include <iostream>
#include <string>

using namespace std;

struct CompleteBinaryTree {
    string* tree;
    int size;
    int capacity;

    CompleteBinaryTree(int cap = 4);
    ~CompleteBinaryTree();

    void ensureCapacity(int needed);
    void insert(const string& value);
    int  search(const string& value) const;
    bool remove(const string& value);
    bool isComplete() const;

    void print() const;
    void printPreOrder(int index) const;
    void printInOrder(int index) const;
    void printPostOrder(int index) const;
    void printPre() const;
    void printIn() const;
    void printPost() const;
    void clear();

    int getSize() const { return size; }
    string getElement(int index) const { return tree[index]; }
};

#endif