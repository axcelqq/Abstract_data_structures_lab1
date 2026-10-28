#include "avlTree.h"
#include "queue.h"
#include <iostream>
#include <algorithm>

// получение высоты узла (0 для nullptr)
int getHeight(AVLNode* n) {
    return (n) ? n->height : 0;
}

// вычисление баланса узла (разница высот левого и правого поддеревьев)
int getBalance(AVLNode* n) {
    return (n) ? getHeight(n->left) - getHeight(n->right) : 0;
}

// обновление высоты узла на основе высот потомков
void updateHeight(AVLNode* n) {
    if (n)
        n->height = 1 + std::max(getHeight(n->left), getHeight(n->right));
}

// правый поворот вокруг узла y
AVLNode* rotateRight(AVLNode* y) {
    AVLNode* x = y->left;
    AVLNode* T2 = x->right;
    x->right = y;
    y->left = T2;
    updateHeight(y);
    updateHeight(x);
    return x;
}

// левый поворот вокруг узла x
AVLNode* rotateLeft(AVLNode* x) {
    AVLNode* y = x->right;
    AVLNode* T2 = y->left;
    y->left = x;
    x->right = T2;
    updateHeight(x);
    updateHeight(y);
    return y;
}

// балансировка узла после вставки или удаления
AVLNode* rebalance(AVLNode* n) {
    updateHeight(n);
    int bal = getBalance(n);
    if (bal > 1) {
        if (getBalance(n->left) < 0)
            n->left = rotateLeft(n->left);
        return rotateRight(n);
    }
    if (bal < -1) {
        if (getBalance(n->right) > 0)
            n->right = rotateRight(n->right);
        return rotateLeft(n);
    }
    return n;
}

// поиск узла с минимальным ключом в поддереве
AVLNode* minNode(AVLNode* n) {
    while (n && n->left)
        n = n->left;
    return n;
}

// рекурсивная вставка узла
AVLNode* insertNode(AVLNode* n, int key) {
    if (!n) return new AVLNode{key, 1, nullptr, nullptr};
    if (key < n->key)
        n->left = insertNode(n->left, key);
    else if (key > n->key)
        n->right = insertNode(n->right, key);
    else
        return n; // Ключ уже существует, ничего не делаем
    return rebalance(n);
}

// рекурсивное удаление узла
AVLNode* removeNode(AVLNode* n, int key) {
    if (!n) return nullptr;
    if (key < n->key)
        n->left = removeNode(n->left, key);
    else if (key > n->key)
        n->right = removeNode(n->right, key);
    else {
        if (!n->left || !n->right) {
            AVLNode* tmp = n->left ? n->left : n->right;
            if (!tmp) {
                delete n;
                return nullptr;
            }
            *n = *tmp; // копирование данных из единственного потомка
            delete tmp;
        } else {
            AVLNode* tmp = minNode(n->right);
            n->key = tmp->key;
            n->right = removeNode(n->right, tmp->key);
        }
    }
    return rebalance(n);
}

// рекурсивный поиск узла по ключу
AVLNode* searchNode(AVLNode* n, int key) {
    if (!n || n->key == key) return n;
    return (key < n->key) ? searchNode(n->left, key) : searchNode(n->right, key);
}

// рекурсивный обход дерева в порядке (in-order)
void inOrder(AVLNode* n) {
    if (!n) return;
    inOrder(n->left);
    std::cout << n->key << " ";
    inOrder(n->right);
}

// рекурсивное уничтожение поддерева
void destroyNode(AVLNode* n) {
    if (!n) return;
    destroyNode(n->left);
    destroyNode(n->right);
    delete n;
}

void initAVL(AVLTree& tree) {
    tree.root = nullptr;
}

void insert(AVLTree& tree, int key) {
    tree.root = insertNode(tree.root, key);
}

AVLNode* search(AVLTree& tree, int key) {
    return searchNode(tree.root, key);
}

void remove(AVLTree& tree, int key) {
    tree.root = removeNode(tree.root, key);
}

void readInOrder(AVLTree& tree) {
    inOrder(tree.root);
    std::cout << "\n";
}

void destroyAVL(AVLTree& tree) {
    destroyNode(tree.root);
    tree.root = nullptr;
}

// Симметричный (In-order): Лево -> Корень -> Право
// Выводит элементы в отсортированном порядке!
void inorder_rec(AVLNode* node) {
    if (node == nullptr) return;
    inorder_rec(node->left);
    std::cout << node->key << " ";
    inorder_rec(node->right);
}

// Прямой (Pre-order): Корень -> Лево -> Право
// Используется для копирования дерева или сохранения в файл
void preorder_rec(AVLNode* node) {
    if (node == nullptr) return;
    std::cout << node->key << " ";
    preorder_rec(node->left);
    preorder_rec(node->right);
}

// Обратный (Post-order): Лево -> Право -> Корень
// Используется для удаления дерева (сначала дети, потом родитель)
void postorder_rec(AVLNode* node) {
    if (node == nullptr) return;
    postorder_rec(node->left);
    postorder_rec(node->right);
    std::cout << node->key << " ";
}

// Функции-обертки, которые вызывает main
void printInOrder(AVLTree& tree) {
    std::cout << "InOrder:   ";
    inorder_rec(tree.root);
    std::cout << "\n";
}

void printPreOrder(AVLTree& tree) {
    std::cout << "PreOrder:  ";
    preorder_rec(tree.root);
    std::cout << "\n";
}

void printPostOrder(AVLTree& tree) {
    std::cout << "PostOrder: ";
    postorder_rec(tree.root);
    std::cout << "\n";
}

void printLevelOrder(AVLTree& tree) {
    std::cout << "LevelOrder: ";
    if (tree.root == nullptr) {
        std::cout << "(empty)\n";
        return;
    }
    AVLNode* nodes[1000]; // массив для хранения указателей
    int front = 0;
    int rear = 0;

    // Кладем корень в очередь
    nodes[rear++] = tree.root;

    while (front < rear) {
        // Достаем узел из начала очереди
        AVLNode* current = nodes[front++];
        
        // Выводим его
        std::cout << current->key << " ";

        // Кладем в конец очереди его детей
        if (current->left != nullptr) {
            nodes[rear++] = current->left;
        }
        if (current->right != nullptr) {
            nodes[rear++] = current->right;
        }
    }
    std::cout << "\n";
}
