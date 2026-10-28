#ifndef REGISTRY_H
#define REGISTRY_H

#include "array.h"
#include "slist.h"
#include "dlist.h"
#include "stack.h"
#include "queue.h"
#include "avlTree.h"

struct Entry {
    char name[64];      // имя структуры, например "a1"
    char type;          // 'M','F','L','S','Q','T'
    Array arr;
    SList fl;
    DList dl;
    Stack st;
    Queue q;
    AVLTree tr;
    Entry* next;
};

struct Registry {
    Entry* head;
    int count;
};

void  regInit(Registry& r);
Entry* regFind(Registry& r, const char* name);
Entry* regCreate(Registry& r, const char* name, char type);
Entry* regGetOrCreate(Registry& r, const char* name, char type);
void  regFree(Registry& r);

#endif