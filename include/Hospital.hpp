#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include "clases/Paciente.hpp"
#include "estructura/Cola.hpp"
#include "estructura/Pila.hpp"
#include "estructura/AVL.hpp"
#include "estructura/ArbolDecision.hpp"
#include <string>


// lista enlazada servicios. cada servicio funciona con su propio AVL
struct NodoServicio {
    std::string nombreServicio;
    AVLTree* avl;
    NodoServicio* siguiente;

    explicit NodoServicio(const std::string& nombre)
        : nombreServicio(nombre), avl(new AVLTree()), siguiente(nullptr) {}

    ~NodoServicio() { delete avl; }

    NodoServicio(const NodoServicio&) = delete;
    NodoServicio& operator=(const NodoServicio&) = delete;
};

class Hospital {
private:
    NodoServicio* cabeza;
    Cola<Paciente> colaGlobal;   // orden de llegada (FIFO):
    Pila<Paciente> historial;    // Ultimos atendido (LIFO)
    ArbolDecision arbol;         // clasifica a caad paciente por servicio

    NodoServicio* buscarServicio(const std::string& nombre) const;
    bool servicioValido(const std::string& nombre) const;
    bool idExiste(const std::string& id) const;   // verificar existencia en la cola en AVL

public:
    Hospital();
    ~Hospital();

    Hospital(const Hospital&) = delete;
    Hospital& operator=(const Hospital&) = delete;

    void inicializarServicios();
    void cargarPacientesDesdeArchivo(const std::string& ruta);
    void atenderPacientes(int cantidad);
    void mostrarEstadoServicios() const;
    void buscarPaciente(const std::string& termino) const;
    void menuAVL();                       // recorridos, altura y balance de un servicio
    void mostrarHistorial() const;
    void mostrarColaEspera() const;
    void mostrarArbolDecision() const;
};

#endif
