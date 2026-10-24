#ifndef LISTA_HPP
#define LISTA_HPP

#include <cstddef>
#include "Nodo.hpp"

template <typename T>
class Lista {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    size_t count;

    Nodo<T>* getNodoAt(size_t index) const;

public:
    // constructor y destructor
    Lista();
    ~Lista();

    Lista(const Lista&) = delete;
    Lista& operator=(const Lista&) = delete;

    bool isEmpty() const; 
    size_t size() const;
    void clear();

    T& front(); //// usar para acceder a la lista°
    const T& front() const;
    T& back();
    const T& back() const;
    T& at(size_t index);
    const T& at(size_t index) const;

    void pushFront(const T& data); // insersion
    void pushBack(const T& data);
    void insertAt(size_t index, const T& data);

    void popFront(); // eliminiacion
    void popBack();
    void removeAt(size_t index);
    bool remove(const T& data);

    int find(const T& data) const; // busqueda
    bool contains(const T& data) const;

    Nodo<T>* getHead() const; // 
    Nodo<T>* getTail() const;
};

#include "../../src/estructura/Lista.cpp"
#endif
