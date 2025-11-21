#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <iostream>
#include <stdexcept>

template<typename T>
class DynamicArray {
private:
    T* data;
    int capacity;
    int currentSize;

    void resize() {
        capacity = capacity == 0 ? 1 : capacity * 2;
        T* newData = new T[capacity];
        for (int i = 0; i < currentSize; i++) {
            newData[i] = data[i];
        }
        delete[] data;
        data = newData;
    }

public:
    DynamicArray() : data(nullptr), capacity(0), currentSize(0) {}

    ~DynamicArray() {
        delete[] data;
    }

    void push_back(T value) {
        if (currentSize >= capacity) {
            resize();
        }
        data[currentSize++] = value;
    }

    void insert(int index, T value) {
        if (index < 0 || index > currentSize) {
            throw std::out_of_range("Index out of range");
        }

        if (currentSize >= capacity) {
            resize();
        }

        for (int i = currentSize; i > index; i--) {
            data[i] = data[i - 1];
        }
        data[index] = value;
        currentSize++;
    }

    void remove(int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }

        for (int i = index; i < currentSize - 1; i++) {
            data[i] = data[i + 1];
        }
        currentSize--;
    }

    T& operator[](int index) {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    const T& operator[](int index) const {
        if (index < 0 || index >= currentSize) {
            throw std::out_of_range("Index out of range");
        }
        return data[index];
    }

    void print() const {
        for (int i = 0; i < currentSize; i++) {
            std::cout << data[i] << " ";
        }
        std::cout << std::endl;
    }

    int getSize() const { return currentSize; }

    bool isEmpty() const { return currentSize == 0; }
};

#endif