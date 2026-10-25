#include "../../include/clases/Paciente.hpp"
#include <iomanip>
#include <sstream>

namespace {
std::string formatoTemperatura(double t) {
    std::ostringstream os;
    os << std::fixed << std::setprecision(1) << t;
    return os.str();
}
const char* siNo(bool b) { return b ? "Si" : "No"; }
}

Paciente::Paciente()
    : Persona("", 0), id(""), temperatura(0.0), presion(0), dolor(0), tipoDolor(""),
      trauma(false), sintomasNeurologicos(false), requiereCirugia(false),
      diasHospitalizacion(0), servicio("") {}

Paciente::Paciente(const std::string& _id, const std::string& _nombre, int _edad,
                   double _temperatura, int _presion, int _dolor, const std::string& _tipoDolor,
                   bool _trauma, bool _neuro, bool _cirugia, int _dias)
    : Persona(_nombre, _edad), id(_id), temperatura(_temperatura), presion(_presion),
      dolor(_dolor), tipoDolor(_tipoDolor), trauma(_trauma), sintomasNeurologicos(_neuro),
      requiereCirugia(_cirugia), diasHospitalizacion(_dias), servicio("") {}

Paciente::~Paciente() {}

const std::string& Paciente::getId() const { return id; }
double Paciente::getTemperatura() const { return temperatura; }
int Paciente::getPresion() const { return presion; }
int Paciente::getDolor() const { return dolor; }
const std::string& Paciente::getTipoDolor() const { return tipoDolor; }
bool Paciente::getTrauma() const { return trauma; }
bool Paciente::getSintomasNeurologicos() const { return sintomasNeurologicos; }
bool Paciente::getRequiereCirugia() const { return requiereCirugia; }
int Paciente::getDiasHospitalizacion() const { return diasHospitalizacion; }
const std::string& Paciente::getServicio() const { return servicio; }

void Paciente::setServicio(const std::string& s) { servicio = s; }

bool Paciente::tipoDolorValido(const std::string& t) {
    return t == "pecho" || t == "cabeza" || t == "abdomen" || t == "extremidad" || t == "otro";
}

bool Paciente::esValido(std::string& motivo) const {
    if (id.empty())                 { motivo = "ID vacio"; return false; }
    if (nombre.empty())             { motivo = "Nombre vacio"; return false; }
    if (edad < 0 || edad > 120)     { motivo = "Edad fuera de rango (0-120): " + std::to_string(edad); return false; }
    if (temperatura < 30.0 || temperatura > 45.0) {
        motivo = "Temperatura fuera de rango (30.0-45.0): " + formatoTemperatura(temperatura);
        return false;
    }
    if (presion < 50 || presion > 260) {
        motivo = "PresionArterial fuera de rango (50-260 mmHg): " + std::to_string(presion);
        return false;
    }
    if (dolor < 0 || dolor > 10)    { motivo = "Dolor fuera de rango (0-10): " + std::to_string(dolor); return false; }
    if (!tipoDolorValido(tipoDolor)) {
        motivo = "TipoDolor invalido (pecho, cabeza, abdomen, extremidad, otro): '" + tipoDolor + "'";
        return false;
    }
    if (diasHospitalizacion < 0 || diasHospitalizacion > 365) {
        motivo = "DiasHospitalizacion fuera de rango (0-365): " + std::to_string(diasHospitalizacion);
        return false;
    }
    return true;
}

void Paciente::mostrar() const {
    std::cout << "ID: " << id << "\n";
    std::cout << "Nombre: " << nombre << "\n";
    std::cout << "Edad: " << edad << "\n";
    std::cout << "Temperatura: " << formatoTemperatura(temperatura) << "\n";
    std::cout << "PresionArterial: " << presion << "\n";
    std::cout << "Dolor: " << dolor << "\n";
    std::cout << "TipoDolor: " << tipoDolor << "\n";
    std::cout << "Trauma: " << (trauma ? 1 : 0) << "\n";
    std::cout << "SintomasNeurologicos: " << (sintomasNeurologicos ? 1 : 0) << "\n";
    std::cout << "RequiereCirugia: " << (requiereCirugia ? 1 : 0) << "\n";
    std::cout << "DiasHospitalizacion: " << diasHospitalizacion << "\n";
    if (!servicio.empty()) std::cout << "Servicio: " << servicio << "\n";
}

void Paciente::mostrarResumen() const {
    std::cout << "T: " << formatoTemperatura(temperatura) << " C | PA: " << presion
              << " | D: " << dolor << " | TD: " << tipoDolor
              << " | TR: " << siNo(trauma) << " | SN: " << siNo(sintomasNeurologicos)
              << " | RC: " << siNo(requiereCirugia) << " | DH: ";
    if (diasHospitalizacion == 0) std::cout << "Ninguno";
    else std::cout << diasHospitalizacion << " dias";
    std::cout << "\n";
}
