#ifndef SLIST_H
#define SLIST_H

// Узел односвязного списка: хранит данные и указатель на следующий узел
struct SNode {
    int data;
    SNode* next;
};

struct SList {
    SNode* head;
    SNode* tail;
    int size;
};

void initSList(SList& lst);
void addHead(SList& lst, int val);  // добавление в начало (перед головой)
void addTail(SList& lst, int val);  // добавление в конец (после хвоста)
void addAfterHead(SList& lst, int val);     // добавление после головы
void addBeforeTail(SList& lst, int val);    // добавление перед хвостом
void removeHead(SList& lst);    // удаление из начала
void removeTail(SList& lst);    // удаление из конца
void removeAfterHead(SList& lst);   // удаление после головы
void removeBeforeTail(SList& lst);  // удаление перед хвостом
void removeByValue(SList& lst, int val);    // удаление первого найденного элемента по значению
int searchByValue(const SList& lst, int val);   // поиск элемента по значению (возвращает индекс или -1)
void readForward(const SList& lst);     // вывод списка в прямом порядке
void readWithIndices(const SList& lst);     // вывод списка с индексацией элементов
void destroySList(SList& lst);

#endif
