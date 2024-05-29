#include "EnemigoFinal.h"
#include <cstdlib>
#include <ctime>

//constructor
EnemigoFinal::EnemigoFinal(string pNombre, int pVida, int pAtaque, int pPosX, int pPosY, int pSuperAtaque1, int pSuperAtaque2)
	: Personaje(pNombre, pVida, pAtaque, pPosX, pPosY), SuperAtaque1(pSuperAtaque1), SuperAtaque2(pSuperAtaque2) {
	srand(time(0));
}

int EnemigoFinal::getSuperAtaque1() {
	return SuperAtaque1;
}

void EnemigoFinal::setSuperAtaque1(int pSuperAtaque1) {
	SuperAtaque1 = pSuperAtaque1;
}

int EnemigoFinal::getSuperAtaque2() {
	return SuperAtaque2;
}

void EnemigoFinal::setSuperAtaque2(int pSuperAtaque2) {
	SuperAtaque2 = pSuperAtaque2;
}

//usando rand para el ataque
int EnemigoFinal::ejecutarAtaque() {
	int randNum = rand() % 3;
	if (randNum == 0) {
		return SuperAtaque1;
	}
	else if (randNum == 1) {
		return SuperAtaque2; 
	}
	else {
		return getAtaque();
	}
}
