#include "dlist.h"
#include <iostream>

void initDList(DList& lst) {
    lst.head = lst.tail = nullptr;
    lst.size = 0;
}

void addHead(DList& lst, int val) {      // добавление в начало
    DNode* n = new DNode{val, nullptr, lst.head};
    if (lst.head) lst.head->prev = n;
    else lst.tail = n;      // если список был пуст, хвост тоже новый узел
    lst.head = n;
    ++lst.size;
}

void addTail(DList& lst, int val) {     // добавление в конец
    DNode* n = new DNode{val, lst.tail, nullptr};
    if (lst.tail) lst.tail->next = n;
    else lst.head = n;      // если список был пуст, голова тоже новый узел
    lst.tail = n;
    ++lst.size;
}

void addAfterHead(DList& lst, int val) {    // добавление после головы
    if (!lst.head || !lst.head->next) {
        addTail(lst, val);      // если после головы нет элемента или список пуст, добавляем в конец
        return;
    }
    DNode* n = new DNode{val, lst.head, lst.head->next};
    lst.head->next->prev = n;
    lst.head->next = n;
    ++lst.size;
}

void addBeforeTail(DList& lst, int val) {       // добавлени перед хвостом
    if (!lst.head || lst.head == lst.tail) {
        addHead(lst, val);      // если список пуст или содержит один элемент, добавляем в начало
        return;
    }
    DNode* n = new DNode{val, lst.tail->prev, lst.tail};
    lst.tail->prev->next = n;
    lst.tail->prev = n;
    ++lst.size;
}

void removeHead(DList& lst) {   // удаление из начала
    if (!lst.head) return;
    DNode* tmp = lst.head;
    lst.head = lst.head->next;
    if (lst.head) lst.head->prev = nullptr;
    else lst.tail = nullptr;    // если список стал пустым, обнуляем хвост
    delete tmp;
    --lst.size;
}

void removeTail(DList& lst) {   // удаление из конца
    if (!lst.tail) return;
    DNode* tmp = lst.tail;
    lst.tail = lst.tail->prev;
    if (lst.tail) lst.tail->next = nullptr;
    else lst.head = nullptr;    // если список стал пустым, обнуляем голову
    delete tmp;
    --lst.size;
}

void removeAfterHead(DList& lst) {
    if (!lst.head || !lst.head->next) return;
    DNode* tmp = lst.head->next;
    lst.head->next = tmp->next;
    if (tmp->next) tmp->next->prev = lst.head;
    else lst.tail = lst.head;   // если удаляли последний элемент, обновляем хвост
    delete tmp;
    --lst.size;
}

void removeBeforeTail(DList& lst) {     // удаление перед хвостом
    if (!lst.tail || !lst.tail->prev) {
        removeHead(lst);    // если удаляемый элемент — голова или список слишком мал, удаляем голову
        return;
    }
    DNode* tmp = lst.tail->prev;
    lst.tail->prev = tmp->prev;
    if (tmp->prev) tmp->prev->next = lst.tail;
    else lst.head = lst.tail;   // если удаляли голову, обновляем голову
    delete tmp;
    --lst.size;
}

void removeByValue(DList& lst, int val) {    // удаление по значению
    DNode* cur = lst.head;
    while (cur && cur->data != val)
        cur = cur->next;
    if (!cur) return;
    if (cur->prev) cur->prev->next = cur->next;
    else lst.head = cur->next;      // если удаляли голову, обновляем голову
    if (cur->next) cur->next->prev = cur->prev;
    else lst.tail = cur->prev;      // если удаляли хвост, обновляем хвост
    delete cur;
    --lst.size;
}

int searchByValue(const DList& lst, int val) {  // поиск по значению
    DNode* cur = lst.head;
    int idx = 0;
    while (cur) {
        if (cur->data == val) return idx;
        cur = cur->next;
        ++idx;
    }
    return -1;
}

void readForward(const DList& lst) {    // вывод списка в прямом порядке
    DNode* cur = lst.head;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << "\n";
}

void readBackward(const DList& lst) {   // вывод списка в обратном порядке
    DNode* cur = lst.tail;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->prev;
    }
    std::cout << "\n";
}

void destroyDList(DList& lst) {
    while (lst.head) {
        DNode* tmp = lst.head;
        lst.head = lst.head->next;
        delete tmp;
    }
    lst.tail = nullptr;
    lst.size = 0;
}
