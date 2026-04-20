#include <iostream>
#include <list>
#include <string>
#include <functional>
#include "Entity.h"
#include "CommandCenter.h"
#include "CommandTypes.h"

using namespace std::placeholders;

int main() {
    // CREAR UN OBJETO DE ENTITY Y COMMANDCENTER
    Entity heroe("Arthas", 150.0, 5);
    sd<Entity> centro(heroe);

    // Definicion de funciones lambdas

    // Lambda para Curar
    auto logicaCurar = [&heroe](const std::list<std::string>& args) {
        if (args.empty()) {
            std::cout << "[Error] Curar requiere un valor numerico.\n";
            return;
        }
        try {
            heroe.curar(std::stod(args.front()));
        } catch (...) {
            std::cout << "[Error] El valor de curacion debe ser un numero.\n";
        }
    };

    // Lambda para Energía
    auto logicaEnergia = [&heroe](const std::list<std::string>& args) {
        if (args.empty()) {
            std::cout << "[Error] Indica la cantidad de energia a usar.\n";
            return;
        }
        try {
            heroe.usarEnergia(std::stod(args.front()));
        } catch (...) {
            std::cout << "[Error] La energia debe ser un valor numerico.\n";
        }
    };

    // Lambda para Status
    auto logicaStatus = [&heroe](const std::list<std::string>&) {
        std::cout << ">>> " << heroe.obtenerEstado() << "\n";
    };

    // REGISTRO DE COMANDOS
    std::cout << "\n1. EJECUTANDO COMANDOS:\n";

    // A. Registro usando Funciones Libres
    centro.registrarComando("mover", std::bind(moverFuncion, std::ref(heroe), _1));
    centro.registrarComando("recolectar", std::bind(recolectarFuncion, std::ref(heroe), _1));

    // B. Registro usando Functores
    DanioFunctor danioOp(heroe);
    centro.registrarComando("danio", danioOp);

    // C. Registro usando Lambdas
    centro.registrarComando("curar", logicaCurar);
    centro.registrarComando("energia", logicaEnergia);
    centro.registrarComando("status", logicaStatus);


    // EJECUCION DE CAMANDOS VALIDOS
    std::cout << "a) EJECUCION DE COMANDOS VALIDOS:\n";

    // Ejemplos de Funciones Libres (Mover/Recolectar)
    centro.ejecutar("mover", {"10", "20"});
    centro.ejecutar("recolectar", {"50"});

    // Ejemplos de Functor (Daño)
    centro.ejecutar("danio", {"26.5"});
    centro.ejecutar("danio", {"5.0"});

    // Ejemplos de Lambdas (Curar/Energía/Status)
    centro.ejecutar("curar", {"15.0"});
    centro.ejecutar("energia", {"43.0"});
    centro.ejecutar("status");

    // EJECUCION DE CAMANDOS INVALIDOS
    std::cout << "b) EJECUCION DE COMANDOS INVALIDOS:\n";

    centro.ejecutar("volar", {"100"}); // Comando que no existe
    centro.ejecutar("mover", {"diez"}); // Argumentos invalidos
    centro.ejecutar("curar", {});  // Lista de argumentos vacía


    // REGISTRO DE MACRO COMANDOS
    std::cout << "\n2. EJECUTANDO MACRO COMANDOS:\n";

    centro.registrarMacro("explorar", {
        {"mover", {"5", "5"}},
        {"status", {}}
    });
    centro.registrarMacro("combate", {
        {"danio", {"20"}},
        {"energia", {"10"}},
        {"status", {}}
    });
    centro.registrarMacro("descanso", {
        {"curar", {"50"}},
        {"recolectar", {"10"}},
        {"status", {}}
    });
    centro.registrarMacro("patrulla", {
        {"mover", {"10", "0"}},
        {"status", {}},
        {"mover", {"-10", "0"}},
        {"status", {}}
    });
    centro.registrarMacro("escape", {
        {"curar", {"40"}},
        {"energia", {"20"}},
        {"mover", {"50", "50"}},
        {"status", {}}
    });

    // EJECUCION DE MACRO CAMANDOS
    centro.ejecutarMacro("explorar");
    centro.ejecutarMacro("combate");
    centro.ejecutarMacro("descanso");
    centro.ejecutarMacro("patrulla");
    centro.ejecutarMacro("escape");

    // DEMOSTRAR LA ELIMINACION DINAMICA
    std::cout << "\n3. DEMOSTRACION DE ELMINACION DINAMICA:\n";

    centro.ejecutar("recolectar", {"25"});
    centro.eliminarComando("recolectar");

    // Intentar ejecutar el comando eliminado (ERROR)
    centro.ejecutar("recolectar", {"25"});

    // Intentar eliminar un comando que no existe (ERROR)
    centro.eliminarComando("volar");


    // VISUALIZACION DEL ESTADO FINAL Y EL HISTORIAL
    std::cout << "\nEntidad al finalizar: " << heroe.obtenerEstado() << "\n";
    centro.mostrarHistorial();

    return 0;
}