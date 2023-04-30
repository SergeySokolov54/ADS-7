// Copyright 2022 NNTU-CS
#ifndef INCLUDE_TPQUEUE_H_
#define INCLUDE_TPQUEUE_H_
#include <iostream>
#include <string>

template<typename T>
class TPQueue {
 private:
    struct Item {
        T part;
        Item* next;
        Item* prev;
    };
    Item* head;
    Item* tail;
    TPQueue::Item* create(const T&);

 public:
    TPQueue() : head(nullptr), tail(nullptr) {}
    ~TPQueue();
    void push(const T&);
    T pop();
};

template<typename T>
typename TPQueue<T>::Item* TPQueue<T>::create(const T& value) {
    Item* item = new Item;
    item->part = value;
    item->next = item->prev = nullptr;
    return item;
}

template<typename T>
T TPQueue<T>::pop() {
    if (head == nullptr) {
        throw std::string("Empty");
    } else {
        Item* temp = head->next;
        T value = head->part;
        delete head;
        head = temp;
        return value;
    }
}

template<typename T>
void TPQueue<T>::push(const T& value) {
    if (head == nullptr) {
        head = create(value);
        tail = head;
    } else if (tail->part.prior >= value.prior) {
        tail->next = create(value);
        tail->next->prev = tail;
        tail = tail->next;
    } else if (head == tail) {
        tail->prev = create(value);
        head = tail->prev;
        head->next = tail;
    } else if (tail->part.prior < value.prior) {
        Item* temp = tail;
        while (temp != head && value.prior > temp->part.prior) {
            temp = temp->prev;
        }
        if (temp->part.prior >= value.prior) {
            Item* item = create(value);
            temp->next->prev = item;
            item->next = temp->next;
            temp->next = item;
            item->prev = temp;
        } else if (temp == head && temp->part.prior < value.prior) {
            head->prev = create(value);
            head = head->prev;
            head->next = temp;
            temp->prev = head;
        }
    }
}

template<typename T>
TPQueue<T>::~TPQueue() {
    while (head != nullptr) {
        pop();
    }
}

struct SYM {
  char ch;
  int prior;
};

#endif  // INCLUDE_TPQUEUE_H_
