#ifndef PERSONAJE_H
#define PERSONAJE_H

#include "item.h"

class Personaje {
private:
    char nombre[50];
    int nivel, vidaActual, vidaMaxima, ataque, defensa, oro;
    bool eliminado;
    const Item* armaEquipada;
    const Item* armaduraEquipada;

public:
    // Constructor
    Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim);

    void equiparArma(const Item* arma);
    void equiparArmadura(const Item* armadura);

    // Métodos principales
    int atacar();
    void recibirDanio(int danio);
    bool curar(int puntos);
    void agregarOro(int cantidad);
    bool gastarOro(int cantidad);

    // Getters
    const char* getNombre() const;
    int getAtaque() const;
    int getDefensa() const;
    int getNivel() const;
    int getVidaActual() const;
    int getVidaMaxima() const;
    int getOro() const;
    bool estaEliminado() const;
};

#endif // PERSONAJE_H