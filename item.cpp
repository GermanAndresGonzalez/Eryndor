# include<iostream>

using namespace std;

Item::Item(int id,const char* nombre,TipoItem tipo,int bonusAtk = 0,int bonusDef = 0){
         _id=id;
        strncpy(_nombre, nombre, sizeof(_nombre) - 1);
        _nombre[sizeof(_nombre) - 1] = '\0';
         _tipo=tipo;
         _bonusAtk=bonusAtk;
         _bonusDef=bonusDef;
         }

Item::Item(){
         _id=0;
         _nombre[0] = '\0';
         _tipo = RECURSO;
         _bonusAtk=0;
         _bonusDef=0;
         }


int Item::getId()const {
    return _id;
}

const char* Item::getNombre(){
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
