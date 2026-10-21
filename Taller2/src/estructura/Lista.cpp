#ifndef LISTA_CPP
#define LISTA_CPP

#include "../../include/estructura/Lista.hpp"
#include <cstdlib>

template <typename T>
Lista<T>::Lista() : head(nullptr), tail(nullptr), count(0) {}

template <typename T>
Lista<T>::~Lista() {
    clear();
}

template <typename T>
bool Lista<T>::isEmpty() const {
    return count == 0;
}

template <typename T>
size_t Lista<T>::size() const {
    return count;
}

template <typename T>
void Lista<T>::clear() {
    while (!isEmpty()) {
        popFront();
    }
}

template <typename T>
T& Lista<T>::front() {
    return head->info;
}

template <typename T>
const T& Lista<T>::front() const {
    return head->info;
}

template <typename T>
T& Lista<T>::back() {
    return tail->info;
}

template <typename T>
const T& Lista<T>::back() const {
    return tail->info;
}

template <typename T>
Nodo<T>* Lista<T>::getNodoAt(size_t index) const {
    if (index >= count) return nullptr;
    
    Nodo<T>* current = head;
    for (size_t i = 0; i < index; i++) {
        current = current->next;
    }
    return current;
}

template <typename T>
T& Lista<T>::at(size_t index) {
    return getNodoAt(index)->info;
}

template <typename T>
const T& Lista<T>::at(size_t index) const {
    return getNodoAt(index)->info;
}

template <typename T>
void Lista<T>::pushFront(const T& info) {
    Nodo<T>* newNodo = new Nodo<T>(info);
    
    if (isEmpty()) {
        head = tail = newNodo;
    } else {
        newNodo->next = head;
        head->prev = newNodo;
        head = newNodo;
    }
    count++;
}

template <typename T>
void Lista<T>::pushBack(const T& info) {
    Nodo<T>* newNodo = new Nodo<T>(info);
    
    if (isEmpty()) {
        head = tail = newNodo;
    } else {
        tail->next = newNodo;
        newNodo->prev = tail;
        tail = newNodo;
    }
    count++;
}

template <typename T>
void Lista<T>::insertAt(size_t index, const T& info) {
    if (index == 0) {
        pushFront(info);
    } else if (index == count) {
        pushBack(info);
    } else if (index < count) {
        Nodo<T>* current = getNodoAt(index);
        Nodo<T>* newNodo = new Nodo<T>(info);
        
        newNodo->prev = current->prev;
        newNodo->next = current;
        current->prev->next = newNodo;
        current->prev = newNodo;
        
        count++;
    }
}

template <typename T>
void Lista<T>::popFront() {
    if (isEmpty()) return;
    
    Nodo<T>* temp = head;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        head = head->next;
        head->prev = nullptr;
    }
    
    delete temp;
    count--;
}

template <typename T>
void Lista<T>::popBack() {
    if (isEmpty()) return;
    
    Nodo<T>* temp = tail;
    
    if (head == tail) {
        head = tail = nullptr;
    } else {
        tail = tail->prev;
        tail->next = nullptr;
    }
    
    delete temp;
    count--;
}

template <typename T>
void Lista<T>::removeAt(size_t index) {
    if (index >= count) return;
    
    if (index == 0) {
        popFront();
    } else if (index == count - 1) {
        popBack();
    } else {
        Nodo<T>* current = getNodoAt(index);
        current->prev->next = current->next;
        current->next->prev = current->prev;
        delete current;
        count--;
    }
}

template <typename T>
bool Lista<T>::remove(const T& info) {
    int index = find(info);
    if (index != -1) {
        removeAt(index);
        return true;
    }
    return false;
}

template <typename T>
int Lista<T>::find(const T& info) const {
    Nodo<T>* current = head;
    int index = 0;
    
    while (current != nullptr) {
        if (current->info == info) {
            return index;
        }
        current = current->next;
        index++;
    }
    return -1;
}

template <typename T>
bool Lista<T>::contains(const T& info) const {
    return find(info) != -1;
}

template <typename T>
Nodo<T>* Lista<T>::getHead() const {
    return head;
}

template <typename T>
Nodo<T>* Lista<T>::getTail() const {
    return tail;
}
#endif
