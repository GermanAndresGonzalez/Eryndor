#include "crafteo.h"

bool Crafteo::crearPocionCurativa(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HONGOS_MAGICOS, 3))
    {
        return false;
    }

    inventario.quitarItem(HONGOS_MAGICOS, 3);

    inventario.agregarItem(POCION_CURATIVA, 1);

    return true;
}

bool Crafteo::crearEspadaMadera(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(MADERA, 5))
    {
        return false;
    }

    inventario.quitarItem(MADERA, 5);

    inventario.agregarItem(ESPADA_MADERA, 1);

    return true;
}

bool Crafteo::crearEspadaHierro(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HIERRO, 5))
    {
        return false;
    }

    inventario.quitarItem(HIERRO, 5);

    inventario.agregarItem(ESPADA_HIERRO, 1);

    return true;
}

bool Crafteo::crearEscudoMadera(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(MADERA, 5))
    {
        return false;
    }

    inventario.quitarItem(MADERA, 5);

    inventario.agregarItem(ESCUDO_MADERA, 1);

    return true;
}

bool Crafteo::crearEscudoHierro(Inventario& inventario)
{
    if (!inventario.tieneCantidadNecesaria(HIERRO, 5))
    {
        return false;
    }

    inventario.quitarItem(HIERRO, 5);

    inventario.agregarItem(ESCUDO_HIERRO, 1);

    return true;
}
