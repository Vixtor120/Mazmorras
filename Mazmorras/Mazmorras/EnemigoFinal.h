#pragma once

#include "Personaje.h"

class EnemigoFinal : public Personaje {
private:
    int SuperAtaque1;
    int SuperAtaque2;

public:
    //constructor
    EnemigoFinal(string pNombre, int pVida, int pAtaque, int pPosX, int pPosY, int pSuperAtaque1, int pSuperAtaque2);

    int getSuperAtaque1();
    void setSuperAtaque1(int pSuperAtaque1);

    int getSuperAtaque2();
    void setSuperAtaque2(int pSuperAtaque2);

    //hacer ataque
    int ejecutarAtaque();
};
