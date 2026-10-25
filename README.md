25-10-2026
# EstructuraTaller2
Extender el sistema desarrollado en el Taller 1 :trollface: para clasificar automáticamente a los pacientes mediante un árbol de decisión y almacenarlos en árboles AVL según el servicio asignado.

# Integrante 
>Oscar Merino | 21279689-1 | GitHub: OscarMerino-G | ICCI | C2

# Compilar
ingresar el siguiente comando en la consola
```
g++ -std=c++17 -g -Iinclude main.cpp src/Hospital.cpp src/clases/Paciente.cpp src/estructura/AVL.cpp src/estructura/ArbolDecision.cpp -o main
```
# Ejecutar
ingresar el siguiente comando en la consola
```
./main
```
# Arbol de decision

ArbolDecision rama izquierda = "Si", derecha = "No". Las preguntas son nodos internos y los servicios son hojas. Permite construccion, recorridos (pre/in/postorden), evaluacion de un paciente y obtencion del servicio resultante. Opcion ]7[ del menu muestra el arbol con la justificacion de cada decision.
funciona siguiendo la lógica:
```

Edad < 14?                                      -> Si: Pediatria
 No: Trauma == 1?
   Si: RequiereCirugia == 1?                   -> Si: Cirugia   | No: Traumatologia
   No: SintomasNeurologicos == 1?              -> Si: Neurologia
     No: TipoDolor == pecho?                   -> Si: Cardiologia
       No: Temperatura >= 38.5?                -> Si: Urgencias
         No: Dolor >= 8?                       -> Si: Urgencias
           No: PresionArterial >= 180?         -> Si: Urgencias
             No: PresionArterial < 90?         -> Si: Urgencias
               No: RequiereCirugia == 1?       -> Si: Cirugia
                 No: DiasHospitalizacion >= 2? -> Si: Hospitalizacion | No: Medicina General

```

La condicion "o" de Urgencias se implementa como una cadena de preguntas simples, la ruta mostrada indica cual condicion se cumplio.
