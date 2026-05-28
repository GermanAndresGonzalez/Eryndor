#ifndef ENEMIGOS_H_INCLUDED
#define ENEMIGOS_H_INCLUDED

class Enemigos {
    private:
    int _vidaActual, _vidaMaxima, _defensa, _ataque, _idEnemigo, _oroOtorgado, _expOtorgada;
    char _nombre[50], _descripcion[150];

    public:
    Enemigos();
    Enemigos(int vidaActual, int vidaMaxima, int defensa, int ataque, int idEnemigo, int oroOtorgado, int expOtorgada, char nombre [50], char descripcion[150]);


    int getvidaActual();
    int getvidaMaxima();
    int getdefensa();
    int getataque();
    int getidEnemigo();
    int getoroOtorgado();
    int getexpOtorgada();
    char getnombre();
    char getdescripcion();


    void setvidaActual(int vidaActual);
    void setvidaMaxima(int vidaMaxima);
    void setdefensa(int defensa);
    void setataque(int ataque);
    void setidEnemigo(int ataque);
    void setoroOtorgado(int oroOtorgado);
    void setexpOtorgada(int expOtorgada);
    void setnombre(char nombre[50]);
    void setdescripcion(char descripcion [150]);


};

#endif // ENEMIGOS_H_INCLUDED

