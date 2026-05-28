#include "botonera.h"
#include <iostream>

//Botonera::Botonera(float x, float y, float ancho, float alto, sf::Color color) {
Botonera::Botonera(const float coordenadas[], sf::Color color)
{
    fondo.setSize(sf::Vector2f(coordenadas[2], coordenadas[3]));
    fondo.setPosition(coordenadas[0], coordenadas[1]);
    fondo.setFillColor(color);

    // Borde opcional
    fondo.setOutlineThickness(2.f);
    fondo.setOutlineColor(sf::Color::White);

    cantidadBotones = 0;

    if (!fuente.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "Error cargando fuente" << std::endl;
    }
}

Botonera::Botonera(const float coordenadas[], sf::Color color, int personaje)
{
    fondo.setSize(sf::Vector2f(coordenadas[2], coordenadas[3]));
    fondo.setPosition(coordenadas[0], coordenadas[1]);
    fondo.setFillColor(color);

    // Borde opcional
    fondo.setOutlineThickness(2.f);
    fondo.setOutlineColor(sf::Color::White);

    cantidadBotones = 0;

    if (!fuente.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "Error cargando fuente" << std::endl;
    }
    std::string ruta="recursos/imag/Jugadores/";
    switch(personaje)
    {
    case 0:
        ruta+="Cabeza_jugador1.png";
        break;
    case 1:
        ruta+="Cabeza_jugador2.png";
        break;

    }
    sf:: Texture texturaCabeza;
    if (!texturaCabeza.loadFromFile(ruta))
    {
        std::cerr << "Error al cargando cabeza de jugador" << std::endl;
    }
    spCabezaJugador.setTexture(texturaCabeza);
    float x= coordenadas[0];
    float y=coordenadas[1];
    spCabezaJugador.setPosition(x,y);



}








Botonera::Botonera(const float coordenadas[], sf::Color color,
                   const std::string etiquetas[], int n)
    : Botonera(coordenadas, color)
      //Botonera(coordenadas[], color)
{
    // Limitar a máximo 9 botones
    if (n > 9) n = 9;
    cantidadBotones = n;

    int columnas = 3;
    float margen = 10.f;
    float anchoBoton = (coordenadas[2] - (columnas + 1) * margen) / columnas;
    float altoBoton = 40.f;

    for (int i = 0; i < cantidadBotones; i++)
    {
        botones[i].setFont(fuente);
        botones[i].setString(etiquetas[i]);
        botones[i].setCharacterSize(20);
        botones[i].setFillColor(sf::Color::White);
        botones[i].setOutlineColor(sf::Color::Black);
        botones[i].setOutlineThickness(1.f);

        // Calcular posición en grilla
        int fila = i / columnas;
        int col = i % columnas;

        float posX = coordenadas[0] + margen + col * (anchoBoton + margen);
        float posY = coordenadas[1] + margen + fila * (altoBoton + margen);

        botones[i].setPosition(posX, posY);
    }
}

Botonera::~Botonera()
{
    // Nada que liberar manualmente
}

void Botonera::draw(sf::RenderWindow& window) const
{
    window.draw(fondo);
    for (int i = 0; i < cantidadBotones; i++)
    {
        window.draw(botones[i]);
    }
}

int Botonera::obtenerClickeado(int mouseX, int mouseY) const
{
    for (int i = 0; i < cantidadBotones; ++i)
    {
        if (botones[i].getGlobalBounds().contains(static_cast<float>(mouseX),
                static_cast<float>(mouseY)))
        {
            return i;
        }
    }

    return -1;
}
