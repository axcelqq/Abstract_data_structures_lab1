#include "registry.h"
#include "storage.h"
#include <iostream>
#include <cstring>
#include <string>
using namespace std;

// делит строку на слова. Возвращает количество слов.
int splitWords(const char* s, char words[][64], int maxWords) {
    int count = 0;
    int i = 0;
    while (s[i] && count < maxWords) {
        while (s[i] == ' ') i++;
        if (!s[i]) break;

        int k = 0;
        while (s[i] && s[i] != ' ' && k < 63) {
            words[count][k++] = s[i++];
        }
        words[count][k] = 0;
        count++;
    }
    return count;
}

void printHelp() {
    cout << "=== Команды ===\n";
    cout << "Массив   (M): MPUSH <имя> v | MPUSHAT <имя> i v | MDEL <имя> i | MSET <имя> i v\n";
    cout << "              MGET <имя> i | MLEN <имя> | MPRINT <имя>\n";
    cout << "Список   (F): FPUSH <имя> v | FADDH <имя> v | FDEL <имя> v | FDELH <имя> | FDELT <имя>\n";
    cout << "              FGET <имя> v | FLEN <имя> | FPRINT <имя>\n";
    cout << "Список   (L): LPUSH <имя> v | LADDH <имя> v | LDEL <имя> v | LDELH <имя> | LDELT <имя>\n";
    cout << "              LGET <имя> v | LLEN <имя> | LPRINT <имя> | LPRINTB <имя>\n";
    cout << "Стек     (S): SPUSH <имя> v | SPOP <имя> | SPEEK <имя> | SLEN <имя> | SPRINT <имя>\n";
    cout << "Очередь  (Q): QPUSH <имя> v | QPOP <имя> | QPEEK <имя> | QLEN <имя> | QPRINT <имя>\n";
    cout << "Дерево   (T): TINSERT mytree v | TGET mytree v | TCHECK mytree\n";
    cout << "              TPRE mytree | TIN mytree | TPOST mytree\n";
    cout << "Общие       : PRINT | SAVE | LOAD | HELP | EXIT\n";
}

// обработка одной команды 
// возвращаение true, если данные изменились (нужно сохранить в файл)
bool processCommand(const char* line, Registry& reg, const char* filename) {
    char w[8][64];
    int n = splitWords(line, w, 8);
    if (n == 0) return false;

    const char* cmd = w[0];
    bool changed = false;

    // M : массив 
    if (strcmp(cmd, "MPUSH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'M');
        if (e) { addAtEnd(e->arr, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "MPUSHAT") == 0 && n >= 4) {
        Entry* e = regGetOrCreate(reg, w[1], 'M');
        if (e) { addAtIndex(e->arr, stoi(w[2]), std::string(w[3])); changed = true; }
    }
    else if (strcmp(cmd, "MDEL") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'M') { removeAtIndex(e->arr, stoi(w[2])); changed = true; }
        else cout << "ERROR: array '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "MSET") == 0 && n >= 4) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'M') { replaceAtIndex(e->arr, stoi(w[2]), std::string(w[3])); changed = true; }
        else cout << "ERROR: array '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "MGET") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'M')
            cout << "M[" << w[2] << "] = " << getElement(e->arr, stoi(w[2])) << "\n";
        else cout << "ERROR: array '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "MLEN") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'M') cout << "len = " << getLength(e->arr) << "\n";
        else cout << "ERROR: array '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "MPRINT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'M') { cout << "M_" << e->name << " : "; readArray(e->arr); }
        else cout << "ERROR: array '" << w[1] << "' not found\n";
    }

    // F : односвязный
    else if (strcmp(cmd, "FPUSH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'F');
        if (e) { addTail(e->fl, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "FADDH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'F');
        if (e) { addHead(e->fl, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "FDEL") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F') { removeByValue(e->fl, std::string(w[2])); changed = true; }
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "FDELH") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F') { removeHead(e->fl); changed = true; }
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "FDELT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F') { removeTail(e->fl); changed = true; }
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "FGET") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F')
            cout << "index = " << searchByValue(e->fl, std::string(w[2])) << "\n";
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "FLEN") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F') cout << "len = " << e->fl.size << "\n";
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "FPRINT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'F') { cout << "F_" << e->name << " : "; readWithIndices(e->fl); }
        else cout << "ERROR: forward list '" << w[1] << "' not found\n";
    }

    // L : двусвязный
    else if (strcmp(cmd, "LPUSH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'L');
        if (e) { addTail(e->dl, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "LADDH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'L');
        if (e) { addHead(e->dl, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "LDEL") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') { removeByValue(e->dl, std::string(w[2])); changed = true; }
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LDELH") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') { removeHead(e->dl); changed = true; }
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LDELT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') { removeTail(e->dl); changed = true; }
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LGET") == 0 && n >= 3) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L')
            cout << "index = " << searchByValue(e->dl, std::string(w[2])) << "\n";
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LLEN") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') cout << "len = " << e->dl.size << "\n";
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LPRINT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') { cout << "L_" << e->name << " : "; readForward(e->dl); }
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "LPRINTB") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'L') { cout << "L_" << e->name << " : "; readBackward(e->dl); }
        else cout << "ERROR: doubly list '" << w[1] << "' not found\n";
    }

    // S : стек
    else if (strcmp(cmd, "SPUSH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'S');
        if (e) { push(e->st, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "SPOP") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'S') { pop(e->st); changed = true; }
        else cout << "ERROR: stack '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "SPEEK") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'S') cout << "top = " << peek(e->st) << "\n";
        else cout << "ERROR: stack '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "SLEN") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'S') cout << "len = " << e->st.size << "\n";
        else cout << "ERROR: stack '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "SPRINT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'S') { cout << "S_" << e->name << " : "; readStack(e->st); }
        else cout << "ERROR: stack '" << w[1] << "' not found\n";
    }

    //  Q : очередь
    else if (strcmp(cmd, "QPUSH") == 0 && n >= 3) {
        Entry* e = regGetOrCreate(reg, w[1], 'Q');
        if (e) { push(e->q, std::string(w[2])); changed = true; }
    }
    else if (strcmp(cmd, "QPOP") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'Q') { pop(e->q); changed = true; }
        else cout << "ERROR: queue '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "QPEEK") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'Q') cout << "front = " << frontVal(e->q) << "\n";
        else cout << "ERROR: queue '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "QLEN") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'Q') cout << "len = " << e->q.size << "\n";
        else cout << "ERROR: queue '" << w[1] << "' not found\n";
    }
    else if (strcmp(cmd, "QPRINT") == 0 && n >= 2) {
        Entry* e = regFind(reg, w[1]);
        if (e && e->type == 'Q') { cout << "Q_" << e->name << " : "; readQueue(e->q); }
        else cout << "ERROR: queue '" << w[1] << "' not found\n";
    }

    // T : полное бинарное дерево
    // 1. Добавление элемента (по таблице: TINSERT)
    else if (strcmp(cmd, "TINSERT") == 0 && n >= 2) {
        const char* name = (n >= 3) ? w[1] : "mytree";
        const char* val  = (n >= 3) ? w[2] : w[1];
        Entry* e = regGetOrCreate(reg, name, 'T');
        if (e) { e->tr.insert(std::string(val)); changed = true; }
    }
    
    // 2. Поиск/Чтение элемента (по таблице: TGET, по скриншоту методички: ISMEMBER)
    else if ((strcmp(cmd, "TGET") == 0 || strcmp(cmd, "ISMEMBER") == 0) && n >= 2) {
        const char* name = (n >= 3) ? w[1] : "mytree";
        const char* val  = (n >= 3) ? w[2] : w[1];
        Entry* e = regFind(reg, name);
        if (e && e->type == 'T') {
            // Если найден — TRUE, иначе FALSE
            bool found = (e->tr.search(std::string(val)) != -1);
            cout << (found ? "TRUE" : "FALSE") << "\n";
        }
        else cout << "ERROR: tree '" << name << "' not found\n";
    }
    
    // 3. Проверка на полноту (вместо удаления TDEL)
    else if (strcmp(cmd, "TCHECK") == 0 && n >= 1) {
        const char* name = (n >= 2) ? w[1] : "mytree";
        Entry* e = regFind(reg, name);
        if (e && e->type == 'T')
            cout << (e->tr.isComplete() ? "TRUE" : "FALSE") << "\n";
        else cout << "ERROR: tree '" << name << "' not found\n";
    }
    
    // 4. Обходы (чтение структуры)
    else if (strcmp(cmd, "TPRE") == 0 && n >= 1) {
        const char* name = (n >= 2) ? w[1] : "mytree";
        Entry* e = regFind(reg, name);
        if (e && e->type == 'T') { e->tr.printPre(); }
        else cout << "ERROR: tree '" << name << "' not found\n";
    }
    else if (strcmp(cmd, "TIN") == 0 && n >= 1) {
        const char* name = (n >= 2) ? w[1] : "mytree";
        Entry* e = regFind(reg, name);
        if (e && e->type == 'T') { e->tr.printIn(); }
        else cout << "ERROR: tree '" << name << "' not found\n";
    }
    else if (strcmp(cmd, "TPOST") == 0 && n >= 1) {
        const char* name = (n >= 2) ? w[1] : "mytree";
        Entry* e = regFind(reg, name);
        if (e && e->type == 'T') { e->tr.printPost(); }
        else cout << "ERROR: tree '" << name << "' not found\n";
    }


    // Общие 
    else if (strcmp(cmd, "PRINT") == 0) {
        Entry* e = reg.head;
        while (e) {
            if (e->type == 'M') { cout << "M_" << e->name << " : "; readArray(e->arr); }
            else if (e->type == 'F') { cout << "F_" << e->name << " : "; readWithIndices(e->fl); }
            else if (e->type == 'L') { cout << "L_" << e->name << " : "; readForward(e->dl); }
            else if (e->type == 'S') { cout << "S_" << e->name << " : "; readStack(e->st); }
            else if (e->type == 'Q') { cout << "Q_" << e->name << " : "; readQueue(e->q); }
            else if (e->type == 'T') { 
                cout << "T_" << e->name << " : "; 
                e->tr.print(); 
            }
            e = e->next;
        }
    }
    else if (strcmp(cmd, "SAVE") == 0) {
        saveRegistry(filename, reg);
        cout << "saved\n";
    }
    else if (strcmp(cmd, "LOAD") == 0) {
        regFree(reg);
        regInit(reg);
        loadRegistry(filename, reg);
        cout << "loaded\n";
    }
    else if (strcmp(cmd, "HELP") == 0) {
        printHelp();
    }
    else {
        cout << "ERROR: unknown command '" << cmd << "'\n";
    }

    return changed;
}

int main(int argc, char* argv[]) {
    std::string filename = "data.txt";
    std::string query = "";

    // Разбор аргументов командной строки
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--file") == 0 && i + 1 < argc) {
            filename = argv[++i];
        } else if (strcmp(argv[i], "--query") == 0 && i + 1 < argc) {
            query = argv[++i];
        }
    }

    Registry reg;
    regInit(reg);
    loadRegistry(filename.c_str(), reg);

    // если передан флаг --query (режим утилиты)
    if (!query.empty()) {
        processCommand(query.c_str(), reg, filename.c_str());
        saveRegistry(filename.c_str(), reg); // сохраняем изменения
        regFree(reg);
        return 0; // программа завершается сразу после одной команды
    }

    // если аргументов нет (режим интерактивной консоли)
    std::cout << "Введите HELP для списка команд, EXIT для выхода\n";
    char line[512];
    while (true) {
        std::cout << "> ";
        if (!std::cin.getline(line, sizeof(line))) break;
        if (line[0] == 0) continue;

           if (strcmp(line, "EXIT") == 0 || strcmp(line, "exit") == 0) {
            saveRegistry(filename.c_str(), reg);
            break;
        }

        bool changed = processCommand(line, reg, filename.c_str());
        if (changed) saveRegistry(filename.c_str(), reg);
    }

    regFree(reg);
    return 0;
}
