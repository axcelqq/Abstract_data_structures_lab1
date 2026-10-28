#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "avlTree.h"
#include <iostream>

int main() {
    // a. Массив
    Array arr;
    initArray(arr, 10);
    addAtEnd(arr, 10);
    addAtIndex(arr, 0, 5);
    replaceAtIndex(arr, 1, 20);
    std::cout << "Array length: " << getLength(arr) << "\n";
    std::cout << "Array: ";
    readArray(arr);
    removeAtIndex(arr, 0);
    std::cout << "Array after remove: ";
    readArray(arr);
    destroyArray(arr);

    // b. Односвязный список
    SList slist;
    initSList(slist);
    addHead(slist, 1);
    addTail(slist, 3);
    addAfterHead(slist, 2);
    addBeforeTail(slist, 25);
    std::cout << "SList forward: ";
    readForward(slist);
    std::cout << "SList with indices: ";
    readWithIndices(slist);
    removeByValue(slist, 25);
    removeHead(slist);
    std::cout << "SList after removes: ";
    readForward(slist);
    std::cout << "Search 3: " << searchByValue(slist, 3) << "\n";
    destroySList(slist);

    // c. Двусвязный список
    DList dlist;
    initDList(dlist);
    addHead(dlist, 10);
    addTail(dlist, 30);
    addAfterHead(dlist, 20);
    addBeforeTail(dlist, 25);
    std::cout << "DList forward: ";
    readForward(dlist);
    std::cout << "DList backward: ";
    readBackward(dlist);
    removeByValue(dlist, 25);
    removeTail(dlist);
    std::cout << "DList after removes: ";
    readForward(dlist);
    destroyDList(dlist);

    // d. Стек
    Stack st;
    initStack(st);
    push(st, 1);
    push(st, 2);
    push(st, 3);
    std::cout << "Stack top: " << peek(st) << "\n";
    std::cout << "Stack: ";
    readStack(st);
    pop(st);
    std::cout << "Stack after pop: ";
    readStack(st);
    destroyStack(st);

    // e. Очередь
    Queue q;
    initQueue(q);
    push(q, 1);
    push(q, 2);
    push(q, 3);
    std::cout << "Queue front: " << frontVal(q) << "\n";
    std::cout << "Queue: ";
    readQueue(q);
    pop(q);
    std::cout << "Queue after pop: ";
    readQueue(q);
    destroyQueue(q);

    // f. АВЛ-дерево
    AVLTree avl;
    initAVL(avl);
    insert(avl, 10);
    insert(avl, 20);
    insert(avl, 30);
    insert(avl, 40);
    insert(avl, 50);
    insert(avl, 25);
    std::cout << "AVL in-order: ";
    readInOrder(avl);
    AVLNode* found = search(avl, 25);
    std::cout << "Search 25: " << (found ? "found" : "not found") << "\n";
    remove(avl, 30);
    std::cout << "AVL after remove 30: ";
    readInOrder(avl);
    destroyAVL(avl);

    return 0;
}
