#ifndef CRAFTEO_H_INCLUDED
#define CRAFTEO_H_INCLUDED

#include "inventario.h"
#include "ITEMS JUEGO.h"

class Crafteo
{
public:

    static bool crearPocionCurativa(Inventario& inventario);

    static bool crearEspadaMadera(Inventario& inventario);

    static bool crearEspadaHierro(Inventario& inventario);

    static bool crearEscudoMadera(Inventario& inventario);

    static bool crearEscudoHierro(Inventario& inventario);
};

#endif // CRAFTEO_H_INCLUDED
