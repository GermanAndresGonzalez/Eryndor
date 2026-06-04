#ifndef INVENTARIO_H_INCLUDED
#define INVENTARIO_H_INCLUDED

struct SlotInventario
{
    int idItem;
    int cantidad;
};

class Inventario
{
private:
    SlotInventario _slotsTotales[100];
    int _cantidadDeSlotsOcupados;

public:

    Inventario();

    void agregarItem(int id, int cantidad);

    bool quitarItem(int id, int cantidad);

    int obtenerCantidad(int id) const;

    bool tieneCantidadNecesaria(int id, int cantidad) const;
};

#endif // INVENTARIO_H_INCLUDED
