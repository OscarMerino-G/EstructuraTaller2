#ifndef PACIENTE_HPP
#define PACIENTE_HPP

#include "Persona.hpp"
#include <string>
#include <iostream>

// Clase derivada de Persona.
class Paciente : public Persona {
private:
    std::string id;
    double temperatura;      // °C
    int presion;             // mmHg
    int dolor;               // 0->10
    std::string tipoDolor;   // pecho, cabeza, abdomen, extremidad, otor
    bool trauma; //T F
    bool sintomasNeurologicos;
    bool requiereCirugia;
    int diasHospitalizacion;
    std::string servicio;    // vacio hasta que el arbol de decision lo asigna

public:
    Paciente();
    Paciente(const std::string& id, const std::string& nombre, int edad,
             double temperatura, int presion, int dolor, const std::string& tipoDolor,
             bool trauma, bool sintomasNeurologicos, bool requiereCirugia,
             int diasHospitalizacion);

    ~Paciente() override;

    // Getters
    const std::string& getId() const;
    double getTemperatura() const;
    int getPresion() const;
    int getDolor() const;
    const std::string& getTipoDolor() const;
    bool getTrauma() const;
    bool getSintomasNeurologicos() const;
    bool getRequiereCirugia() const;
    int getDiasHospitalizacion() const;
    const std::string& getServicio() const;

    void setServicio(const std::string& s);

    // Valida rangos. Si hay un problema devuelve false y deja el motivo en 'motivo'.
    bool esValido(std::string& motivo) const;
    static bool tipoDolorValido(const std::string& t);

    void mostrar() const;     // muestra ficha completa
    void mostrarResumen() const;  // muestra resumen de fichja con  ID

    bool operator==(const Paciente& otro) const { return id == otro.id; }
};

#endif
