#pragma once

class Partidas
{
public:
    int id;
    int idPersonaje;
    int idNivel;
    bool eliminado;

    Partidas();
    Partidas(int id, int idPersonaje, int idNivel);

    int getId() const;
    int getIdPersonaje() const;
    int getIdNivel() const;
    bool estaEliminada() const;

    bool GuardarPartida(const char* nombreArchivo = "recursos/archivos/partidas.dat");
    bool CargarPartida(int idBuscado, const char* nombreArchivo = "recursos/archivos/partidas.dat");
    int ContarRegistros() const;
};
