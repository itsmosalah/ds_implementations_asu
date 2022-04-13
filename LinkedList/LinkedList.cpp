#include "LinkedList.h"
#include "assert.h"
#include <iostream>

template<typename T>
linkedList<typename T>::linkedList() {
    head = tail = nullptr;
    elements = 0;
}

template<typename T>
void linkedList<typename T>::push_back(T value) {
  
    elements++;
    node* newNode = new node;
    newNode->value = value;
    newNode->next = nullptr;

    newNode->prev = tail;

    if (tail != nullptr) {
        tail->next = newNode;
    }

    tail = newNode;

    if (head == nullptr) {
        head = newNode;
    }

    tasksStack.push({ 1 });
}

template<typename T>
void linkedList<typename T>::push_front(T value) {
    elements++;
    node* newNode = new node;
    newNode->value = value;
    newNode->prev = nullptr;

    newNode->next = head;

    if (head != nullptr) {
        head->prev = newNode;
    }

    head = newNode;


    if (tail == nullptr) {
        tail = newNode;
    }

    tasksStack.push({ 2 });
}

template<typename T>
void linkedList<typename T>::pop_back() {
    assert(tail != nullptr);

    elements--;

    node* target = tail;
    tail = target->prev;

    if (target->prev != nullptr) {
        target->prev->next = target->next; //which is null in this case
    }

    tasksStack.push({ -1, target->value });
    delete target;
}

template<typename T>
void linkedList<typename T>::pop_front() {

    assert(head != nullptr);

    elements--;

    node* target = head;
    head = target->next;

    if (target->next != nullptr) {
        target->next->prev = target->prev; //which is null in this case
    }

    tasksStack.push({ -2, target->value });
    delete target;
}

template<typename T>
void linkedList<typename T>::displayDetail() {
    std::cout << "current size: " << elements << '\n';

    node* ptr = head;
    while (ptr != nullptr) {
        ptr->prev == nullptr ? std::cout << "NULL" : std::cout << ptr->prev->value;
        std::cout << " <- " << ptr->value << " -> " ;
        ptr->next == nullptr ? std::cout << "NULL\n" : std::cout << ptr->next->value << '\n';
        ptr = ptr->next;
    }
}

template<typename T>
void linkedList<typename T>::display() {
    node* ptr = head;
    while (ptr != nullptr) {
        std::cout << ptr->value << '\n';
        ptr = ptr->next;
    }
}

template<typename T>
int linkedList<typename T>::size() {
    return elements;
}

template<typename T>
T linkedList<typename T>::front() {
    assert(head != nullptr);
    return head->value;
}
template<typename T>
T linkedList<typename T>::back() {
    assert(tail != nullptr);
    return tail->value;
}

template<typename T>
void linkedList<typename T>::undo() {
    task x = tasksStack.top();
    tasksStack.pop();

    switch (x.type) {
    case 1: {
        //undo push back
        pop_back();
        break;
    };
    case 2: {
        //undo push front
        pop_front();
        break;
    };
    case -1: {
        //undo pop back
        push_back(x.value);
        break;
    };
    case -2: {
        //undo pop front
        push_front(x.value);
    };
    default: {}
    };

    //to neglect the undo action
    tasksStack.pop();
}
