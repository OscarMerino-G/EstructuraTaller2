#ifndef COLA_CPP
#define COLA_CPP

#include "../../include/estructura/Cola.hpp"

template <typename T>
Cola<T>::Cola() {}

template <typename T>
Cola<T>::~Cola() {
    clear();
}

template <typename T>
bool Cola<T>::isEmpty() const {
    return list.isEmpty();
}

template <typename T>
size_t Cola<T>::size() const {
    return list.size();
}

template <typename T>
void Cola<T>::clear() {
    list.clear();
}

template <typename T>
void Cola<T>::encolar(const T& data) {
    list.pushBack(data);
}

template <typename T>
void Cola<T>::deencolar() {
    list.popFront();
}

template <typename T>
T& Cola<T>::front() {
    return list.front();
}

template <typename T>
const T& Cola<T>::front() const {
    return list.front();
}

template <typename T>
T& Cola<T>::back() {
    return list.back();
}

template <typename T>
const T& Cola<T>::back() const {
    return list.back();
}

template <typename T>
const T& Cola<T>::at(size_t index) const {
    return list.at(index);
}

template <typename T>
T& Cola<T>::at(size_t index) {
    return list.at(index);
}

template <typename T>
void Cola<T>::insertAt(size_t index, const T& info) {
    list.insertAt(index, info);
}

template <typename T>
void Cola<T>::removeAt(size_t index) {
    list.removeAt(index);
}

template <typename T>
LinkedList<T>& Cola<T>::getList() {
    return list;
}

template <typename T>
const LinkedList<T>& Cola<T>::getList() const {
    return list;
}

#endif
