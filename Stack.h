#pragma once
#include "AllHeaders.h"

template <typename T>
class Node {
public:
    T data;
    Node* next;
    Node(T& value) : data(value), next(nullptr) {}
};
template <typename T>
class Stack {
public:
    Stack() : head(nullptr), stackSize(0) {}
    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push( T& value) {
        Node<T>* newNode = new Node<T>(value);
        newNode->next = head;
        head = newNode;
        stackSize++;
    }

    void pop() {
        if (empty()) {
            return;
        }
        Node<T>* oldHead = head;
        head = head->next;
        delete oldHead;
        stackSize--;
    }

    T& top() {
        if (empty()) {
            return head->data; 
        }
        return head->data;
    }

    const T& top() const {
        if (empty()) {
            return head->data; 
        }
        return head->data;
    }

    bool empty() const {
        return head == nullptr;
    }

    int size() const {
        return stackSize;
    }

private:
    Node<T>* head; 
    int stackSize; 
};
