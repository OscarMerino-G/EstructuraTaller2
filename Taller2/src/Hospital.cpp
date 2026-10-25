#include "../include/Hospital.hpp"
#include "../include/Utilidades.hpp"
#include <fstream>
#include <iostream>

namespace {

const int CAMPOS_ESPERADOS = 11;

// division con ';'. Devuelve la cantidad de campos (puede superar maxCampos).
int dividirCampos(const std::string& linea, std::string campos[], int maxCampos) {
    int n = 0;
    size_t ini = 0;
    while (true) {
        size_t pos = linea.find(';', ini);
        std::string campo = (pos == std::string::npos) ? linea.substr(ini)
                                                       : linea.substr(ini, pos - ini);
        if (n < maxCampos) campos[n] = util::trim(campo);
        ++n;
        if (pos == std::string::npos) break;
        ini = pos + 1;
    }
    return n;
}

bool leerBandera(const std::string& texto, const char* nombre, bool& salida, std::string& motivo) {
    int v = 0;
    if (!util::aEntero(texto, v) || (v != 0 && v != 1)) {
        motivo = std::string(nombre) + " debe ser 0 o 1 (valor: '" + texto + "')";
        return false;
    }
    salida = (v == 1);
    return true;
}

// convierte una linea de pacientes.txt en paciente validado
bool parsearPaciente(const std::string& linea, Paciente& salida, std::string& motivo) {
    std::string c[CAMPOS_ESPERADOS + 1];
    int n = dividirCampos(linea, c, CAMPOS_ESPERADOS + 1);
    if (n == CAMPOS_ESPERADOS + 1 && c[CAMPOS_ESPERADOS].empty()) n = CAMPOS_ESPERADOS; // ';' final

    if (n < CAMPOS_ESPERADOS) {
        motivo = "datos insuficientes: se esperaban 11 campos y hay " + std::to_string(n);
        return false;
    }
    if (n > CAMPOS_ESPERADOS) {
        motivo = "formato invalido: se esperaban 11 campos y hay " + std::to_string(n);
        return false;
    }

    int edad = 0, presion = 0, dolor = 0, dias = 0;
    double temperatura = 0.0;
    bool trauma = false, neuro = false, cirugia = false;

    if (c[0].empty()) { motivo = "ID vacio"; return false; }
    if (c[1].empty()) { motivo = "Nombre vacio"; return false; }
    if (!util::aEntero(c[2], edad))        { motivo = "Edad no es un entero valido ('" + c[2] + "')"; return false; }
    if (!util::aDecimal(c[3], temperatura)) { motivo = "Temperatura no es un numero valido ('" + c[3] + "')"; return false; }
    if (!util::aEntero(c[4], presion))     { motivo = "PresionArterial no es un entero valido ('" + c[4] + "')"; return false; }
    if (!util::aEntero(c[5], dolor))       { motivo = "Dolor no es un entero valido ('" + c[5] + "')"; return false; }
    if (!leerBandera(c[7], "Trauma", trauma, motivo)) return false;
    if (!leerBandera(c[8], "SintomasNeurologicos", neuro, motivo)) return false;
    if (!leerBandera(c[9], "RequiereCirugia", cirugia, motivo)) return false;
    if (!util::aEntero(c[10], dias))       { motivo = "DiasHospitalizacion no es un entero valido ('" + c[10] + "')"; return false; }

    Paciente p(c[0], c[1], edad, temperatura, presion, dolor, util::minusculas(c[6]),
               trauma, neuro, cirugia, dias);
    if (!p.esValido(motivo)) return false;

    salida = p;
    return true;
}

void imprimirFicha(const Paciente& p) {
    std::cout << "------\n";
    std::cout << "ID: " << p.getId() << "\n";
    std::cout << "Nombre: " << p.getNombre() << "\n";
    std::cout << "Edad: " << p.getEdad() << "\n";
    std::cout << "Departamento: " << p.getServicio() << "\n";
    p.mostrarResumen();
    std::cout << "------\n";
}

} 

Hospital::Hospital() : cabeza(nullptr) {
    inicializarServicios();
}

Hospital::~Hospital() {
    NodoServicio* actual = cabeza;
    while (actual != nullptr) {
        NodoServicio* aux = actual;
        actual = actual->siguiente;
        delete aux;   // destructor de nodoServicio para libera el AVL
    }
    cabeza = nullptr;
}

void Hospital::inicializarServicios() {
    const std::string servicios[] = {
        "Urgencias", "Medicina General", "Cardiologia",
        "Neurologia", "Traumatologia", "Cirugia",
        "Pediatria", "Hospitalizacion"
    };

    NodoServicio* ultimo = nullptr;
    for (const std::string& s : servicios) {
        NodoServicio* nuevo = new NodoServicio(s);
        if (cabeza == nullptr) cabeza = nuevo;
        else ultimo->siguiente = nuevo;
        ultimo = nuevo;
    }
}

NodoServicio* Hospital::buscarServicio(const std::string& nombre) const {
    NodoServicio* actual = cabeza;
    while (actual != nullptr) {
        if (actual->nombreServicio == nombre) return actual;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool Hospital::servicioValido(const std::string& nombre) const {
    return buscarServicio(nombre) != nullptr;
}

bool Hospital::idExiste(const std::string& id) const {
    // 1 en la cola de espera
    for (Nodo<Paciente>* n = colaGlobal.getList().getHead(); n != nullptr; n = n->next) {
        if (n->info.getId() == id) return true;
    }
    // 2 en los AVL de los servicios para pacientes ya atendidos
    std::string ruta;
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        if (s->avl->search(id, ruta) != nullptr) return true;
    }
    return false;
}

void Hospital::cargarPacientesDesdeArchivo(const std::string& ruta) {
    std::ifstream archivo(ruta);
    if (!archivo.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo '" << ruta
                  << "'. Se continua sin pacientes en espera.\n";
        return;
    }

    int cargados = 0, omitidos = 0, numLinea = 0;
    std::string linea;
    while (std::getline(archivo, linea)) {
        ++numLinea;
        if (numLinea == 1 && linea.compare(0, 3, "\xEF\xBB\xBF") == 0) linea.erase(0, 3);
        linea = util::trim(linea);
        if (linea.empty() || linea[0] == '#') continue; 
        if (util::minusculas(linea).compare(0, 3, "id;") == 0) continue; 

        Paciente p;
        std::string motivo;
        if (!parsearPaciente(linea, p, motivo)) {
            std::cerr << "Linea " << numLinea << " omitida: " << motivo << "\n";
            ++omitidos;
            continue;
        }
        if (idExiste(p.getId())) {
            std::cerr << "Linea " << numLinea << " omitida: paciente duplicado (ID " << p.getId() << ")\n";
            ++omitidos;
            continue;
        }
        colaGlobal.encolar(p);
        ++cargados;
    }
    archivo.close();

    std::cout << "Carga finalizada: " << cargados << " paciente(s) en espera, "
              << omitidos << " linea(s) omitida(s).\n";
}

void Hospital::atenderPacientes(int cantidad) {
    std::cout << "\n=== ATENDIENDO PACIENTES ===\n";
    int atendidos = 0;
    for (int i = 0; i < cantidad; i++) {
        if (colaGlobal.isEmpty()) {
            std::cout << "No hay mas pacientes en espera.\n";
            break;
        }

        // retirar de la cola
        Paciente p = colaGlobal.front();
        colaGlobal.deencolar();

        p.mostrar();

        //evaliuar con el arbol de decision y obtener el servicio
        std::string ruta;
        std::string nombreServicio = arbol.evaluar(p, ruta);
        if (nombreServicio.empty()) {
            std::cout << "Error: no se pudo clasificar al paciente. " << ruta << "\n";
            std::cout << "--------------------------\n";
            continue;
        }
        std::cout << "Ruta: " << ruta << "\n";
        std::cout << "Servicio asignado: " << nombreServicio << "\n";
        p.setServicio(nombreServicio);

        //  insertar en el AVL del servicio
        NodoServicio* servicio = buscarServicio(nombreServicio);
        if (servicio == nullptr) {
            std::cout << "Error critico: el servicio '" << nombreServicio << "' no existe.\n";
        } else if (servicio->avl->insert(p)) {
            //  informar el resultado
            std::cout << "Paciente insertado en el AVL de " << nombreServicio << ".\n";
            if (servicio->avl->getUltimaRotacion() != "Ninguna")
                std::cout << "AVL rebalanceado: " << servicio->avl->getUltimaRotacion() << ".\n";
            historial.push(p);
            ++atendidos;
        } else {
            std::cout << "Error: ya existe un paciente con ID " << p.getId()
                      << " en " << nombreServicio << ". No se inserto.\n";
        }
        std::cout << "--------------------------\n";
    }
    std::cout << "Pacientes atendidos en esta operacion: " << atendidos << "\n";
}

void Hospital::mostrarEstadoServicios() const {
    std::cout << "\n=== ESTADO DE LOS DEPARTAMENTOS ===\n";
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        std::cout << s->nombreServicio << "\n";
        if (s->avl->isEmpty()) {
            std::cout << "  Sin pacientes\n";
        } else {
            std::cout << "  Pacientes (" << s->avl->size() << ", altura AVL "
                      << s->avl->getHeight() << "): " << s->avl->listInOrder() << "\n";
        }
    }
}

void Hospital::buscarPaciente(const std::string& terminoCrudo) const {
    std::string termino = util::trim(terminoCrudo);
    std::cout << "\n=== BUSCAR PACIENTE ===\n";
    if (termino.empty()) {
        std::cout << "Debe indicar un ID o un nombre.\n";
        return;
    }
    std::cout << "Buscando en AVL...\n";

    // por id, en cada AVL se usa el orden del arbol
    std::string ruta;
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        const Paciente* p = s->avl->search(termino, ruta);
        if (p != nullptr) {
            std::cout << "Paciente encontrado:\n";
            imprimirFicha(*p);
            std::cout << "Ruta de busqueda (IDs visitados en el AVL de " << s->nombreServicio
                      << "):\n" << ruta << "\n";
            return;
        }
    }

    // por nombre, la clave es el ID, se recorre el AVL completo.
    Lista<Paciente> resultados;
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        s->avl->searchByName(termino, resultados);
    }
    if (resultados.isEmpty()) {
        std::cout << "No se encontro ningun paciente con ID o nombre '" << termino << "'.\n";
        return;
    }
    std::cout << "Coincidencias por nombre: " << resultados.size() << "\n";
    for (Nodo<Paciente>* n = resultados.getHead(); n != nullptr; n = n->next) {
        imprimirFicha(n->info);
    }
}

void Hospital::menuAVL() {
    std::cout << "\n=== OPERACIONES SOBRE AVL ===\n";
    int cantidad = 0;
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        ++cantidad;
        std::cout << cantidad << ". " << s->nombreServicio << "\n";
    }
    int eleccion = 0;
    if (!util::leerEnteroEnRango("Seleccione departamento (0 para volver): ", 0, cantidad, eleccion)
        || eleccion == 0) return;

    NodoServicio* servicio = cabeza;
    for (int i = 1; i < eleccion; i++) servicio = servicio->siguiente;

    int op = -1;
    do {
        std::cout << "\n--- AVL de " << servicio->nombreServicio << " ---\n";
        std::cout << "1. Recorrido inorden\n2. Recorrido preorden\n3. Recorrido postorden\n"
                     "4. Altura del arbol\n5. Factor de balance\n0. Volver\n";
        if (!util::leerEnteroEnRango("Seleccionar opcion: ", 0, 5, op)) return;
        switch (op) {
            case 1: servicio->avl->displayInOrder(); break;
            case 2: servicio->avl->displayPreOrder(); break;
            case 3: servicio->avl->displayPostOrder(); break;
            case 4: std::cout << "Altura: " << servicio->avl->getHeight() << "\n"; break;
            case 5: servicio->avl->displayBalanceFactors(); break;
            default: break;
        }
    } while (op != 0);
}

void Hospital::mostrarHistorial() const {
    std::cout << "\n=== HISTORIAL DE ATENCIONES (Reciente a Antiguo) ===\n";
    if (historial.isEmpty()) {
        std::cout << "El historial esta vacio.\n";
        return;
    }
    for (Nodo<Paciente>* n = historial.getList().getHead(); n != nullptr; n = n->next) {
        std::cout << "--------------------------\n";
        n->info.mostrar();
    }
}

void Hospital::mostrarColaEspera() const {
    std::cout << "\n=== PACIENTES EN ESPERA ===\n";
    if (colaGlobal.isEmpty()) {
        std::cout << "No hay pacientes en espera.\n";
        return;
    }
    int pos = 1;
    for (Nodo<Paciente>* n = colaGlobal.getList().getHead(); n != nullptr; n = n->next, ++pos) {
        std::cout << pos << ". " << n->info.getId() << " - " << n->info.getNombre() << "\n";
    }
}

void Hospital::mostrarArbolDecision() const {
    arbol.mostrarArbol();
    arbol.mostrarPreorden();
    arbol.mostrarInorden();
    arbol.mostrarPostorden();
// AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
    std::cout << "\nRutas (hojas) que llevan a cada servicio:\n";
    for (NodoServicio* s = cabeza; s != nullptr; s = s->siguiente) {
        std::cout << "  " << s->nombreServicio << ": " << arbol.contarHojas(s->nombreServicio) << "\n";
    }
}
