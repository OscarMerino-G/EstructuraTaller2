#include "../../include/estructura/ArbolDecision.hpp"
#include <iomanip>
#include <iostream>
#include <sstream>

namespace {

const char* nombreAtributo(Atributo a) {
    switch (a) {
        case Atributo::EDAD:        return "Edad";
        case Atributo::TEMPERATURA: return "Temperatura";
        case Atributo::PRESION:     return "PresionArterial";
        case Atributo::DOLOR:       return "Dolor";
        case Atributo::TRAUMA:      return "Trauma";
        case Atributo::NEUROLOGICO: return "SintomasNeurologicos";
        case Atributo::CIRUGIA:     return "RequiereCirugia";
        case Atributo::DIAS:        return "DiasHospitalizacion";
        case Atributo::TIPO_DOLOR:  return "TipoDolor";
    }
    return "?";
}

bool esBooleano(Atributo a) {
    return a == Atributo::TRAUMA || a == Atributo::NEUROLOGICO || a == Atributo::CIRUGIA;
}

std::string formatoValor(double v) {
    std::ostringstream os;
    if (v == static_cast<long>(v)) os << static_cast<long>(v);
    else os << std::fixed << std::setprecision(1) << v;
    return os.str();
}

void agregar(std::string& salida, const std::string& texto) {
    if (!salida.empty()) salida += " | ";
    salida += texto;
}

// para leer arbol
NodoDecision* P(Atributo a, Operador o, double valor, const std::string& texto,
                const std::string& just, NodoDecision* si, NodoDecision* no) {
    NodoDecision* n = new NodoDecision(a, o, valor, texto, just);
    n->si = si;
    n->no = no;
    return n;
}

NodoDecision* H(const std::string& servicio, const std::string& just) {
    return new NodoDecision(servicio, just);
}

} 
// n
NodoDecision::NodoDecision(Atributo a, Operador o, double valor, const std::string& texto,
                           const std::string& just)
    : esHoja(false), atributo(a), operador(o), valorNumerico(valor), valorTexto(texto),
      servicio(""), justificacion(just), si(nullptr), no(nullptr) {}

NodoDecision::NodoDecision(const std::string& serv, const std::string& just)
    : esHoja(true), atributo(Atributo::EDAD), operador(Operador::IGUAL), valorNumerico(0),
      valorTexto(""), servicio(serv), justificacion(just), si(nullptr), no(nullptr) {}

std::string NodoDecision::condicion() const {
    std::string s = nombreAtributo(atributo);
    if (atributo == Atributo::TIPO_DOLOR) return s + " == " + valorTexto;
    switch (operador) {
        case Operador::MENOR:       s += " < ";  break;
        case Operador::MAYOR_IGUAL: s += " >= "; break;
        case Operador::IGUAL:       s += " == "; break;
    }
    return s + formatoValor(valorNumerico);
}

std::string NodoDecision::condicionNegada() const {
    std::string s = nombreAtributo(atributo);
    if (atributo == Atributo::TIPO_DOLOR) return s + " != " + valorTexto;
    switch (operador) {
        case Operador::MENOR:       return s + " >= " + formatoValor(valorNumerico);
        case Operador::MAYOR_IGUAL: return s + " < "  + formatoValor(valorNumerico);
        case Operador::IGUAL:
            if (esBooleano(atributo)) return s + " == " + (valorNumerico == 1 ? "0" : "1");
            return s + " != " + formatoValor(valorNumerico);
    }
    return s;
}

std::string NodoDecision::etiqueta() const {
    if (esHoja) return "[" + servicio + "]";
    return condicion() + "?";
}

bool NodoDecision::evaluar(const Paciente& p) const {
    if (atributo == Atributo::TIPO_DOLOR) return p.getTipoDolor() == valorTexto;

    double v = 0;
    switch (atributo) {
        case Atributo::EDAD:        v = p.getEdad(); break;
        case Atributo::TEMPERATURA: v = p.getTemperatura(); break;
        case Atributo::PRESION:     v = p.getPresion(); break;
        case Atributo::DOLOR:       v = p.getDolor(); break;
        case Atributo::TRAUMA:      v = p.getTrauma() ? 1 : 0; break;
        case Atributo::NEUROLOGICO: v = p.getSintomasNeurologicos() ? 1 : 0; break;
        case Atributo::CIRUGIA:     v = p.getRequiereCirugia() ? 1 : 0; break;
        case Atributo::DIAS:        v = p.getDiasHospitalizacion(); break;
        case Atributo::TIPO_DOLOR:  break; // ya se evalua el dolor 
    }
    switch (operador) {
        case Operador::MENOR:       return v < valorNumerico;
        case Operador::MAYOR_IGUAL: return v >= valorNumerico;
        case Operador::IGUAL:       return v == valorNumerico;
    }
    return false;
}


ArbolDecision::ArbolDecision() : raiz(nullptr) {
    construir();
}

ArbolDecision::~ArbolDecision() {
    destruir(raiz);
    raiz = nullptr;
}

void ArbolDecision::destruir(NodoDecision* n) {
    if (n == nullptr) return;
    destruir(n->si);
    destruir(n->no);
    delete n;
}

void ArbolDecision::construir() {
    destruir(raiz);
    raiz = nullptr;

    // para cada pregunta "si"= true, "no" = false
    raiz =
    P(Atributo::EDAD, Operador::MENOR, 14, "",
      "Menores de 14 anos se derivan siempre a Pediatria: es la unidad especializada en ese grupo etario.",
      H("Pediatria", "Paciente menor de 14 anos."),

    P(Atributo::TRAUMA, Operador::IGUAL, 1, "",
      "Un trauma activo condiciona el resto del caso, por eso se evalua antes que los sintomas generales.",
      P(Atributo::CIRUGIA, Operador::IGUAL, 1, "",
        "Con trauma, si el medico indico cirugia el paciente va a Cirugia; si no, se maneja de forma conservadora.",
        H("Cirugia", "Trauma que requiere intervencion quirurgica."),
        H("Traumatologia", "Trauma sin indicacion quirurgica.")),

    P(Atributo::NEUROLOGICO, Operador::IGUAL, 1, "",
      "Sin trauma, los sintomas neurologicos tienen prioridad diagnostica sobre el dolor o la fiebre.",
      H("Neurologia", "Sintomas neurologicos sin trauma."),

    P(Atributo::TIPO_DOLOR, Operador::IGUAL, 0, "pecho",
      "Dolor de pecho: se deriva a Cardiologia para descartar causa cardiaca.",
      H("Cardiologia", "Dolor toracico."),

    P(Atributo::TEMPERATURA, Operador::MAYOR_IGUAL, 38.5, "",
      "Fiebre alta (>= 38.5 C) es signo de gravedad y se atiende en Urgencias.",
      H("Urgencias", "Fiebre alta."),

    P(Atributo::DOLOR, Operador::MAYOR_IGUAL, 8, "",
      "Dolor intenso (>= 8 en escala 0-10) requiere atencion inmediata.",
      H("Urgencias", "Dolor intenso."),

    P(Atributo::PRESION, Operador::MAYOR_IGUAL, 180, "",
      "Presion  >= 180 mmHg se considera crisis hipertensiva.",
      H("Urgencias", "Crisis hipertensiva."),

    P(Atributo::PRESION, Operador::MENOR, 90, "",
      "Presion  < 90 mmHg se considera hipotension con riesgo de shock.",
      H("Urgencias", "Hipotension."),

    P(Atributo::CIRUGIA, Operador::IGUAL, 1, "",
      "Estable y sin urgencia, pero con indicacion quirurgica (por ejemplo cirugia programada): va a Cirugia.",
      H("Cirugia", "Cirugia indicada sin trauma ni urgencia."),

    P(Atributo::DIAS, Operador::MAYOR_IGUAL, 2, "",
      "Caso estable que se estima necesitara 2 o mas dias de internacion: se hospitaliza.",
      H("Hospitalizacion", "Internacion estimada de 2 o mas dias."),
      H("Medicina General", "Caso estable y de baja complejidad (opcion por defecto).")
    ))))))))));
}

std::string ArbolDecision::evaluar(const Paciente& p, std::string& ruta) const {
    ruta.clear();

    
    // datos invalidos o no rellena
    std::string motivo;
    if (!p.esValido(motivo)) {
        ruta = "Datos invalidos: " + motivo;
        return "";
    }
    if (raiz == nullptr) {
        ruta = "El arbol de decision no esta construido";
        return "";
    }

    const NodoDecision* n = raiz;
    while (!n->esHoja) {
        bool respuesta = n->evaluar(p);
        if (!ruta.empty()) ruta += " -> ";
        ruta += respuesta ? n->condicion() : n->condicionNegada();
        n = respuesta ? n->si : n->no;
    }
    return n->servicio;
}

void ArbolDecision::imprimir(const NodoDecision* n, int nivel, const std::string& rama) {
    if (n == nullptr) return;
    std::string sangria(static_cast<size_t>(nivel) * 3, ' ');
    if (n->esHoja) {
        std::cout << sangria << rama << "=> " << n->servicio << "   (" << n->justificacion << ")\n";
        return;
    }
    std::cout << sangria << rama << n->condicion() << "?\n";
    std::cout << sangria << "      Justificacion: " << n->justificacion << "\n";
    imprimir(n->si, nivel + 1, "[Si] ");
    imprimir(n->no, nivel + 1, "[No] ");
}

void ArbolDecision::mostrarArbol() const {
    std::cout << "\n=== ARBOL DE DECISION ===\n";
    imprimir(raiz, 0, "");
}

void ArbolDecision::preorden(const NodoDecision* n, std::string& salida) {
    if (n == nullptr) return;
    agregar(salida, n->etiqueta());
    preorden(n->si, salida);
    preorden(n->no, salida);
}

void ArbolDecision::inorden(const NodoDecision* n, std::string& salida) {
    if (n == nullptr) return;
    inorden(n->si, salida);
    agregar(salida, n->etiqueta());
    inorden(n->no, salida);
}

void ArbolDecision::postorden(const NodoDecision* n, std::string& salida) {
    if (n == nullptr) return;
    postorden(n->si, salida);
    postorden(n->no, salida);
    agregar(salida, n->etiqueta());
}

void ArbolDecision::mostrarPreorden() const {
    std::string s;
    preorden(raiz, s);
    std::cout << "\nPreorden:\n" << s << "\n";
}

void ArbolDecision::mostrarInorden() const {
    std::string s;
    inorden(raiz, s);
    std::cout << "\nInorden:\n" << s << "\n";
}

void ArbolDecision::mostrarPostorden() const {
    std::string s;
    postorden(raiz, s);
    std::cout << "\nPostorden:\n" << s << "\n";
}

int ArbolDecision::contarHojas(const NodoDecision* n, const std::string& servicio) {
    if (n == nullptr) return 0;
    if (n->esHoja) return n->servicio == servicio ? 1 : 0;
    return contarHojas(n->si, servicio) + contarHojas(n->no, servicio);
}

int ArbolDecision::contarHojas(const std::string& servicio) const {
    return contarHojas(raiz, servicio);
}
