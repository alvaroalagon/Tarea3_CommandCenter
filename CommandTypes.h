#ifndef COMMANDCENTER___COMMANDTYPES_H
#define COMMANDCENTER___COMMANDTYPES_H

#include "Entity.h"
#include <list>
#include <string>
#include <iostream>

// Declaracion de funciones libres
void moverFuncion(Entity& e, const std::list<std::string>& args);
void recolectarFuncion(Entity& e, const std::list<std::string>& args);

// Declaracion de un functor
struct DanioFunctor {
    Entity& entidad;
    int vecesEjecutado = 0;
    explicit DanioFunctor(Entity& e) : entidad(e) {}
    void operator()(const std::list<std::string>& args);
};

#endif //COMMANDCENTER___COMMANDTYPES_H