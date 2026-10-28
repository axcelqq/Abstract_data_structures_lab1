#ifndef STACK_H
#define STACK_H

// Узел стека: хранит данные и указатель на следующий узел
struct StackNode {
    int data;
    StackNode* next;
};

// Структура стека: хранит указатель на вершину и размер
struct Stack {
    StackNode* top;
    int size;
};

void initStack(Stack& st);
void push(Stack& st, int val);  // добавление на вершину (push)
void pop(Stack& st);    // удаление с вершины (pop)
int peek(const Stack& st);  // получение значения вершины без удаления (peek)
void readStack(const Stack& st);    // вывод всех элементов стека (от вершины к низу)
void destroyStack(Stack& st);

#endif
