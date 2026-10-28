#include "stack.h"
#include <iostream>

void initStack(Stack& st) {
    st.top = nullptr;
    st.size = 0;
}

void push(Stack& st, int val) {
    StackNode* n = new StackNode{val, st.top};
    st.top = n;
    ++st.size;
}

void pop(Stack& st) {
    if (!st.top) return;
    StackNode* tmp = st.top;
    st.top = st.top->next;
    delete tmp;
    --st.size;
}

int peek(const Stack& st) {
    return (st.top) ? st.top->data : -1;
}

void readStack(const Stack& st) {
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
