#include <iostream>
#include <cstdlib>
#include <ctime>

#include "personaje.h"

using namespace std;

void mostrarEstado(const Personaje& p) {
    cout << p.getNombre() << " — "
         << "HP: " << p.getVidaActual() << "/" << p.getVidaMaxima()
         << " | ATK: " << p.getAtaque() << " | DEF: " << p.getDefensa()
         << " | Nvl: " << p.getNivel()
         << endl;
}

void barraVida(const Personaje& p, int ancho = 20) {
    int lleno = (p.getVidaActual() * ancho) / p.getVidaMaxima();
    cout << "[";
    for (int i = 0; i < ancho; i++) {
        if (i < lleno) cout << "#";
        else           cout << ".";
    }
    cout << "] " << p.getVidaActual() << "/" << p.getVidaMaxima() << endl;
}

int main() {
    srand(time(nullptr));

    // --- Crear personajes ---
    Personaje heroe("Héroe",  5, 100, 20, 10, 50, false);
    Personaje enemigo("Enemigo Genérico", 3, 80, 15, 5, 30, false);

    int pociones = 3;        // curaciones limitadas del jugador
    int turno = 0;

    cout << "\n=== COMIENZA LA BATALLA ===\n\n";

    while (!heroe.estaEliminado() && !enemigo.estaEliminado()) {
        turno++;
        cout << "--- Turno " << turno << " ---\n";
        barraVida(heroe);
        barraVida(enemigo);
        cout << endl;

        // --- Turno del jugador ---
        cout << "Acción: [1] Atacar  [2] Curar (x" << pociones << ")  [3] Rendirse → ";
        int opcion;
        cin >> opcion;

        if (opcion == 3) {
            cout << "\n¡Te has rendido! " << enemigo.getNombre() << " gana.\n";
            return 0;
        }

        if (opcion == 2 && pociones > 0) {
            int curacion = 25 + (rand() % 11);  // 25–35
            heroe.curar(curacion);
            pociones--;
            cout << heroe.getNombre() << " se cura " << curacion << " puntos de vida.\n";
        } else if (opcion == 2 && pociones == 0) {
            cout << "¡No te quedan curaciones! Atacas por inercia.\n";
            int danio = heroe.atacar();
            int variacion = (rand() % 11) - 5;  // -5 .. +5
            danio += variacion;
            if (danio < 0) danio = 0;
            enemigo.recibirDanio(danio);
            cout << heroe.getNombre() << " ataca por " << danio << " de daño.\n";
        } else {
            int danio = heroe.atacar();
            int variacion = (rand() % 11) - 5;  // -5 .. +5
            danio += variacion;
            if (danio < 0) danio = 0;

            // 20 % de golpe crítico
            bool critico = (rand() % 100) < 20;
            if (critico) {
                danio = danio * 2;
                cout << "¡GOLPE CRÍTICO! ";
            }

            enemigo.recibirDanio(danio);
            cout << heroe.getNombre() << " ataca por " << danio << " de daño.\n";
        }

        if (enemigo.estaEliminado()) break;

        // --- Turno del enemigo ---
        int danioEne = enemigo.atacar();
        int variacionE = (rand() % 11) - 5;
        danioEne += variacionE;
        if (danioEne < 0) danioEne = 0;

        heroe.recibirDanio(danioEne);
        cout << enemigo.getNombre() << " ataca por " << danioEne << " de daño.\n";

        cout << endl;
    }

    // --- Resultado ---
    cout << "\n========================\n";
    if (enemigo.estaEliminado()) {
        cout << "¡" << heroe.getNombre() << " ha vencido a " << enemigo.getNombre() << "!\n";
        int oroGanado = 15 + (rand() % 21);  // 15–35
        heroe.agregarOro(oroGanado);
        cout << "Oro obtenido: " << oroGanado << " (total: " << heroe.getOro() << ")\n";
    } else {
        cout << heroe.getNombre() << " ha sido derrotado...\n";
    }
    cout << "Turnos transcurridos: " << turno << "\n";
    cout << "========================\n\n";

    return 0;
}
