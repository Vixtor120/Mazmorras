#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Personaje.h"
#include "EnemigoFinal.h"

using namespace std;

const int NUM_ENEMIGOS = 4;

//batalla por turnos enemigos
bool batalla(Personaje& heroe, Personaje& enemigo) {
    while (heroe.getVida() > 0 && enemigo.getVida() > 0) {
        char accion;
        cout << "Heroe Vida: " << heroe.getVida() << " | Enemigo Vida: " << enemigo.getVida() << endl;
        cout << "Elige tu accion: (A) Atacar, (E) Esquivar: ";
        cin >> accion;

        if (accion == 'a' || accion == 'A') {
            enemigo.setVida(max(0, enemigo.getVida() - heroe.getAtaque()));
            cout << "Has atacado al enemigo! Vida del enemigo: " << enemigo.getVida() << endl;
            if (enemigo.getVida() == 0) {
                cout << "¡Has derrotado al enemigo!" << endl;
                break;
            }
        }
        else if (accion == 'e' || accion == 'E') {
            cout << "Has intentado esquivar el ataque del enemigo!" << endl;
            //50% posibilidad
            if (rand() % 2 == 0) {
                cout << "¡Esquiva exitosa!" << endl;
                continue;
            }
            else {
                cout << "¡Esquiva fallida!" << endl;
            }
        }
        else {
            cout << "Accion no valida. Pierdes tu turno." << endl;
        }

        //enemigo si sigue vivo
        if (enemigo.getVida() > 0) {
            heroe.setVida(max(0, heroe.getVida() - enemigo.getAtaque()));
            cout << "El enemigo te ha atacado! Vida del heroe: " << heroe.getVida() << endl;
        }
    }
    return heroe.getVida() > 0;
}

//mostrar tablero posicion enemigos y salida
void mostrarTablero(char tablero[][20], Personaje& heroe, EnemigoFinal& enemigoFinal, int enemigos[NUM_ENEMIGOS][2], const vector<pair<int, int>>& posicionesX, pair<int, int> salida) {
    //limpiar tablero
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            if (i == 0 || i == 19 || j == 0 || j == 19) {
                tablero[i][j] = '-';  //bordes de los lados
            }
            else {
                tablero[i][j] = ' ';
            }
        }
    }

    //jugador
    tablero[heroe.getPosicionX()][heroe.getPosicionY()] = 'P';

    //enemigos
    for (int i = 0; i < NUM_ENEMIGOS; ++i) {
        if (enemigos[i][0] != -1 && enemigos[i][1] != -1) {
            tablero[enemigos[i][0]][enemigos[i][1]] = 'E';
        }
    }

    //salida
    tablero[salida.first][salida.second] = 'S';

    // Mostrar el tablero
    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 20; ++j) {
            cout << tablero[i][j] << ' ';
        }
        cout << endl;
    }
}

//main
int main() {
    const int filas = 20;
    const int columnas = 20;
    char tablero[filas][columnas];

    srand(time(0));

    char opcion;
    do {
        cout << "Bienvenido al juego. Quieres jugar? (s/n): ";
        cin >> opcion;

        if (opcion != 's' && opcion != 'S')
            return 0;

        //nombre heroe
        string nombreHeroe;
        cout << "Ingresa el nombre de tu heroe: ";
        cin >> nombreHeroe;
        cout << "Recuerda tienes que derrotar a todos los enemigos. Suerte!\n";

        //creamos heroe y enemigo final
        Personaje heroe(nombreHeroe, 100, 20, 1, 1);
        EnemigoFinal enemigoFinal("Thor", 200, 30, filas - 3, columnas - 3, 40, 50);

        //posicion aleatoria
        int enemigos[NUM_ENEMIGOS][2];
        for (int i = 0; i < NUM_ENEMIGOS; ++i) {
            do {
                enemigos[i][0] = rand() % (filas - 2) + 1;
                enemigos[i][1] = rand() % (columnas - 2) + 1;
            } while ((enemigos[i][0] == 1 && enemigos[i][1] == 1) || (enemigos[i][0] <= 1 || enemigos[i][0] >= filas - 2 || enemigos[i][1] <= 1 || enemigos[i][1] >= columnas - 2)); //aseguramos que no estan o en posi de enemigos o de personaje
        }

        //salida que no este en los bordes
        pair<int, int> salida;
        do {
            salida.first = rand() % (filas - 2) + 1;
            salida.second = rand() % (columnas - 2) + 1;
        } while (salida.first == 1 && salida.second == 1); // aseguramos que no esta en donde aparece el personaje

        // Lista de posiciones con 'X' (enemigos derrotados)
        vector<pair<int, int>> posicionesX;

        //tablero inicial
        mostrarTablero(tablero, heroe, enemigoFinal, enemigos, posicionesX, salida);

        //movimiento jugador con w,a,s,d
        while (true) {
            char direccion;
            cout << "Ingresa la direccion a la que quieres moverte (w/a/s/d): ";
            cin >> direccion;

            int nuevaPosX = heroe.getPosicionX();
            int nuevaPosY = heroe.getPosicionY();

            switch (direccion) {
            case 'w':
                if (nuevaPosX > 1)
                    nuevaPosX--;
                break;
            case 'a':
                if (nuevaPosY > 1)
                    nuevaPosY--;
                break;
            case 's':
                if (nuevaPosX < filas - 2)
                    nuevaPosX++;
                break;
            case 'd':
                if (nuevaPosY < columnas - 2)
                    nuevaPosY++;
                break;
            default:
                cout << "Direccion no valida. Por favor, ingresa w/a/s/d." << endl;
                continue;
            }

            //acualizar posicion heroe
            heroe.mover(nuevaPosX, nuevaPosY);

            // posicion enemigo = batalla epica.
            bool batallaIniciada = false;
            for (int i = 0; i < NUM_ENEMIGOS; ++i) {
                if (nuevaPosX == enemigos[i][0] && nuevaPosY == enemigos[i][1]) {
                    cout << "Te has encontrado con un enemigo!" << endl;
                    Personaje enemigo("Enemigo", 50, 10, enemigos[i][0], enemigos[i][1]); //enemigo temporal para la batalla 
                    if (!batalla(heroe, enemigo)) {
                        cout << "GAME OVER. El enemigo te ha derrotado." << endl;

                        return 0; //termian el game
                    }
                    else {
                        // Eliminar al enemigo derrotado del tablero
                        posicionesX.push_back(make_pair(enemigos[i][0], enemigos[i][1]));
                        enemigos[i][0] = -1; //marcamos posicion enemigo derrotado
                        enemigos[i][1] = -1;
                    }
                    batallaIniciada = true;
                    break;
                }
            }

            //separador
            cout << "\n--------------------------------\n";

            //mostrar nuevo tablero
            mostrarTablero(tablero, heroe, enemigoFinal, enemigos, posicionesX, salida);

            //Verificar si todos los enemigos han sido derrotados
            bool todosEnemigosDerrotados = true;
            for (int i = 0; i < NUM_ENEMIGOS; ++i) {
                if (enemigos[i][0] != -1 || enemigos[i][1] != -1) {
                    todosEnemigosDerrotados = false;
                    break;
                }
            }

            //verificar si el jugador llegó a la salida o si está en la misma posición que el enemigo final
            if (todosEnemigosDerrotados && heroe.getPosicionX() == salida.first && heroe.getPosicionY() == salida.second) {
                // Encuentro con el EnemigoFinal en la salida
                cout << "Te has encontrado con el Enemigo Final en la salida!" << endl;
                heroe.setVida(100); //restablecer vida 100
                if (batalla(heroe, enemigoFinal)) {
                    cout << "Felicidades! Has derrotado al Enemigo Final y ganaste el juego!" << endl;
                }
                else {
                    cout << "GAME OVER. El Enemigo Final te ha derrotado." << endl;
                }
                break;
            }
            else if (heroe.getPosicionX() == salida.first && heroe.getPosicionY() == salida.second) {
                cout << "No puedes salir sin derrotar a todos los enemigos." << endl;
            }
            else if (heroe.getPosicionX() == enemigoFinal.getPosicionX() && heroe.getPosicionY() == enemigoFinal.getPosicionY()) {
                heroe.setVida(100); //restablecer vida a 100 en la batalla final
                if (batalla(heroe, enemigoFinal)) {
                    cout << "Felicidades! Has derrotado al Enemigo Final y ganaste el juego!" << endl;
                }
                else {
                    cout << "GAME OVER. El Enemigo Final te ha derrotado." << endl;
                }
                break;
            }

            if (!batallaIniciada) {
                cout << "\n--------------------------------\n";
                mostrarTablero(tablero, heroe, enemigoFinal, enemigos, posicionesX, salida);
            }
        }
    } while (opcion == 's' || opcion == 'S');

    return 0;
}
