#ifndef PILA_CPP
#define PILA_CPP

#include "../../include/estructura/Pila.hpp"

template <typename T>
Pila<T>::Pila() {}

template <typename T>
Pila<T>::~Pila() {
    clear();
}

template <typename T>
bool Pila<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
size_t Pila<T>::size() const {
    return list.size();
}

template <typename T>
void Pila<T>::clear() {
    list.clear();
}

template <typename T>
void Pila<T>::push(const T& info) {
    list.pushFront(info);
}

template <typename T>
void Pila<T>::pop() {
    list.popFront();
}

template <typename T>
T& Pila<T>::top() {
    return list.front();
}

template <typename T>
const T& Pila<T>::top() const {
    return list.front();
}

#endif
