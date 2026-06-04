#include <iostream>
#include "inventario.h"

using namespace std;

Inventario::Inventario()
{
    id = 0;
    eliminado = false;
    _cantidadDeSlotsOcupados = 0;
      for (int i = 0; i < 100; i++)
    {
                _slotsTotales[i].idItem = 0;
                _slotsTotales[i].cantidad = 0;
    }
}

int Inventario::getId() const
{
    return id;
}

void Inventario::setId(int nuevoId)
{
    id = nuevoId;
}

bool Inventario::GuardarInventario(const char* nombreArchivo)
{
    ArchivoBinario<Inventario> archivo(nombreArchivo);
    const int posicion = archivo.BuscarPosicionPorID(id);

    if (posicion >= 0)
    {
        return archivo.Modificar(posicion, *this);
    }

    return archivo.Agregar(*this);
}

bool Inventario::CargarInventario(int idBuscado, const char* nombreArchivo)
{
    ArchivoBinario<Inventario> archivo(nombreArchivo);
    return archivo.BuscarPorID(idBuscado, *this);
}


void Inventario::agregarItem(int id, int cantidad)
{
    // 1. buscar si ya existe el item
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            _slotsTotales[i].cantidad += cantidad;
            return;
        }
    }

    // 2. si no existe, crear nuevo slot
    if (_cantidadDeSlotsOcupados < 100)
    {
        _slotsTotales[_cantidadDeSlotsOcupados].idItem = id;
        _slotsTotales[_cantidadDeSlotsOcupados].cantidad = cantidad;
        _cantidadDeSlotsOcupados++;
    }
}

bool Inventario::quitarItem(int id, int cantidad)
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            if (_slotsTotales[i].cantidad < cantidad)
            {
                return false;
            }

            _slotsTotales[i].cantidad -= cantidad;

            // si queda en 0, eliminar slot
            if (_slotsTotales[i].cantidad == 0)
            {
                for (int j = i; j < _cantidadDeSlotsOcupados - 1; j++)
                {
                    _slotsTotales[j] = _slotsTotales[j + 1];
                }

                _cantidadDeSlotsOcupados--;
            }

            return true;
        }
    }

    return false;
}


int Inventario::obtenerCantidad(int id) const
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return _slotsTotales[i].cantidad;
        }
    }

    return 0;
}

bool Inventario::tieneCantidadNecesaria(int id, int cantidad) const
{
    for (int i = 0; i < _cantidadDeSlotsOcupados; i++)
    {
        if (_slotsTotales[i].idItem == id)
        {
            return _slotsTotales[i].cantidad >= cantidad;
        }
    }

    return false;
}
