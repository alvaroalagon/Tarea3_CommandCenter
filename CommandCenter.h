#ifndef COMMANDCENTER___COMMANDCENTER_H
#define COMMANDCENTER___COMMANDCENTER_H

#include <string>
#include <list>
#include <map>
#include <functional>
#include <iostream>
#include <algorithm>
#include "Entity.h"

// 1. Definición obligatioa del tipo Command
using Command = std::function<void(const std::list<std::string>&)>;

// 2. Estructura para los Macro Comandos
using MacroStep = std::pair<std::string, std::list<std::string>>;

template <typename T>
class sd {
private:
    T& entidad; // Instancia compartida de Entity
    std::map<std::string, Command> comandos;
    std::list<std::string> historial;
    std::map<std::string, std::list<MacroStep>> macros;

public:
    explicit sd(T& e) : entidad(e) {}

    // Metodo para el registro de comandos
    void registrarComando(const std::string& nombre, Command cmd) {
        comandos[nombre] = std::move(cmd);
        std::cout << "[Sistema] Comando registrado: " << nombre << "\n";
    }

    // Metodo para la ejecucion de comandos
    void ejecutar(const std::string& nombre, const std::list<std::string>& argumentos = {}) {
        typename std::map<std::string, Command>::iterator it = comandos.find(nombre);
        if (it != comandos.end()) {
            std::string antes = entidad.obtenerEstado();
            try {
                it->second(argumentos);
                std::string despues = entidad.obtenerEstado();
                historial.push_back("Comando: " + nombre + " | Antes: " + antes + " -> Despues: " + despues);
            } catch (const std::exception& e) {
                std::cerr << "[Error en ejecucion] " << e.what() << "\n";
                historial.push_back("Comando: " + nombre + " | ERROR: " + e.what());
            }
        } else {
            std::cout << "[Error] Comando '" << nombre << "' no registrado.\n";
        }
    }

    // Metodo para la eliminacion dinamica de comandos
    void eliminarComando(const std::string& nombre) {
        typename std::map<std::string, Command>::iterator it = comandos.find(nombre);
        if (it != comandos.end()) {
            comandos.erase(it);
            std::cout << "[Sistema] Comando eliminado: " << nombre << "\n";
        } else {
            std::cout << "[Error] No se puede eliminar: " << nombre << " no existe.\n";
        }
    }

    // Metodo para consultar el historial
    void mostrarHistorial() const {
        std::cout << "\nHISTORIAL DE EJECUCIÓN: \n";
        if (historial.empty()) {
            std::cout << "(Vacio)\n";
            return;
        }
        for (std::list<std::string>::const_iterator it = historial.begin(); it != historial.end(); ++it) {
            std::cout << " > " << *it << "\n";
        }
    }

    // Comandos exclusivos para las macros (registro/ejecucion)
    void registrarMacro(const std::string& nombre, const std::list<MacroStep>& pasos) {
        macros[nombre] = pasos;
        std::cout << "[Sistema] Macro registrado: " << nombre << " (" << pasos.size() << " pasos)\n";
    }

    void ejecutarMacro(const std::string& nombre) {
        typename std::map<std::string, std::list<MacroStep>>::iterator itMacro = macros.find(nombre);

        if (itMacro == macros.end()) {
            std::cout << "[Error] Macro '" << nombre << "' no existe.\n";
            return;
        }

        std::cout << "[Macro] Iniciando: " << nombre << "\n";
        const std::list<MacroStep>& pasos = itMacro->second;

        for (typename std::list<MacroStep>::const_iterator itPaso = pasos.begin(); itPaso != pasos.end(); ++itPaso) {
            ejecutar(itPaso->first, itPaso->second);
        }
        std::cout << "[Macro] Finalizado: " << nombre << "\n";
    }
};

#endif //COMMANDCENTER___COMMANDCENTER_H