#ifndef ITEMS_JUEGO_H_INCLUDED
#define ITEMS_JUEGO_H_INCLUDED

#include "item.h"

enum IdItem
{
    HIERRO = 1,
    MADERA = 2,
    HONGOS_MAGICOS = 3,

    ESPADA_MADERA = 4,
    ESPADA_HIERRO = 5,

    ESCUDO_MADERA = 6,
    ESCUDO_HIERRO = 7,

    POCION_CURATIVA = 8
};

Item obtenerItemPorId(int id);

#endif // ITEMS_JUEGO_H_INCLUDED
