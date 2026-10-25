#include "../../include/estructura/AVL.hpp"
#include "../../include/Utilidades.hpp"
#include <iostream>
// AVL CPP
namespace {

std::string etiqueta(const Paciente& p) {
    return p.getId() + " (" + p.getNombre() + ")";
}

void agregar(std::string& salida, const std::string& texto) {
    if (!salida.empty()) salida += " -> ";
    salida += texto;
}

} // 

AVLNodo::AVLNodo(const Paciente& paciente)
    : dato(paciente), left(nullptr), right(nullptr), height(1) {}

AVLTree::AVLTree() : root(nullptr), total(0), ultimaRotacion("Ninguna") {}

AVLTree::~AVLTree() {
    destroy(root);
    root = nullptr;
}

int AVLTree::max(int a, int b) const {
    return (a > b) ? a : b;
}

int AVLTree::height(const AVLNodo* node) const {
    return (node == nullptr) ? 0 : node->height;
}

int AVLTree::getBalance(const AVLNodo* node) const {
    return (node == nullptr) ? 0 : height(node->left) - height(node->right);
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

AVLNodo* AVLTree::insert(AVLNodo* node, const Paciente& paciente, bool& insertado) {
    if (node == nullptr) {
        insertado = true;
        return new AVLNodo(paciente);
    }

    const std::string& id = paciente.getId();
    int cmp = id.compare(node->dato.getId());

    if (cmp < 0) {
        node->left = insert(node->left, paciente, insertado);
    } else if (cmp > 0) {
        node->right = insert(node->right, paciente, insertado);
    } else {
        insertado = false;   // si ID duplicado no se modifica
        return node;
    }

    node->height = 1 + max(height(node->left), height(node->right));
    int balance = getBalance(node);

    // rotacion simple der
    if (balance > 1 && id < node->left->dato.getId()) {
        ultimaRotacion = "Rotacion simple a la derecha (caso izquierda-izquierda)";
        return rotateRight(node);
    }
    // rotacion simple izq 
    if (balance < -1 && id > node->right->dato.getId()) {
        ultimaRotacion = "Rotacion simple a la izquierda (caso derecha-derecha)";
        return rotateLeft(node);
    }
    // rotacion doble izq der
    if (balance > 1 && id > node->left->dato.getId()) {
        ultimaRotacion = "Rotacion doble izquierda-derecha";
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    // rotacion doble der izq
    if (balance < -1 && id < node->right->dato.getId()) {
        ultimaRotacion = "Rotacion doble derecha-izquierda";
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    return node;
}

bool AVLTree::insert(const Paciente& paciente) {
    ultimaRotacion = "Ninguna";
    bool insertado = false;
    root = insert(root, paciente, insertado);
    if (insertado) ++total;
    return insertado;
}

const Paciente* AVLTree::search(const std::string& id, std::string& ruta) const {
    ruta.clear();
    const AVLNodo* actual = root;
    while (actual != nullptr) {
        agregar(ruta, actual->dato.getId());
        int cmp = id.compare(actual->dato.getId());
        if (cmp == 0) return &actual->dato;
        actual = (cmp < 0) ? actual->left : actual->right;
    }
    return nullptr;
}

void AVLTree::buscarNombre(const AVLNodo* node, const std::string& terminoMin,
                           Lista<Paciente>& out) const {
    if (node == nullptr) return;
    buscarNombre(node->left, terminoMin, out);
    if (util::minusculas(node->dato.getNombre()).find(terminoMin) != std::string::npos)
        out.pushBack(node->dato);
    buscarNombre(node->right, terminoMin, out);
}

void AVLTree::searchByName(const std::string& termino, Lista<Paciente>& resultados) const {
    std::string t = util::minusculas(util::trim(termino));
    if (t.empty()) return;
    buscarNombre(root, t, resultados);
}

bool AVLTree::isEmpty() const { return root == nullptr; }
int AVLTree::size() const { return total; }
int AVLTree::getHeight() const { return height(root); }
int AVLTree::getBalanceRoot() const { return getBalance(root); }
const std::string& AVLTree::getUltimaRotacion() const { return ultimaRotacion; }

void AVLTree::inorder(const AVLNodo* node, std::string& salida) const {
    if (node == nullptr) return;
    inorder(node->left, salida);
    agregar(salida, etiqueta(node->dato));
    inorder(node->right, salida);
}

void AVLTree::preorder(const AVLNodo* node, std::string& salida) const {
    if (node == nullptr) return;
    agregar(salida, etiqueta(node->dato));
    preorder(node->left, salida);
    preorder(node->right, salida);
}

void AVLTree::postorder(const AVLNodo* node, std::string& salida) const {
    if (node == nullptr) return;
    postorder(node->left, salida);
    postorder(node->right, salida);
    agregar(salida, etiqueta(node->dato));
}

void AVLTree::balances(const AVLNodo* node, std::string& salida) const {
    if (node == nullptr) return;
    balances(node->left, salida);
    salida += "  " + etiqueta(node->dato) + ": altura " + std::to_string(node->height) +
              ", factor de balance " + std::to_string(getBalance(node)) + "\n";
    balances(node->right, salida);
}

void AVLTree::listar(const AVLNodo* node, std::string& salida) const {
    if (node == nullptr) return;
    listar(node->left, salida);
    if (!salida.empty()) salida += ", ";
    salida += node->dato.getNombre() + " (" + node->dato.getId() + ")";
    listar(node->right, salida);
}

void AVLTree::displayInOrder() const {
    std::string s;
    inorder(root, s);
    std::cout << "Inorden: " << (s.empty() ? "(arbol vacio)" : s) << "\n";
}

void AVLTree::displayPreOrder() const {
    std::string s;
    preorder(root, s);
    std::cout << "Preorden: " << (s.empty() ? "(arbol vacio)" : s) << "\n";
}

void AVLTree::displayPostOrder() const {
    std::string s;
    postorder(root, s);
    std::cout << "Postorden: " << (s.empty() ? "(arbol vacio)" : s) << "\n";
}

void AVLTree::displayBalanceFactors() const {
    if (root == nullptr) {
        std::cout << "(arbol vacio)\n";
        return;
    }
    std::string s;
    balances(root, s);
    std::cout << "Factor de balance por nodo (inorden):\n" << s;
    std::cout << "Factor de balance de la raiz: " << getBalance(root) << "\n";
}

std::string AVLTree::listInOrder() const {
    std::string s;
    listar(root, s);
    return s;
}

void AVLTree::destroy(AVLNodo* node) {
    if (node == nullptr) return;
    destroy(node->left);
    destroy(node->right);
    delete node;
}
