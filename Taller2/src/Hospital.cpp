#include "../include/Hospital.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Hospital::Hospital() : cabeza(nullptr) {
    inicializarServicios();
}
/////////////////////788+6975.8/9*853647945378.2187964512  
Hospital::~Hospital() {
    
    NodoServicio* actual = cabeza;
    while (actual != nullptr) {
        NodoServicio* aux = actual;
        actual = actual->siguiente;
        delete aux; //usar destructor  
    }
}

void Hospital::inicializarServicios() {
    std::string servicios[] = {
        "Urgencias", "Medicina General", "Cardiologia", 
        "Neurologia", "Traumatologia", "Cirugia", 
        "Pediatria", "Hospitalizacion"
    };

    NodoServicio* ultimo = nullptr;
    for (const std::string& s : servicios) {
        NodoServicio* nuevo = new NodoServicio(s);
        if (cabeza == nullptr) {
            cabeza = nuevo;
            ultimo = nuevo;
        } else {
            ultimo->siguiente = nuevo;
            ultimo = nuevo;
        }
    }
}

NodoServicio* Hospital::buscarServicio(std::string nombre) {
    NodoServicio* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombreServicio == nombre) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool Hospital::servicioValido(std::string nombre) {
    return buscarServicio(nombre) != nullptr;
}

void Hospital::cargarPacientesDesdeArchivo(std::string ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error: No se pudo abrir el archivo " << ruta << "\n";
        return;
    }

    std::string linea;
    while (std::getline(archivo, linea)) {
        std::stringstream ss(linea);
        std::string id, nombre, edadStr, servicio;
        
        if (std::getline(ss, id, ';') && std::getline(ss, nombre, ';') &&
            std::getline(ss, edadStr, ';') && std::getline(ss, servicio)) {
            
            try {
                int edad = std::stoi(edadStr);
                if (!servicioValido(servicio)) {
                    std::cerr << "Advertencia: Servicio no valido '" << servicio 
                              << "'. Paciente " << id << " omitido.\n";
                    continue;
                }
                // VALIDA diplicado
                bool duplicado = false;
                for (size_t i = 0; i < colaGlobal.size(); i++) {
                    if (colaGlobal.at(i).getId() == id) {
                        duplicado = true;
                        break;
                    }
                }
                if (duplicado) {
                    std::cerr << "Advertencia: Paciente duplicado ID " << id << " omitido.\n";
                    continue;
                }

                Paciente p(id, nombre, edad, servicio);
                colaGlobal.encolar(p); // encolat
            } catch (std::exception& e) {
                std::cerr << "Error en formato de linea: " << linea << "\n";
            }
        }
    }
    archivo.close();
}

void Hospital::atenderPacientes(int cantidad) {
    std::cout << "\n=== ATENDIENDO PACIENTES ===\n";
    for (int i = 0; i < cantidad; i++) {
        if (colaGlobal.isEmpty()) {
            std::cout << "No hay mas pacientes en espera.\n";
            break;
        }

        // obtener primero y eleminiar de lacola
        Paciente p = colaGlobal.front();
        colaGlobal.deencolar(); // popfront paar deencolar
        
        p.mostrar();

        NodoServicio* servicio = buscarServicio(p.getServicio());
        if (servicio != nullptr) {
            // Aagregar a la lista servicio
            servicio->listaPacientes->pushBack(p);
            std::cout << "Paciente enviado a " << p.getServicio() << ".\n";
            
            // guardar historial
            historial.push(p); ////////
        } else {
            std::cout << "Error critico: Servicio no encontrado. :'v\n";
        }
        std::cout << "--------------------------\n";
    }
}

void Hospital::mostrarEstadoServicios() const {
    std::cout << "\n=== ESTADO DE SERVICIOS ===\n";
    NodoServicio* actual = cabeza;
    while (actual != nullptr) {
        std::cout << "[" << actual->nombreServicio << "]: ";
        if (actual->listaPacientes->isEmpty()) {
            std::cout << "Sin pacientes. :)";
        } else {
            
            for (size_t i = 0; i < actual->listaPacientes->size(); i++) {
                std::cout << actual->listaPacientes->at(i).getId() << " ";
            }
        }
        std::cout << "\n";
        actual = actual->siguiente;
    }
}

void Hospital::mostrarHistorial() const {
    std::cout << "\n=== HISTORIAL DE ATENCIONES (Reciente a Antiguo) ===\n";
    if (historial.isEmpty()) {
        std::cout << "El historial esta vacio.\n";
        return;
    }
    // Rrecorrer pila arribaaabjo
    const Lista<Paciente>& listaHistorial = historial.getList();
    for (size_t i = 0; i < listaHistorial.size(); i++) {
        std::cout << "--------------------------\n";
        listaHistorial.at(i).mostrar();
    }
}

void Hospital::mostrarColaEspera() const {
    std::cout << "\n=== PACIENTES EN ESPERA ===\n";
    if (colaGlobal.isEmpty()) {
        std::cout << "No hay pacientes en espera. :o\n";
        return;
    }
    for (size_t i = 0; i < colaGlobal.size(); i++) {
        std::cout << (i + 1) << ". " << colaGlobal.at(i).getId() 
                  << " - " << colaGlobal.at(i).getNombre() << "\n";
    }
}
