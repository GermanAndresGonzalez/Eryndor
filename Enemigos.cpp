# include<iostream>
# include "Enemigos.h"

using namespace std;
   Enemigos::Enemigos(){
   _vidaActual = 0;
   _vidaMaxima = 0;
   _defensa = 0;
   _ataque = 0;
   _idEnemigo = 0;
   _oroOtorgado = 0;
   _expOtorgada = 0;
   for(int i = 0; i < 50; i++) {
            _nombre[i] = '\0';
        }

  for(int i = 0; i < 150; i++) {
            _descripcion[i] = '\0';
        }

   }

   Enemigos::Enemigos(int vidaActual, int vidaMaxima, int defensa, int ataque, int idEnemigo, int oroOtorgado, int expOtorgada, char nombre [50], char descripcion[150]){
   _vidaActual = vidaActual;
   _vidaMaxima = vidaMaxima;
   _defensa = defensa;
   _ataque = ataque;
   _idEnemigo = idEnemigo;
   _oroOtorgado = oroOtorgado;
   _expOtorgada = expOtorgada;
   _nombre = nombre;
   _descripcion = descripcion;
   }


   Enemigos::getvidaActual(){
    return _vidaActual;
   }

   Enemigos::getvidaMaxima(){
    return _vidaMaxima;
   }

   Enemigos::getdefensa(){
    return _defensa;
   }

   Enemigos::getataque(){
    return _ataque;
   }

   Enemigos::getidEnemigo(){
    return _idEnemigo;
   }

   Enemigos::getoroOtorgado(){
    return _oroOtorgado;
   }

   Enemigos::getexpOtorgada(){
    return _expOtorgada;
   }

   Enemigos::getnombre(){
    return _nombre;
   }

   Enemigos::getdescripcion(){
    return _descripcion;
   }



    void Enemigos::setvidaActual(int vidaActual){
    _vidaActual = vidaActual;
}

    void Enemigos::getvidaMaxima(int vidaMaxima){
    _vidaMaxima = vidaMaxima;
    }

    void Enemigos::getdefensa(int defensa){
    _defensa = defensa;
    }

    void Enemigos::getataque(int ataque){
    _ataque = ataque;
    }

    void Enemigos::getoroOtorgado(int oroOtorgado){
    _oroOtorgado = oroOtorgado;
    }

    void Enemigos::getexpOtorgada(int expOtorgada){
    _expOtorgada = expOtorgada;
    }

    void Enemigos::getnombre(char nombre[]){
    _nombre = nombre;
    }

    void Enemigos::getdescripcion(char descripcion[]){
    _descripcion = descripcion;
    }

