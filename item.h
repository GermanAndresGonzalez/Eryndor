#ifndef ITEM_H_INCLUDED
#define ITEM_H_INCLUDED

enum TipoItem
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

public:
    Item();
    Item(int id,
         const char* nombre,
         TipoItem tipo,
         int bonusAtk = 0,
         int bonusDef = 0);

    int getId() const;
    const char* getNombre() const;
    TipoItem getTipo() const;

    int getBonusAtaque() const;
    int getBonusDefensa() const;
};


#endif // ITEM_H_INCLUDED
