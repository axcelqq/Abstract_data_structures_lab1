#ifndef AVL_H
#define AVL_H

// узел АВЛ-дерева: хранит ключ, высоту и указатели на левого и правого потомков
struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
};

// структура дерева: хранит указатель на корень
struct AVLTree {
    AVLNode* root;
};

void initAVL(AVLTree& tree);
void insert(AVLTree& tree, int key);    // Вставка элемента в дерево
AVLNode* search(AVLTree& tree, int key);    // Поиск элемента по ключу
void remove(AVLTree& tree, int key);    // Удаление элемента из дерева
void readInOrder(AVLTree& tree);
void destroyAVL(AVLTree& tree);

void printInOrder(AVLTree& tree);
void printPreOrder(AVLTree& tree);
void printPostOrder(AVLTree& tree);
void printLevelOrder(AVLTree& tree);

#endif
