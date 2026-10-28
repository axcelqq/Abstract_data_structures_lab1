#ifndef QUEUE_H
#define QUEUE_H

// Узел очереди: хранит данные и указатель на следующий узел
struct QueueNode {
    int data;
    QueueNode* next;
};

// Структура очереди: хранит указатели на начало (front) и конец (rear), а также размер
struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
};

void initQueue(Queue& q);
void push(Queue& q, int val);   // добавление в конец (push/enqueue)
void pop(Queue& q);     // Удаление из начала (pop/dequeue)
int frontVal(const Queue& q);   // Получение значения начала без удаления
void readQueue(const Queue& q);     // Вывод всех элементов очереди (от начала к концу)
void destroyQueue(Queue& q);

#endif
