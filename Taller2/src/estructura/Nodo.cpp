#ifndef NODO_CPP
#define NODO_CPP

#include "../../include/estructura/Nodo.hpp"

template <typename T>
Nodo<T>::Nodo() : next(nullptr), prev(nullptr) {}

template <typename T>
Nodo<T>::Nodo(const T& info) : info(info), next(nullptr), prev(nullptr) {}

template <typename T>
Nodo<T>::Nodo(const T& info, Nodo<T>* next, Nodo<T>* prev) 
    : info(info), next(next), prev(prev) {}

template <typename T>
Nodo<T>::~Nodo() {
    // No eliminar los nodos siguientes aquí para evitar recursión infinita
    next = nullptr;
    prev = nullptr;
}

#endif
