# include<iostream>
#include "item.h"
#include <cstring>

using namespace std;
Item::Item(int id, const char* nombre, TipoItem tipo, int bonusAtk, int bonusDef, int curacion){
         _id=id;
        strncpy(_nombre, nombre, sizeof(_nombre) - 1);
        _nombre[sizeof(_nombre) - 1] = '\0';
         _tipo=tipo;
         _bonusAtaque=bonusAtk;
         _bonusDefensa=bonusDef;
         _curacion=curacion;
         }

Item::Item(){
         _id=0;
         _nombre[0] = '\0';
         _tipo = RECURSO;
         _bonusAtaque=0;
         _bonusDefensa=0;
         _curacion=0;
         }


int Item::getId()const {
    return _id;
}

const char* Item::getNombre()const{
    return _nombre;
}

TipoItem Item::getTipo() const {
    return _tipo;
}

int Item::getBonusAtaque() const{
    return _bonusAtaque;
}

int Item::getBonusDefensa() const {
    return _bonusDefensa;
}
int Item::getCuracion()const{
    return _curacion;
}
