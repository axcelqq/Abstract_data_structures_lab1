#ifndef ARRAY_H
#define ARRAY_H
#include <string>

struct Array {
    std::string* data;
    int size;
    int capacity;
};

void initArray(Array& arr, int cap);
void addAtEnd(Array& arr, const std::string& val);     // добавление в конец массива
void addAtIndex(Array& arr, int idx, const std::string& val);      // добавление по индексу со сдвигом последующих эл-тов
std::string getElement(const Array& arr, int idx);      // получение элемента по индексу
void removeAtIndex(Array& arr, int idx);    // удаление по индексу со сдвигом последующих эл-тов
void replaceAtIndex(Array& arr, int idx, const std::string& val);      // замена значения элемента по индексу
int getLength(const Array& arr);    // получение текущего количества элементов
void readArray(const Array& arr);   // вывод
void destroyArray(Array& arr);

#endif