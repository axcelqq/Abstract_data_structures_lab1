#ifndef QUEUE_H
#define QUEUE_H
#include <string>

struct QueueNode {
    std::string data;
    QueueNode* next;
};

struct Queue {
    QueueNode* front;
    QueueNode* rear;
    int size;
};

void initQueue(Queue& q);
void push(Queue& q, const std::string& val);   // добавление в конец (push/enqueue)
void pop(Queue& q);     // удаление из начала (pop/dequeue)
std::string frontVal(const Queue& q);   // получение значения начала без удаления
void readQueue(const Queue& q);     // вывод всех элементов очереди (от начала к концу)
void destroyQueue(Queue& q);

#endif
