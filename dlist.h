#ifndef DLIST_H
#define DLIST_H
#include <string>

struct DNode {
    std::string data;
    DNode* prev;
    DNode* next;
};

struct DList {
    DNode* head;
    DNode* tail;
    int size;
};

void initDList(DList& lst);
void addHead(DList& lst, const std::string& val);      // добавление в начало
void addTail(DList& lst, const std::string& val);      // добавление в конец
void addAfterHead(DList& lst, const std::string& val);     // добавление после головы
void addBeforeTail(DList& lst, const std::string& val);    // добавлени перед хвостом
void removeHead(DList& lst);    // удаление из начала
void removeTail(DList& lst);    // удаление из конца
void removeAfterHead(DList& lst);   // удаление после головы
void removeBeforeTail(DList& lst);  // удаление перед хвостом
void removeByValue(DList& lst, const std::string& val);    // удаление по значению
int searchByValue(const DList& lst, const std::string& val);   // поиск по значению (возвращает индекс или -1)
void readForward(const DList& lst);     // вывод списка в прямом порядке
void readBackward(const DList& lst);    // вывод списка в обратном порядке
void destroyDList(DList& lst);

#endif
