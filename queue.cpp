#include "queue.h"
#include <iostream>

void initQueue(Queue& q) {
    q.front = q.rear = nullptr;
    q.size = 0;
}

void push(Queue& q, int val) {
    QueueNode* n = new QueueNode{val, nullptr};
    if (!q.rear) {
        q.front = q.rear = n; // если очередь пуста, новый узел — и начало, и конец
    } else {
        q.rear->next = n;
        q.rear = n;
    }
    ++q.size;
}

void pop(Queue& q) {
    if (!q.front) return;
    QueueNode* tmp = q.front;
    q.front = q.front->next;
    if (!q.front) q.rear = nullptr; // если очередь стала пустой, обнуляем конец
    delete tmp;
    --q.size;
}

int frontVal(const Queue& q) {
    return (q.front) ? q.front->data : -1;
}

void readQueue(const Queue& q) {
    QueueNode* cur = q.front;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << "\n";
}

void destroyQueue(Queue& q) {
    while (q.front) {
        QueueNode* tmp = q.front;
        q.front = q.front->next;
        delete tmp;
    }
    q.rear = nullptr;
    q.size = 0;
}
