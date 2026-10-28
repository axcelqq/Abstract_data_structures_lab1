#ifndef AVL_H
#define AVL_H

// Узел АВЛ-дерева: хранит ключ, высоту и указатели на левого и правого потомков
struct AVLNode {
    int key;
    int height;
    AVLNode* left;
    AVLNode* right;
};

// Структура дерева: хранит указатель на корень
struct AVLTree {
    AVLNode* root;
};

// Инициализация пустого дерева
void initAVL(AVLTree& tree);
// Вставка элемента в дерево
void insert(AVLTree& tree, int key);
// Поиск элемента по ключу
AVLNode* search(AVLTree& tree, int key);
// Удаление элемента из дерева
void remove(AVLTree& tree, int key);
// Вывод элементов дерева в порядке обхода (in-order)
void readInOrder(AVLTree& tree);
// Полное уничтожение дерева и освобождение памяти
void destroyAVL(AVLTree& tree);

#endif
