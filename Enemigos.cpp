#include <cstring>
#include <iostream>

#include "Enemigos.h"

using namespace std;
   Enemigos::Enemigos(){
   _vidaActual = 0;
   _vidaMaxima = 0;
   _defensa = 0;
   _ataque = 0;
   _idEnemigo = 0;
   _oroOtorgado = 0;
   _expOtorgada = 0;
   _eliminado = false;
   for(int i = 0; i < 50; i++) {
            _nombre[i] = '\0';
        }

  for(int i = 0; i < 150; i++) {
            _descripcion[i] = '\0';
        }

   }

    Enemigos::Enemigos(int vidaActual, int vidaMaxima, int defensa, int ataque, int idEnemigo, int oroOtorgado, int expOtorgada, const char* nombre, const char* descripcion){
   _vidaActual = vidaActual;
   _vidaMaxima = vidaMaxima;
   _defensa = defensa;
   _ataque = ataque;
   _idEnemigo = idEnemigo;
   _oroOtorgado = oroOtorgado;
   _expOtorgada = expOtorgada;
   _eliminado = (_vidaActual <= 0);
    std::strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
    std::strncpy(_descripcion, descripcion, sizeof(_descripcion) - 1);
    _descripcion[sizeof(_descripcion) - 1] = '\0';
   }


    int Enemigos::getvidaActual() const{
    return _vidaActual;
   }

    int Enemigos::getvidaMaxima() const{
    return _vidaMaxima;
   }

    int Enemigos::getdefensa() const{
    return _defensa;
   }

    int Enemigos::getataque() const{
    return _ataque;
   }

    int Enemigos::getidEnemigo() const{
    return _idEnemigo;
   }

    int Enemigos::getoroOtorgado() const{
    return _oroOtorgado;
   }

    int Enemigos::getexpOtorgada() const{
    return _expOtorgada;
   }

    const char* Enemigos::getnombre() const{
    return _nombre;
   }

    const char* Enemigos::getdescripcion() const{
    return _descripcion;
   }

    int Enemigos::atacar(){
    return _ataque + (_idEnemigo * 2);
    }

    void Enemigos::recibirDanio(int danio){
    if (_eliminado) {
        return;
    }

    int danioReal = danio - _defensa;
    if (danioReal < 0) {
        danioReal = 0;
    }

    _vidaActual -= danioReal;
    if (_vidaActual < 0) {
        _vidaActual = 0;
    }

    if (_vidaActual == 0) {
        _eliminado = true;
    }
    }

    bool Enemigos::estaEliminado() const{
    return _eliminado;
    }



    void Enemigos::setvidaActual(int vidaActual){
    _vidaActual = vidaActual;
    _eliminado = (_vidaActual <= 0);
}

    void Enemigos::setvidaMaxima(int vidaMaxima){
    _vidaMaxima = vidaMaxima;
    }

    void Enemigos::setdefensa(int defensa){
    _defensa = defensa;
    }

    void Enemigos::setataque(int ataque){
    _ataque = ataque;
    }

    void Enemigos::setidEnemigo(int idEnemigo){
    _idEnemigo = idEnemigo;
    }

    void Enemigos::setoroOtorgado(int oroOtorgado){
    _oroOtorgado = oroOtorgado;
    }

    void Enemigos::setexpOtorgada(int expOtorgada){
    _expOtorgada = expOtorgada;
    }

    void Enemigos::setnombre(const char* nombre){
    std::strncpy(_nombre, nombre, sizeof(_nombre) - 1);
    _nombre[sizeof(_nombre) - 1] = '\0';
    }

    void Enemigos::setdescripcion(const char* descripcion){
    std::strncpy(_descripcion, descripcion, sizeof(_descripcion) - 1);
    _descripcion[sizeof(_descripcion) - 1] = '\0';
    }

