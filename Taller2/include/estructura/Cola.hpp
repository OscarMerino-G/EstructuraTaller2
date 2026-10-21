#ifndef COLA_HPP
#define COLA_HPP

#include "LinkedList.hpp"

template <typename T>
class Cola {
private:
    Lista<T> list;
    
public:
    Cola();
    ~Cola();
    
    bool isEmpty() const;
    size_t size() const;
    void clear();
    
    void encolar(const T& data);
    void deencolar();
    T& front();
    const T& front() const;
    T& back();
    const T& back() const;
    
    
    T& at(size_t index);
    const T& at(size_t index) const;
    void insertAt(size_t index, const T& data); // Inserta el elemento en X posicion
    void removeAt(size_t index); // Elimina el elemento en la posicon X
    LinkedList<T>& getList();
    const LinkedList<T>& getList() const;
};

#include "../../src/estructura/Cola.cpp"
#endif
