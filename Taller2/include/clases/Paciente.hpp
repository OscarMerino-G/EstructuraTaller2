#ifndef PACIENTE_HPP
#define PACIENTE_HPP
// paciente hpp
#include "Persona.hpp" 
#include <string>
#include <iostream>

// Clase Derivada
class Paciente : public Persona {
private:
    std::string id;
    std::string servicioDestino;

public:
    // Constructors
    Paciente();
    Paciente(std::string id, std::string nombre, int edad, std::string servicio);
    
    // Destructor
    ~Paciente() override;

    // Getts
    std::string getId() const;
    std::string getServicio() const;
    
    void mostrar() const;
};

#endif
