#ifndef AVL_HPP
#define AVL_HPP

#include <string>
#include "../clases/Paciente.hpp"
#include "Lista.hpp"

class AVLNodo {
public:
    std::string pacienteId;

    AVLNodo* left;
    AVLNodo* right;
    int height;

    AVLNodo(Paciente* paciente);
};

class AVLTree {
private:
    AVLNodo* root;

    int height(AVLNodo* node);
    int getBalance(AVLNodo* node);
    int max(int a, int b);

    AVLNodo* rotateRight(AVLNodo* y);
    AVLNodo* rotateLeft(AVLNodo* x);

    AVLNodo* insert(AVLNodo* node, Paciente* paciente);
    AVLNodo* search(AVLNodo* node, const std::string& id);

    void destroy(AVLNodo* node);
    void inorder(AVLNodo* node);

public:
    AVLTree();
    ~AVLTree();

    void insert(Paciente* paciente);
    AVLNodo* search(const std::string& id);

    void displayInOrder();
};

#endif
