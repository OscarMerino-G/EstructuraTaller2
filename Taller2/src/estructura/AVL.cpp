#include "../../include/estructura/AVL.hpp"
#include <iostream>
// AVL.cpp
AVLNodo::AVLNodo(Paciente* paciente) {
	id = paciente->getId();
	nombre = paciente->getNombre();
	servicioDestino = paciente->getServicio();
    edad = song->getEdad();
}

AVLTree::AVLTree() {
    root = nullptr;
}

AVLTree::~AVLTree() {
    destroy(root);
}

int AVLTree::max(int a, int b) {
    return (a > b) ? a : b;
}

int AVLTree::height(AVLNodo* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

int AVLTree::getBalance(AVLNodo* node) {
    if (node == nullptr) {
        return 0;
    }
    return height(node->left) - height(node->right);
}

AVLNodo* AVLTree::rotateRight(AVLNodo* y) {
    AVLNodo* x = y->left;
    AVLNodo* temp = x->right;
    x->right = y;
    y->left = temp;
    y->height = 1 + max(height(y->left), height(y->right));
    x->height = 1 + max(height(x->left), height(x->right));
    return x;
}

AVLNodo* AVLTree::rotateLeft(AVLNodo* x) {
    AVLNodo* y = x->right;
    AVLNodo* temp = y->left;
    y->left = x;
    x->right = temp;
    x->height = 1 + max(height(x->left), height(x->right));
    y->height = 1 + max(height(y->left), height(y->right));
    return y;
}

AVLNodo* AVLTree::insert(AVLNodo* node, Paciente* paciente) {
    if (node == nullptr) {
        return new AVLNodo(paciente);
    }

    std::string pacienteID = paciente->getId();

    if (pacienteID < node->id) {
        node->left = insert(node->left, paciente);
    }
    else if (pacienteID > node->id) {
        node->right = insert(node->right, paciente);
    }


    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    if (balance > 1 && pacienteID < node->left->id) {
        return rotateRight(node);
    }
    if (balance < -1 && pacienteID > node->right->id) {
        return rotateLeft(node);
    }
    if (balance > 1 && pacienteID > node->left->id) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    if (balance < -1 && pacienteID < node->right->id) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

void AVLTree::insert(Paciente* paciente) {
    if (paciente == nullptr) {
        return;
    }
    root = insert(root, paciente);
}

AVLNodo* AVLTree::search(AVLNodo* node, const std::string& id) {
    if (node == nullptr) {
        return nullptr;
    }

    if (id == node->id) {
        return node;
    }

    if (id < node->id) {
        return search(node->left, id);
    }

    return search(node->right, id);
}

AVLNodo* AVLTree::search(const std::string& id) {
    return search(root, id);
}

void AVLTree::inorder(AVLNodo* node) {
    if (node == nullptr) {
        return;
    }

    inorder(node->left);


    inorder(node->right);
}

void AVLTree::displayInOrder() {
    inorder(root);
}

void AVLTree::destroy(AVLNodo* node) {
    if (node == nullptr) {
        return;
    }
    destroy(node->left);
    destroy(node->right);
    delete node;
}