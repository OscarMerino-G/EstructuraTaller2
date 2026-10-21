#ifndef LISTA_HPP
#define LISTA_HPP

#include "Nodo.hpp"

template <typename T>
class Lista {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    size_t count;
    
public:
	
	// constructor y destructor
    Lista();
    ~Lista();
    
    bool isEmpty() const; // cap
    size_t size() const;
    void clear();
    

    T& front(); // Acecso 
    const T& front() const;
    T& back();
    const T& back() const;
    T& at(size_t index);
    const T& at(size_t index) const;
    
    

    void pushFront(const T& data); // Insercion
    void pushBack(const T& data);
    void insertAt(size_t index, const T& data);


    void popFront(); // Eliminacion
    void popBack();
    void removeAt(size_t index);
    bool remove(const T& data);
    

    int find(const T& data) const; // Busqueda
    bool contains(const T& data) const;

    Nodo<T>* getHead() const; // Recorre la lista
    Nodo<T>* getTail() const;
    
    
private:
    Nodo<T>* getNodoEn(size_t index) const;
};
#include "../../src/estructura/Lista.cpp"
#endif
