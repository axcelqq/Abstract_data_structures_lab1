#ifndef STACK_H
#define STACK_H
#include <string>

struct StackNode {
    std::string data;
    StackNode* next;
};

struct Stack {
    StackNode* top;
    int size;
};

void initStack(Stack& st);
void push(Stack& st, const std::string& val);  // добавление на вершину (push)
void pop(Stack& st);    // удаление с вершины (pop)
std::string peek(const Stack& st);  // получение значения вершины без удаления (peek)
void readStack(const Stack& st);    // вывод всех элементов стека (от вершины к низу)
void destroyStack(Stack& st);

#endif
