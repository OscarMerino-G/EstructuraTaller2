#ifndef ARBOLDECISION_HPP
#define ARBOLDECISION_HPP

#include <string>
#include "../clases/Paciente.hpp"

// atributos que consulta pregunta
enum class Atributo {
    EDAD, TEMPERATURA, PRESION, DOLOR,
    TRAUMA, NEUROLOGICO, CIRUGIA, DIAS, TIPO_DOLOR
};

enum class Operador { MENOR, MAYOR_IGUAL, IGUAL };


// nodos binarios izq si- der no. nodo interno = pregunta, hojas = resultado
class NodoDecision {
public:
    bool esHoja;

    //pregunta 
    Atributo atributo;
    Operador operador;
    double valorNumerico;
    std::string valorTexto;  // solo para el tipo de dolor      

    //hoja
    std::string servicio;

    std::string justificacion;   // readme arbol

    NodoDecision* si;
    NodoDecision* no;

    NodoDecision(Atributo a, Operador o, double valor, const std::string& texto,const std::string& just);//pregunta
    NodoDecision(const std::string& servicio, const std::string& just);// r

    std::string condicion() const;         // si se cumple la condicion
    std::string condicionNegada() const;   // si no se cumple la condicion
    std::string etiqueta() const;          // pregunta y hoja ( resultado)
    bool evaluar(const Paciente& p) const; // respuesta
};


class ArbolDecision {
private:


    NodoDecision* raiz;
    static void destruir(NodoDecision* n);
    static void preorden(const NodoDecision* n, std::string& salida);
    static void inorden(const NodoDecision* n, std::string& salida);
    static void postorden(const NodoDecision* n, std::string& salida);
    static void imprimir(const NodoDecision* n, int nivel, const std::string& rama);
    static int contarHojas(const NodoDecision* n, const std::string& servicio);


public:
    ArbolDecision();
    ~ArbolDecision();

    ArbolDecision(const ArbolDecision&) = delete;
    ArbolDecision& operator=(const ArbolDecision&) = delete;


    // se construye con el criterio del grupo el arbol
    void construir();

    
    // se evalua el paciente, devuelve el servicio y se guarda en ruta el camino. Si el paciente tiene algun dato invalido se devuelve vacio y se guarda el motivo en ruta
    std::string evaluar(const Paciente& p, std::string& ruta) const;

    void mostrarArbol() const;    // estructura y justificacion de desicion
    void mostrarPreorden() const;
    void mostrarInorden() const;
    void mostrarPostorden() const;


    // cantidad de rutas que llegan a un servicio
    int contarHojas(const std::string& servicio) const;
};

#endif
