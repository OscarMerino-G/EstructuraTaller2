#ifndef PERSONA_HPP
#define PERSONA_HPP

// persona hpp
#include <string>

class Persona {
protected:
    std::string nombre;
    int edad;

public:
    // constructor
    Persona(std::string n, int e) : nombre(n), edad(e) {}

    // getts
    std::string getNombre() const { return nombre; }
    int getEdad() const { return edad; }

    virtual ~Persona() {} // destructor 
};
#endif
