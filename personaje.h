#ifndef PERSONAJE_H
#define PERSONAJE_H

class Personaje {
private:
    char nombre[50];
    int nivel, vidaActual, vidaMaxima, ataque, defensa, oro;
    bool eliminado;

public:
    // Constructor
    Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim);

    // Métodos principales
    int atacar();
    void recibirDanio(int danio);
    void curar(int puntos);
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