#include "stack.h"
#include <iostream>

void initStack(Stack& st) {
    st.top = nullptr;
    st.size = 0;
}

void push(Stack& st, int val) {     // добавление на вершину (push)
    StackNode* n = new StackNode{val, st.top};
    st.top = n;
    ++st.size;
}

void pop(Stack& st) {    // удаление с вершины (pop)
    if (!st.top) return;
    StackNode* tmp = st.top;
    st.top = st.top->next;
    delete tmp;
    --st.size;
}

int peek(const Stack& st) {      // получение значения вершины без удаления (peek)
    return (st.top) ? st.top->data : -1;
}

void readStack(const Stack& st) {   // вывод всех элементов стека (от вершины к низу)
    StackNode* cur = st.top;
    while (cur) {
        std::cout << cur->data << " ";
        cur = cur->next;
    }
    std::cout << "\n";
}

void destroyStack(Stack& st) {
    while (st.top) {
        StackNode* tmp = st.top;
        st.top = st.top->next;
        delete tmp;
    }
    st.size = 0;
}
