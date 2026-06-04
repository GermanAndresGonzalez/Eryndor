#include "partidas.h"

#include "archivos.h"

Partidas::Partidas()
{
    id = 0;
    idPersonaje = 0;
    idNivel = 0;
    eliminado = false;
}

Partidas::Partidas(int id, int idPersonaje, int idNivel)
{
    this->id = id;
    this->idPersonaje = idPersonaje;
    this->idNivel = idNivel;
    eliminado = false;
}

int Partidas::getId() const
{
    return id;
}

int Partidas::getIdPersonaje() const
{
    return idPersonaje;
}

int Partidas::getIdNivel() const
{
    return idNivel;
}

bool Partidas::estaEliminada() const
{
    return eliminado;
}

bool Partidas::GuardarPartida(const char* nombreArchivo)
{
    ArchivoBinario<Partidas> archivo(nombreArchivo);
    const int posicion = archivo.BuscarPosicionPorID(id);

    if (posicion >= 0)
    {
        return archivo.Modificar(posicion, *this);
    }

    return archivo.Agregar(*this);
}

bool Partidas::CargarPartida(int idBuscado, const char* nombreArchivo)
{
    ArchivoBinario<Partidas> archivo(nombreArchivo);
    return archivo.BuscarPorID(idBuscado, *this);
}