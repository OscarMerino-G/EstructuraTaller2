#ifndef PILA_HPP
#define PILA_HPP

#include "Lista.hpp"

template <typename T>
class Pila {
private:
    Lista<T> list;
    
public:
    Pila();
    ~Pila();
    
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    void push(const T& info);
    void pop();
    T& top();
    const T& top() const;
    const Lista<T>& getList() const { return list; }
};

#include "../../src/estructura/Pila.cpp"
#endif
