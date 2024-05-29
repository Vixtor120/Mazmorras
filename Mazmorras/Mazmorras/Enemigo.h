#pragma once

#include "Personaje.h"

class Enemigo : public Personaje {
public:
    Enemigo(string pNombre, int pVida, int pAtaque, int pPosX, int pPosY);
};
