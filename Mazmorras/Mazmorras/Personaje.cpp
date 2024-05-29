#include "Personaje.h"

//Constructor
Personaje::Personaje(string pNombre, int pVida, int pAtaque, int pPosX, int pPosY) {
    Nombre = pNombre;
    Vida = pVida;
    Ataque = pAtaque;
    PosicionX = pPosX;
    PosicionY = pPosY;
}

//get set
string Personaje::getNombre() {
    return Nombre;
}

void Personaje::setNombre(string pNombre) {
    Nombre = pNombre;
}

int Personaje::getVida() {
    return Vida;
}

void Personaje::setVida(int pVida) {
    Vida = pVida;
}

int Personaje::getAtaque() {
    return Ataque;
}

void Personaje::setAtaque(int pAtaque) {
    Ataque = pAtaque;
}

int Personaje::getPosicionX() {
    return PosicionX;
}

void Personaje::setPosicionX(int pPosX) {
    PosicionX = pPosX;
}

int Personaje::getPosicionY() {
    return PosicionY;
}

void Personaje::setPosicionY(int pPosY) {
    PosicionY = pPosY;
}

//mover el personaje
void Personaje::mover(int pNuevaPosX, int pNuevaPosY) {
    PosicionX = pNuevaPosX;
    PosicionY = pNuevaPosY;
}
