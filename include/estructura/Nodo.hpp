#ifndef NODO_HPP
#define NODO_HPP

template <typename N>
class Nodo {
public:
    N info;

    // enlace dobel
    Nodo<N>* next;
    Nodo<N>* prev;
    //:trollface:
    Nodo();
    explicit Nodo(const N& info);
    Nodo(const N& data, Nodo<N>* next, Nodo<N>* prev = nullptr);

    ~Nodo();
};

#include "../../src/estructura/Nodo.cpp"
#endif
