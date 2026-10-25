#ifndef AVL_HPP
#define AVL_HPP
#include <string>
//

#include "../clases/Paciente.hpp"
#include "Lista.hpp"


//NDOO: se guarda el paciente, se usa el ID como identificador para orden
class AVLNodo {
public:
    Paciente dato;
    AVLNodo* left; //
    AVLNodo* right;
    int height;   // cuando es hoja  = 1, vacio = 0
    explicit AVLNodo(const Paciente& paciente);
};
//
class AVLTree {
private:
    AVLNodo* root;
    int total;
    std::string ultimaRotacion;  //se guarda la rotación que se aplicó en la ultima insersión del arbol  

    int height(const AVLNodo* node) const;
    int getBalance(const AVLNodo* node) const;  // izq-der
    int max(int a, int b) const;

    AVLNodo* rotateRight(AVLNodo* y);
    AVLNodo* rotateLeft(AVLNodo* x);

    AVLNodo* insert(AVLNodo* node, const Paciente& paciente, bool& insertado);

    void destroy(AVLNodo* node);
    void inorder(const AVLNodo* node, std::string& salida) const;
    void preorder(const AVLNodo* node, std::string& salida) const;//
    void postorder(const AVLNodo* node, std::string& salida) const;
    void balances(const AVLNodo* node, std::string& salida) const;
    void listar(const AVLNodo* node, std::string& salida) const;
    void buscarNombre(const AVLNodo* node, const std::string& terminoMin, Lista<Paciente>& out) const;
//
public:
    AVLTree();
    ~AVLTree();

    AVLTree(const AVLTree&) = delete;
    AVLTree& operator=(const AVLTree&) = delete;


        //Inserción por ID, devuelve falso si el ID ya existe y no modifica elarbol
    bool insert(const Paciente& paciente);


    // busqueda por id, se guarda en ruta los ID visitados, devuelve nullptr si no existe
    const Paciente* search(const std::string& id, std::string& ruta) const;


    // busqueda por nombre a través de todo el arbol
    void searchByName(const std::string& termino, Lista<Paciente>& resultados) const;


    bool isEmpty() const;
    int size() const;
//
    int getHeight() const;
    int getBalanceRoot() const;
    const std::string& getUltimaRotacion() const;

    void displayInOrder() const;
    void displayPreOrder() const;
    void displayPostOrder() const;
    void displayBalanceFactors() const;

    std::string listInOrder() const;  //devuelve lista de nombres y su id. Formato: Nombre (ID), Nombre (ID) ..
};

#endif
