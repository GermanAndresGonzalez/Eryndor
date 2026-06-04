#include "ITEMS JUEGO.h"

Item obtenerItemPorId(int id)
{
    switch(id)
    {
    case HIERRO:    //Con el enum utilizado antes HIERRO es lo mismo que decir 1. ASI QUE SERIA ID INGRESADA=1
        return Item(
            HIERRO,
            "Hierro",
            RECURSO
        );

    case MADERA: //ACA MADERA ES 2. ETC ETC
        return Item(
            MADERA,
            "Madera",
            RECURSO
        );

    case HONGOS_MAGICOS:
        return Item(
            HONGOS_MAGICOS,
            "Hongos Magicos",
            RECURSO
        );

    case ESPADA_MADERA:
        return Item(
            ESPADA_MADERA,
            "Espada de Madera",
            ARMA,
            3,
            0
        );

    case ESPADA_HIERRO:
        return Item(
            ESPADA_HIERRO,
            "Espada de Hierro",
            ARMA,
            7,
            0
        );

    case ESCUDO_MADERA:
        return Item(
            ESCUDO_MADERA,
            "Escudo de Madera",
            ARMADURA,
            0,
            3
        );

    case ESCUDO_HIERRO:
        return Item(
            ESCUDO_HIERRO,
            "Escudo de Hierro",
            ARMADURA,
            0,
            7
        );

    case POCION_CURATIVA:
        return Item(
            POCION_CURATIVA,
            "Pocion Curativa",
            CONSUMIBLE,
            0,
            0,
            25
        );
     default:
        return Item();
    }
}
