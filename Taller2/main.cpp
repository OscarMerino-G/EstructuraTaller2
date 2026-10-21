#include <iostream>
#include <limits>
#include "include/Hospital.hpp"

void limpiarBuffer() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main() {
    Hospital hospital;
    int opcion;

    std::cout << "Cargando pacientes desde archivo...\n";
    hospital.cargarPacientesDesdeArchivo("pacientes.txt");

    do {
        std::cout << "\n=== HOSPITAL MARMAJAA ===\n";
        std::cout << "1. Atender pacientes\n";
        std::cout << "2. Ver departamento (Estado Servicios)\n";
        std::cout << "3. Revisar historial de atencion\n";
        std::cout << "4. Ver cola de espera\n";
        std::cout << "5. Salir\n";
        std::cout << "Seleccionar opcion: ";
        
        if (!(std::cin >> opcion)) {
            std::cout << "Entrada invalida. :'v\n";
            limpiarBuffer();
            continue;
        }

        switch (opcion) {
            case 1: {
                hospital.mostrarColaEspera();
                int cant;
                std::cout << "\nIndique la cantidad de pacientes a atender: ";
                if (std::cin >> cant && cant > 0) {
                    hospital.atenderPacientes(cant);
                } else {
                    std::cout << "Cantidad invalida.\n";
                    limpiarBuffer();
                }
                break;
            }//////////////////////////////////////////////////////////////////////////*/////8//////////////////////////////////////////////////////////////////////////////1234567890'¿'098765432
            case 2: hospital.mostrarEstadoServicios(); break;
            case 3: hospital.mostrarHistorial(); break;
            case 4: hospital.mostrarColaEspera(); break;
            case 5: std::cout << "Saliendo y liberando memoria...\n"; break;
            default: std::cout << "Opcion no valida.\n";
        }
    } while (opcion != 5);

    return 0;
}
