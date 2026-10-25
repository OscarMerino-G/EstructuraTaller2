#include <iostream>
#include <string>
#include "include/Hospital.hpp"
#include "include/Utilidades.hpp"
int main(int argc, char* argv[]) {
    Hospital hospital;
    const std::string archivo = (argc > 1) ? argv[1] : "pacientes.txt";
    std::cout << "Cargando pacientes desde archivo...\n";
    hospital.cargarPacientesDesdeArchivo(archivo);
    int opcion = 0;
    do {
        std::cout << "\n=== HOSPITAL MARMAAJA ===\n";
        std::cout << "1. Atender pacientes\n";
        std::cout << "2. Ver departamentos\n";
        std::cout << "3. Buscar paciente\n";
        std::cout << "4. Operaciones AVL por departamento\n";
        std::cout << "5. Ver cola de espera\n";
        std::cout << "6. Revisar historial de atencion\n";
        std::cout << "7. Ver arbol de decision\n";
        std::cout << "8. Salir\n";
        if (!util::leerEnteroEnRango("Seleccionar opcion: ", 1, 8, opcion)) {
            std::cout << "\nFin de la entrada.\n";
            break;
        }
        switch (opcion) {
            case 1: {
                hospital.mostrarColaEspera();
                int cantidad = 0;
                if (!util::leerEnteroEnRango("\nCantidad de pacientes a atender (0 para cancelar): ",
                                             0, 1000000, cantidad)) {
                    opcion = 8;
                    break;
                }
                if (cantidad > 0) hospital.atenderPacientes(cantidad);
                break;
            }
            case 2: hospital.mostrarEstadoServicios(); break;
            case 3: {
                std::string termino;
                std::cout << "\nIndique el ID o Nombre del paciente: ";
                if (!util::leerLinea(termino)) { opcion = 8; break; }
                hospital.buscarPaciente(termino);
                break;
            }
            case 4: hospital.menuAVL(); break;
            case 5: hospital.mostrarColaEspera(); break;
            case 6: hospital.mostrarHistorial(); break;
            case 7: hospital.mostrarArbolDecision(); break;
            case 8: std::cout << "Saliendo y liberando memoria...\n"; break;
        }
    } while (opcion != 8);
    return 0;
}
