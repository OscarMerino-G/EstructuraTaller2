#ifndef UTILIDADES_HPP
#define UTILIDADES_HPP

// funciones apoyo para texto
#include <cctype>
#include <cerrno>
#include <climits>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <string>

namespace util {

inline std::string trim(const std::string& s) {
    size_t ini = 0;
    while (ini < s.size() && std::isspace(static_cast<unsigned char>(s[ini]))) ++ini;
    size_t fin = s.size();
    while (fin > ini && std::isspace(static_cast<unsigned char>(s[fin - 1]))) --fin;
    return s.substr(ini, fin - ini);
}

inline std::string minusculas(std::string s) {
    for (size_t i = 0; i < s.size(); ++i)
        s[i] = static_cast<char>(std::tolower(static_cast<unsigned char>(s[i])));
    return s;
}

// convertir texto a netero. devolver false si no es entero valido
inline bool aEntero(const std::string& texto, int& salida) {
    std::string t = trim(texto);
    if (t.empty()) return false;
    char* fin = nullptr;
    errno = 0;
    long v = std::strtol(t.c_str(), &fin, 10);
    if (*fin != '\0' || errno == ERANGE || v < INT_MIN || v > INT_MAX) return false;
    salida = static_cast<int>(v);
    return true;
}

// texto a decimal
inline bool aDecimal(const std::string& texto, double& salida) {
    std::string t = trim(texto);
    if (t.empty()) return false;
    for (size_t i = 0; i < t.size(); ++i)
        if (t[i] == ',') t[i] = '.';
    char* fin = nullptr;
    errno = 0;
    double v = std::strtod(t.c_str(), &fin);
    if (*fin != '\0' || errno == ERANGE || !std::isfinite(v)) return false;
    salida = v;
    return true;
}

// lee linea completa entrada, tira false si se acaba end of line)
inline bool leerLinea(std::string& linea) {
    return static_cast<bool>(std::getline(std::cin, linea));
}

// solicite entero en rango, bucle hasta qe sea valido, tira false cuando no hay mas caracteres en mensaje
inline bool leerEnteroEnRango(const std::string& mensaje, int minimo, int maximo, int& salida) {
    std::string linea;
    while (true) {
        std::cout << mensaje;
        if (!leerLinea(linea)) return false;
        int v = 0;
        if (aEntero(linea, v) && v >= minimo && v <= maximo) {
            salida = v;
            return true;
        }
        std::cout << "Entrada invalida. Ingrese un numero entre " << minimo << " y " << maximo << ".\n";
    }
}

} 
#endif
