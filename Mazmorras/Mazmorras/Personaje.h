#pragma once

#include <iostream>

using namespace std;

class Personaje {
private:
    string Nombre;
    int Vida;
    int Ataque;
    int PosicionX;
    int PosicionY;

public:
    // Constructor
    Personaje(string pNombre, int pVida, int pAtaque, int pPosX, int pPosY);

    string getNombre();
    void setNombre(string pNombre);

    int getVida();
    void setVida(int pVida);
    int getAtaque();
    void setAtaque(int pAtaque);
    int getPosicionX();
    void setPosicionX(int pPosX);
    int getPosicionY();
    void setPosicionY(int pPosY);

    // Mover personaje
    void mover(int pNuevaPosX, int pNuevaPosY);
};
