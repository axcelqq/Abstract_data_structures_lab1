#include "array.h"
#include <iostream>
#include <fstream>

void initArray(Array& arr, int cap) {
    arr.capacity = cap;
    arr.size = 0;
    arr.data = new int[cap];
}

void addAtEnd(Array& arr, int val) {    // добавление в конец
    // проверка на переполнение перед добавлением
    if (arr.size >= arr.capacity) return;
    arr.data[arr.size++] = val;
}

void addAtIndex(Array& arr, int idx, int val) {      // добавление по индексу со сдвигом последующих эл-тов
    // проверка корректности индекса и наличия свободного места
    if (idx < 0 || idx > arr.size || arr.size >= arr.capacity) return;
    // сдвиг элементов вправо для освобождения места
    for (int i = arr.size; i > idx; --i)
        arr.data[i] = arr.data[i - 1];
    arr.data[idx] = val;
    ++arr.size;
}

int getElement(const Array& arr, int idx) {
    // безопасное получение элемента с проверкой границ
    return (idx >= 0 && idx < arr.size) ? arr.data[idx] : -1;
}

void removeAtIndex(Array& arr, int idx) {    // удаление по индексу со сдвигом последующих эл-тов
    // проверка корректности индекса
    if (idx < 0 || idx >= arr.size) return;
    // сдвиг элементов влево для заполнения пробела
    for (int i = idx; i < arr.size - 1; ++i)
        arr.data[i] = arr.data[i + 1];
    --arr.size;
}

void replaceAtIndex(Array& arr, int idx, int val) {
    // замена значения при корректном индексе
    if (idx >= 0 && idx < arr.size)
        arr.data[idx] = val;
}

int getLength(const Array& arr) {
    return arr.size;
}

void readArray(const Array& arr) {
    // последовательный вывод элементов
    for (int i = 0; i < arr.size; ++i)
        std::cout << arr.data[i] << " ";
    std::cout << "\n";
}


void destroyArray(Array& arr) {
    delete[] arr.data;
    arr.data = nullptr;
    arr.size = 0;
    arr.capacity = 0;
}
