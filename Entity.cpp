#include "Entity.h"
#include <sstream>
#include <algorithm>

Entity::Entity(std::string nombre, double vida, int nivel) {
    this->nombre = nombre;
    this->nivel = nivel;
    this->vida = vida;
    this->vidaMax = vida;
    this->energia = 100.0;
    this->x = 0;
    this->y = 0;
    this->recursos = 0;
}

// Implementacion del cuerpo de los setters
void Entity::setNombre(const std::string& n) {
    nombre = n;
}
void Entity::setNivel(int n) {
    nivel = n;
}
void Entity::setVida(double v) {
    if (v < 0) vida = 0;
    else if (v > vidaMax) vida = vidaMax;
    else vida = v;
}
void Entity::setVidaMax(double vm) {
    vidaMax = vm;
}
void Entity::setEnergia(double e) {
    if (e < 0) energia = 0;
    else if (e > 100.0) energia = 100.0;
    else energia = e;
}
void Entity::setX(int nx) {
    x = nx;
}
void Entity::setY(int ny) {
    y = ny;
}
void Entity::setRecursos(int r) {
    recursos = r;
}

// Implementacion del cuerpo de los getters
std::string Entity::getNombre() const {
    return nombre;
}
int Entity::getNivel() const {
    return nivel;
}
double Entity::getVida() const {
    return vida;
}
double Entity::getVidaMax() const {
    return vidaMax;
}
double Entity::getEnergia() const {
    return energia;
}
int Entity::getX() const {
    return x;
}
int Entity::getY() const {
    return y;
}
int Entity::getRecursos() const {
    return recursos;
}

// Definicion de los métodos que los comandos llamarán
void Entity::mover(int dx, int dy) {
    setX(x + dx);
    setY(y + dy);
}
void Entity::curar(double cantidad) {
    setVida(vida + cantidad);
}
void Entity::recibirDanio(double cantidad) {
    setVida(vida - cantidad);
}
void Entity::usarEnergia(double cantidad) {
    setEnergia(energia - cantidad);
}
void Entity::recolectarRecursos(int cantidad) {
    setRecursos(recursos + cantidad);
}

std::string Entity::obtenerEstado() const {
    std::ostringstream oss;
    oss << "[Entidad: " << nombre
        << " | Nivel: " << nivel
        << " | Vida: " << vida << "/" << vidaMax
        << " | Energia: " << energia
        << " | Recursos: " << recursos
        << " | Posicion: (x=" << x << ", y=" << y << ")]";
    return oss.str();
}