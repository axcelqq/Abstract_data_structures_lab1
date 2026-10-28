#include "storage.h"
#include <fstream>
#include <cstring>
#include <iostream>
using namespace std;

static const char* prefixOf(char t) {
    if (t == 'M') return "M_";
    if (t == 'F') return "F_";
    if (t == 'L') return "L_";
    if (t == 'S') return "S_";
    if (t == 'Q') return "Q_";
    return "T_";
}

void saveRegistry(const char* filename, Registry& r) {
    ofstream f(filename);
    if (!f) { cout << "ERROR: cannot save\n"; return; }

    Entry* cur = r.head;
    while (cur) {
        f << prefixOf(cur->type) << cur->name << " : ";

        bool first = true;
        if (cur->type == 'M') {
            for (int i = 0; i < cur->arr.size; i++) {
                if (!first) f << ",";
                f << cur->arr.data[i];
                first = false;
            }
        }
        else if (cur->type == 'F') {
            for (SNode* n = cur->fl.head; n; n = n->next) {
                if (!first) f << ",";
                f << n->data;
                first = false;
            }
        }
        else if (cur->type == 'L') {
            for (DNode* n = cur->dl.head; n; n = n->next) {
                if (!first) f << ",";
                f << n->data;
                first = false;
            }
        }
        else if (cur->type == 'S') {
            // сохраняем снизу вверх — чтобы при чтении push восстановил порядок
            int cnt = cur->st.size;
            int* buf = new int[cnt > 0 ? cnt : 1];
            StackNode* p = cur->st.top;
            for (int i = cnt - 1; i >= 0; i--) {
                buf[i] = p->data;
                p = p->next;
            }
            for (int i = 0; i < cnt; i++) {
                if (!first) f << ",";
                f << buf[i];
                first = false;
            }
            delete[] buf;
        }
        else if (cur->type == 'Q') {
            for (QueueNode* n = cur->q.front; n; n = n->next) {
                if (!first) f << ",";
                f << n->data;
                first = false;
            }
        }
        else if (cur->type == 'T') {
            // обходим дерево в прямом порядке (pre-order) и пишем ключи
            AVLNode* stack[1000];
            int sp = 0;
            if (cur->tr.root) stack[sp++] = cur->tr.root;
            while (sp > 0) {
                AVLNode* n = stack[--sp];
                if (!first) f << ",";
                f << n->key;
                first = false;
                if (n->right) stack[sp++] = n->right;
                if (n->left)  stack[sp++] = n->left;
            }
        }
        f << "\n";
        cur = cur->next;
    }
    f.close();
}

// превращает "a,b,c" в массив строк. Возвращает число строк.
static int splitByComma(const char* s, char items[][32], int maxItems) {
    int count = 0;
    int pos = 0;
    int len = (int)strlen(s);

    while (pos <= len && count < maxItems) {
        int k = 0;
        while (pos < len && s[pos] != ',' && k < 31) {
            items[count][k++] = s[pos++];
        }
        items[count][k] = 0;
        count++;
        if (pos < len && s[pos] == ',') pos++;
        else break;
    }
    return count;
}

static int toInt(const char* s) {
    int v = 0, i = 0, sign = 1;
    if (s[i] == '-') { sign = -1; i++; }
    while (s[i] >= '0' && s[i] <= '9') {
        v = v * 10 + (s[i] - '0');
        i++;
    }
    return v * sign;
}

void loadRegistry(const char* filename, Registry& r) {
    ifstream f(filename);
    if (!f) return;

    char line[4096];
    while (f.getline(line, sizeof(line))) {
        if (strlen(line) == 0) continue;

        // ищем ":"
        int colon = -1;
        for (int i = 0; line[i]; i++) {
            if (line[i] == ':') { colon = i; break; }
        }
        if (colon < 0) continue;

        // левая часть: "M_имя"
        char left[128];
        int k = 0;
        for (int i = 0; i < colon && line[i] != ' '; i++) {
            if (k < 127) left[k++] = line[i];
        }
        left[k] = 0;
        if (k < 3 || left[1] != '_') continue;

        char type = left[0];
        const char* name = left + 2;

        Entry* e = regCreate(r, name, type);

        // правая часть: "1,2,3"
        char items[1000][32];
        int n = splitByComma(line + colon + 1, items, 1000);

        for (int i = 0; i < n; i++) {
            // убираем возможный пробел в начале
            char* s = items[i];
            while (*s == ' ') s++;
            if (*s == 0) continue;

            int v = toInt(s);
            if (type == 'M') addAtEnd(e->arr, v);
            else if (type == 'F') addTail(e->fl, v);
            else if (type == 'L') addTail(e->dl, v);
            else if (type == 'S') push(e->st, v);
            else if (type == 'Q') push(e->q, v);
            else if (type == 'T') insert(e->tr, v);
        }
    }
    f.close();
}