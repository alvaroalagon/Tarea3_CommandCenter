#ifndef COMMANDCENTER___ENTITY_H
#define COMMANDCENTER___ENTITY_H

#include <string>

class Entity {
private:
    // Estado interno (atributos privados)
    std::string nombre;
    int nivel;
    double vida;
    double vidaMax;
    double energia;
    int x, y;
    int recursos;

public:
    Entity(std::string nombre = "Heroe", double vida = 100.0, int nivel = 1);

    // Setters
    void setNombre(const std::string& n);
    void setNivel(int n);
    void setVida(double v);
    void setVidaMax(double vm);
    void setEnergia(double e);
    void setX(int nx);
    void setY(int ny);
    void setRecursos(int r);

    // Getters
    std::string getNombre() const;
    int getNivel() const;
    double getVida() const;
    double getVidaMax() const;
    double getEnergia() const;
    int getX() const;
    int getY() const;
    int getRecursos() const;

    // Métodos de la lógica de comandos
    void mover(int dx, int dy);
    void curar(double cantidad);
    void recibirDanio(double cantidad);
    void usarEnergia(double cantidad);
    void recolectarRecursos(int cantidad);

    std::string obtenerEstado() const;
};

#endif