#include "Paciente.hpp"

// Constructor defautl
Paciente::Paciente() : Persona("", 0), id(""), servicioDestino("") {}

// Constructor 
Paciente::Paciente(std::string _id, std::string _nombre, int _edad, std::string _servicio)
    : Persona(_nombre, _edad), id(_id), servicioDestino(_servicio) {}

Paciente::~Paciente() {
    // Destructr
}

std::string Paciente::getId() const {
    return id;
}

std::string Paciente::getServicio() const {
    return servicioDestino;
}

void Paciente::mostrar() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Edad: " << edad << "\n";
    std::cout << "Servicio: " << servicioDestino << "\n";
}
