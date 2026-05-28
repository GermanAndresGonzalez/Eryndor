#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED

#include <cstddef>

class Enemigos {
    private:
    int _vidaActual, _vidaMaxima, _defensa, _ataque, _idEnemigo, _oroOtorgado, _expOtorgada;
    char _nombre[50], _descripcion[150];

    public:
    Enemigos();
    Enemigos(int vidaActual, int vidaMaxima, int defensa, int ataque, int idEnemigo, int oroOtorgado, int expOtorgada, char nombre [50], char descripcion[150]);


    int getvidaActual() const;
    int getvidaMaxima() const;
    int getdefensa() const;
    int getataque() const;
    int getidEnemigo() const;
    int getoroOtorgado() const;
    int getexpOtorgada() const;
    const char* getnombre() const;
    const char* getdescripcion() const;


    void setvidaActual(int vidaActual);
    void setvidaMaxima(int vidaMaxima);
    void setdefensa(int defensa);
    void setataque(int ataque);
    void setidEnemigo(int idEnemigo);
    void setoroOtorgado(int oroOtorgado);
    void setexpOtorgada(int expOtorgada);
    void setnombre(char nombre[50]);
    void setdescripcion(char descripcion [150]);


};

#endif // ENEMIGOS_H_INCLUDED

