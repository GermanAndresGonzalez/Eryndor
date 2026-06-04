#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

#include "archivos.h"

struct SlotInventario
{
    int idItem;
    int cantidad;
};

class Inventario
{
public:
    int id;
    bool eliminado;

    Inventario();

    int getId() const;
    void setId(int nuevoId);

    bool GuardarInventario(const char* nombreArchivo = "recursos/archivos/inventarios.dat");
    bool CargarInventario(int idBuscado, const char* nombreArchivo = "recursos/archivos/inventarios.dat");

    void agregarItem(int id, int cantidad);

    bool quitarItem(int id, int cantidad);

    int obtenerCantidad(int id) const;

    bool tieneCantidadNecesaria(int id, int cantidad) const;

private:
    SlotInventario _slotsTotales[100];
    int _cantidadDeSlotsOcupados;
};

#endif // INVENTARIO_H_INCLUDED
