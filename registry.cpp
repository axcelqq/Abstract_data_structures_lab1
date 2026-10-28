#include "registry.h"
#include <cstring>
#include <iostream>
using namespace std;

void regInit(Registry& r) {
    r.head = nullptr;
    r.count = 0;
}

Entry* regFind(Registry& r, const char* name) {
    Entry* cur = r.head;
    while (cur) {
        if (strcmp(cur->name, name) == 0) return cur;
        cur = cur->next;
    }
    return nullptr;
}

Entry* regCreate(Registry& r, const char* name, char type) {
    Entry* e = new Entry;
    strncpy(e->name, name, 63);
    e->name[63] = 0;
    e->type = type;

    initArray(e->arr, 100);
    initSList(e->fl);
    initDList(e->dl);
    initStack(e->st);
    initQueue(e->q);
    initAVL(e->tr);

    e->next = r.head;    // вставляем в начало — проще всего
    r.head = e;
    r.count++;
    return e;
}

Entry* regGetOrCreate(Registry& r, const char* name, char type) {
    Entry* e = regFind(r, name);
    if (e) {
        if (e->type != type) {
            cout << "ERROR: name '" << name
                 << "' already used for another type\n";
            return nullptr;
        }
        return e;
    }
    return regCreate(r, name, type);
}

void regFree(Registry& r) {
    Entry* cur = r.head;
    while (cur) {
        Entry* nxt = cur->next;
        destroyArray(cur->arr);
        destroySList(cur->fl);
        destroyDList(cur->dl);
        destroyStack(cur->st);
        destroyQueue(cur->q);
        destroyAVL(cur->tr);
        delete cur;
        cur = nxt;
    }
    r.head = nullptr;
    r.count = 0;
}