#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED

#include <cstddef>

class Enemigos {
    private:
    int _vidaActual, _vidaMaxima, _defensa, _ataque, _idEnemigo, _oroOtorgado, _expOtorgada;
    bool _eliminado;
    char _nombre[50], _descripcion[150];

    public:
    Enemigos();
    Enemigos(int vidaActual, int vidaMaxima, int defensa, int ataque, int idEnemigo, int oroOtorgado, int expOtorgada, const char* nombre, const char* descripcion);


    int getvidaActual() const;
    int getvidaMaxima() const;
    int getdefensa() const;
    int getataque() const;
    int getidEnemigo() const;
    int getoroOtorgado() const;
    int getexpOtorgada() const;
    const char* getnombre() const;
    const char* getdescripcion() const;
    int atacar();
    void recibirDanio(int danio);
    bool estaEliminado() const;

    int getVidaActual() const { return getvidaActual(); }
    int getVidaMaxima() const { return getvidaMaxima(); }
    int getDefensa() const { return getdefensa(); }
    int getAtaque() const { return getataque(); }
    int getIdEnemigo() const { return getidEnemigo(); }
    int getOroOtorgado() const { return getoroOtorgado(); }
    int getExpOtorgada() const { return getexpOtorgada(); }
    const char* getNombre() const { return getnombre(); }
    const char* getDescripcion() const { return getdescripcion(); }


    void setvidaActual(int vidaActual);
    void setvidaMaxima(int vidaMaxima);
    void setdefensa(int defensa);
    void setataque(int ataque);
    void setidEnemigo(int idEnemigo);
    void setoroOtorgado(int oroOtorgado);
    void setexpOtorgada(int expOtorgada);
    void setnombre(const char* nombre);
    void setdescripcion(const char* descripcion);


};

#endif // ENEMIGOS_H_INCLUDED

