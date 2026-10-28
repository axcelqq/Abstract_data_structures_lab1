#include "slist.h"
#include <iostream>

void initSList(SList& lst) {
    lst.head = lst.tail = nullptr;
    lst.size = 0;
}

void addHead(SList& lst, int val) {
    SNode* n = new SNode{val, lst.head};
    if (!lst.head) lst.tail = n; // если список был пуст, хвост тоже новый узел
    lst.head = n;
    ++lst.size;
}

void addTail(SList& lst, int val) {
    SNode* n = new SNode{val, nullptr};
    if (!lst.head) {
        lst.head = lst.tail = n; // если список пуст, голова и хвост совпадают
    } else {
        lst.tail->next = n;
        lst.tail = n;
    }
    ++lst.size;
}

void addAfterHead(SList& lst, int val) {
    if (!lst.head || !lst.head->next) {
        addTail(lst, val); // если после головы нет элемента или список пуст, добавляем в конец
        return;
    }
    SNode* n = new SNode{val, lst.head->next};
    lst.head->next = n;
    ++lst.size;
}

void addBeforeTail(SList& lst, int val) {
    if (!lst.head || lst.head == lst.tail) {
        addHead(lst, val); // если список пуст или содержит один элемент, добавляем в начало
        return;
    }
    SNode* cur = lst.head;
    while (cur->next != lst.tail && cur->next)
        cur = cur->next;
    SNode* n = new SNode{val, lst.tail};
    cur->next = n;
    ++lst.size;
}

void removeHead(SList& lst) {
    if (!lst.head) return;
    SNode* tmp = lst.head;
    lst.head = lst.head->next;
    if (!lst.head) lst.tail = nullptr; // если список стал пустым, обнуляем хвост
    delete tmp;
    --lst.size;
}

void removeTail(SList& lst) {
    if (!lst.head) return;
    if (lst.head == lst.tail) {
        delete lst.head;
        lst.head = lst.tail = nullptr;
        --lst.size;
        return;
    }
    SNode* cur = lst.head;
    while (cur->next != lst.tail)
        cur = cur->next;
    delete lst.tail;
    lst.tail = cur;
    lst.tail->next = nullptr;
    --lst.size;
}

void removeAfterHead(SList& lst) {
    if (!lst.head || !lst.head->next) return;
    SNode* tmp = lst.head->next;
    lst.head->next = tmp->next;
    if (tmp == lst.tail) lst.tail = lst.head; // если удаляли последний элемент, обновляем хвост
    delete tmp;
    --lst.size;
}

void removeBeforeTail(SList& lst) {
    if (!lst.head || lst.head == lst.tail || lst.head->next == lst.tail) {
        removeHead(lst); // если удаляемый элемент — голова или список слишком мал, удаляем голову
        return;
    }
    SNode* cur = lst.head;
    while (cur->next != lst.tail && cur->next->next != lst.tail)
        cur = cur->next;
    SNode* tmp = cur->next;
    cur->next = lst.tail;
    delete tmp;
    --lst.size;
}

void removeByValue(SList& lst, int val) {
    if (!lst.head) return;
    if (lst.head->data == val) {
        removeHead(lst);
        return;
    }
    SNode* cur = lst.head;
    while (cur->next && cur->next->data != val)
        cur = cur->next;
    if (!cur->next) return;
    SNode* tmp = cur->next;
    cur->next = tmp->next;
    if (tmp == lst.tail) lst.tail = cur; // если удаляли хвост, обновляем указатель
    delete tmp;
    --lst.size;
}

int searchByValue(const SList& lst, int val) {
    SNode* cur = lst.head;
    int idx = 0;
    while (cur) {
        if (cur->data == val) return idx;
        cur = cur->next;
        ++idx;
    }
    return -1;
}

void readForward(const SList& lst) {
    SNode* cur = lst.head;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << "\n";
}

void readWithIndices(const SList& lst) {
    SNode* cur = lst.head;
    int idx = 0;
    while (cur) {
        std::cout << "[" << idx << "]=" << cur->data << " ";
        cur = cur->next;
        ++idx;
    }
    std::cout << "\n";
}

void destroySList(SList& lst) {
    while (lst.head) {
        SNode* tmp = lst.head;
        lst.head = lst.head->next;
        delete tmp;
    }
    lst.tail = nullptr;
    lst.size = 0;
}
