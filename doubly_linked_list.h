#ifndef DOUBLY_LINKED_LIST_H
#define DOUBLY_LINKED_LIST_H

#include <iostream>
#include <stdexcept>

template<typename T>
class DoublyLinkedList {
private:
    class Node {
    public:
        T data;
        Node* prev;
        Node* next;
        Node(T value) : data(value), prev(nullptr), next(nullptr) {}
    };

    Node* head;
    Node* tail;
    int size;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    ~DoublyLinkedList() {
        while (head != nullptr) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }

    void push_back(T value) {
        Node* newNode = new Node(value);
        if (tail == nullptr) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
        size++;
    }

    void insert(int index, T value) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of range");
        }

        if (index == size) {
            push_back(value);
            return;
        }

        Node* newNode = new Node(value);

        if (index == 0) {
            newNode->next = head;
            if (head != nullptr) {
                head->prev = newNode;
            }
            head = newNode;
            if (tail == nullptr) {
                tail = newNode;
            }
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }

            newNode->prev = current->prev;
            newNode->next = current;
            current->prev->next = newNode;
            current->prev = newNode;
        }
        size++;
    }

    void remove(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of range");
        }

        Node* toDelete;

        if (index == 0) {
            toDelete = head;
            head = head->next;
            if (head != nullptr) {
                head->prev = nullptr;
            }
            else {
                tail = nullptr;
            }
        }
        else if (index == size - 1) {
            toDelete = tail;
            tail = tail->prev;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            else {
                head = nullptr;
            }
        }
        else {
            Node* current = head;
            for (int i = 0; i < index; i++) {
                current = current->next;
            }
            toDelete = current;
            current->prev->next = current->next;
            current->next->prev = current->prev;
        }

        delete toDelete;
        size--;
    }

    void print() const {
        Node* current = head;
        while (current != nullptr) {
            std::cout << current->data << " ";
            current = current->next;
        }
        std::cout << std::endl;
    }

    int getSize() const { return size; }

    bool isEmpty() const { return size == 0; }

    T& getFront() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return head->data;
    }

    T& getBack() const {
        if (isEmpty()) throw std::runtime_error("List is empty");
        return tail->data;
    }
};

#endif
