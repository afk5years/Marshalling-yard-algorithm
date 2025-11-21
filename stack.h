#ifndef STACK_H
#define STACK_H

#include "doubly_linked_list.h"
#include <stdexcept>


template<typename T>
class Stack {
private:
    DoublyLinkedList<T> list;

public:
    void push(T value) {
        list.push_back(value);
    }

    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        T value = list.getBack();
        list.remove(list.getSize() - 1);
        return value;
    }

    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty");
        }
        return list.getBack();
    }

    bool isEmpty() const {
        return list.isEmpty();
    }

    int size() const {
        return list.getSize();
    }

    void clear() {
        while (!list.isEmpty()) {
            list.remove(0);
        }
    }
    void print() const {
        list.print();
    }
};

#endif