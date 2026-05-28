#include <iostream>
#include <cstring>

class Personaje {
private:
    char nombre[50];
    int nivel, vidaActual, vidaMaxima, ataque, defensa, oro;
    bool eliminado;

public:
    // Constructor: se llama automáticamente al crear un Personaje
    Personaje(const char* nom, int niv, int vidaMax, int atk, int def, int oroInicial, bool elim) {
        strncpy(nombre, nom, 49);
        nombre[49] = '\0';
        
        nivel = niv;
        vidaMaxima = vidaMax;
        vidaActual = vidaMax;   // Empieza con la vida al máximo
        ataque = atk;
        defensa = def;
        oro = oroInicial;
        eliminado = elim;
    }

    // Métodos principales
    int atacar() {
        int danio = ataque + (nivel * 2);
        //std::cout << nombre << " ataca causando " << danio << " de daño.\n";
        return danio;
    }

    void recibirDanio(int danio) {
        if (estaEliminado()) {
            //std::cout << nombre << " ya está eliminado.\n";
            return;
        }
        int danioReal = danio - defensa;
        if (danioReal < 0) danioReal = 0;
        vidaActual -= danioReal;
        if (vidaActual < 0){
            vidaActual = 0;
        }
        if (vidaActual == 0) eliminado = true;
        //std::cout << nombre << " recibe " << danioReal << " de daño. Vida: " << vidaActual << "/" << vidaMaxima << "\n";
    }

    void curar(int puntos) {
        if (estaEliminado()) return;
        vidaActual += puntos;
        if (vidaActual > vidaMaxima) vidaActual = vidaMaxima;
        //std::cout << nombre << " se cura. Vida: " << vidaActual << "/" << vidaMaxima << "\n";
    }

    void agregarOro(int cantidad) {
        oro += cantidad;
    }

    bool gastarOro(int cantidad) {
        if (oro >= cantidad) {
            oro -= cantidad;
            return true;
        }
        return false;
    }

    // Getters (solo lectura)
    const char* getNombre() const { return nombre; }
    int getAtaque() const { return ataque; }
    int getDefensa() const { return defensa; }
    int getNivel() const { return nivel; }
    int getVidaActual() const { return vidaActual; }
    int getVidaMaxima() const { return vidaMaxima; }
    int getOro() const { return oro; }
    bool estaEliminado() const { return eliminado; }
};