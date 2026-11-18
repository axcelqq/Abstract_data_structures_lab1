#include "complete_binary_tree.h"

CompleteBinaryTree::CompleteBinaryTree(int cap) {
    capacity = cap;
    size = 0;
    tree = new string[capacity + 1];
}

CompleteBinaryTree::~CompleteBinaryTree() { delete[] tree; }

void CompleteBinaryTree::ensureCapacity(int needed) {
    if (needed <= capacity) return;
    while (capacity < needed) capacity *= 2;
    string* nt = new string[capacity + 1];
    for (int i = 1; i <= size; ++i) nt[i] = tree[i];
    delete[] tree;
    tree = nt;
}

void CompleteBinaryTree::insert(const string& value) {
    ensureCapacity(size + 1);
    tree[++size] = value;
}

int CompleteBinaryTree::search(const string& value) const {
    for (int i = 1; i <= size; ++i) if (tree[i] == value) return i;
    return -1;
}

bool CompleteBinaryTree::remove(const string& value) {
    int pos = search(value);
    if (pos == -1) return false;
    tree[pos] = tree[size];
    --size;
    return true;
}

bool CompleteBinaryTree::isComplete() const {
    for (int i = 1; i <= size; ++i) {
        if (2 * i <= size && tree[2 * i].empty()) return false;
        if (2 * i + 1 <= size && tree[2 * i + 1].empty()) return false;
    }
    return true;
}

void CompleteBinaryTree::print() const {
    cout << "Дерево(по уровням): [";
    for (int i = 1; i <= size; ++i) {
        if (i > 1) cout << ", ";
        cout << tree[i];
    }
    cout << "]\n";
}

void CompleteBinaryTree::printPreOrder(int index) const {
    if (index > size) return;
    cout << tree[index] << " ";
    printPreOrder(2 * index);
    printPreOrder(2 * index + 1);
}
void CompleteBinaryTree::printInOrder(int index) const {
    if (index > size) return;
    printInOrder(2 * index);
    cout << tree[index] << " ";
    printInOrder(2 * index + 1);
}
void CompleteBinaryTree::printPostOrder(int index) const {
    if (index > size) return;
    printPostOrder(2 * index);
    printPostOrder(2 * index + 1);
    cout << tree[index] << " ";
}

void CompleteBinaryTree::printPre() const  { cout << "Pre-order: [ ";  printPreOrder(1);  cout << "]\n"; }
void CompleteBinaryTree::printIn() const   { cout << "In-order: [ ";   printInOrder(1);   cout << "]\n"; }
void CompleteBinaryTree::printPost() const { cout << "Post-order: [ "; printPostOrder(1); cout << "]\n"; }

void CompleteBinaryTree::clear() { size = 0; }