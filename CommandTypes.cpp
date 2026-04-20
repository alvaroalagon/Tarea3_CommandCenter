#include "CommandTypes.h"

// Implementacion de moverFuncion
void moverFuncion(Entity& e, const std::list<std::string>& args) {
    if (args.size() < 2) {
        std::cout << "[Error] Mover requiere 2 argumentos (dx, dy).\n";
        return;
    }
    try {
        auto it = args.begin();
        int dx = std::stoi(*it);
        int dy = std::stoi(*(++it));
        e.mover(dx, dy);
    } catch (const std::exception& ex) {
        std::cout << "[Error] Argumentos invalidos para mover.\n";
    }
}

// Implementacion de recolectarFuncion
void recolectarFuncion(Entity& e, const std::list<std::string>& args) {
    if (args.empty()) return;
    try {
        int cantidad = std::stoi(args.front());
        e.recolectarRecursos(cantidad);
    } catch (...) {
        std::cout << "[Error] Recurso debe ser entero.\n";
    }
}

// Implementacion del operator() del functor
void DanioFunctor::operator()(const std::list<std::string>& args) {
    if (args.empty()) {
        std::cout << "[Error] Danio requiere 1 argumento.\n";
        return;
    }
    try {
        double cantidad = std::stod(args.front());
        entidad.recibirDanio(cantidad);
        vecesEjecutado++;
        std::cout << "[Functor] Danio aplicado. Total de veces: "
                  << vecesEjecutado << "\n";
    } catch (...) {
        std::cout << "[Error] La cantidad de danio debe ser un numero.\n";
    }
}