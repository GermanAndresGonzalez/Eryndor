#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

enum TipoItem //Esto los numera. recurso es 0 arma 1 armadura 2 y consumible 3.
{
    RECURSO,
    ARMA,
    ARMADURA,
    CONSUMIBLE
};
class Item
{
private:
    int _id;
    char _nombre[50];
    TipoItem _tipo;

    int _bonusAtaque;
    int _bonusDefensa;
    int _curacion;

public:
    Item();
    Item(int id,
         const char* nombre,
         TipoItem tipo,
         int bonusAtk = 0,
         int bonusDef = 0,
         int curacion = 0);

    int getId() const;
    const char* getNombre() const;
    TipoItem getTipo() const;

    int getBonusAtaque() const;
    int getBonusDefensa() const;
    int getCuracion() const;
};


#endif // ITEM_H_INCLUDED
