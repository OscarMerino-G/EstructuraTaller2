// archivo temporal para orden
#ifndef HOSPITAL_HPP
#define HOSPITAL_HPP

#include "clases/Paciente.hpp"
#include "estructura/Cola.hpp"
#include "estructura/Pila.hpp"
#include "estructura/Lista.hpp"
#include <string>

struct NodoServicio {
    std::string nombreServicio;
    Lista<Paciente>* listaPacientes; // lista geenrica paciente
    NodoServicio* siguiente;         

    NodoServicio(std::string nombre) 
        : nombreServicio(nombre), siguiente(nullptr) {
        listaPacientes = new Lista<Paciente>();
    }
    
    ~NodoServicio() {
        delete listaPacientes;
    }
};

class Hospital {
private:
    NodoServicio* cabeza;              //////////////////////////////////////////////////////////////
    Cola<Paciente> colaGlobal;         // FiFo lista espera 
    Pila<Paciente> historial;          // LiFo historial

    NodoServicio* buscarServicio(std::string nombre);
    bool servicioValido(std::string nombre);

public:
    Hospital();
    ~Hospital();

    void inicializarServicios();
    void cargarPacientesDesdeArchivo(std::string ruta);
    void atenderPacientes(int cantidad);
    void mostrarEstadoServicios() const;
    void mostrarHistorial() const;
    void mostrarColaEspera() const;
};

#endif
