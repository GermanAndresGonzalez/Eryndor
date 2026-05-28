#include "botonera.h"
#include <algorithm>
#include <iostream>

//Botonera::Botonera(float x, float y, float ancho, float alto, sf::Color color) {
Botonera::Botonera(const float coordenadas[], sf::Color color)
    : personajeActual(0)
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
    : personajeActual(0)
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
    setPersonaje(personaje);



}

void Botonera::actualizarSpriteCabeza()
{
    if (texturaCabezaJugador.getSize().x == 0 || texturaCabezaJugador.getSize().y == 0)
    {
        return;
    }

    spCabezaJugador.setTexture(texturaCabezaJugador, true);

    const auto fondoBounds = fondo.getGlobalBounds();
    const auto texturaSize = texturaCabezaJugador.getSize();
    const float padding = 10.f;
    const float anchoDisponible = std::max(0.f, fondoBounds.width - padding * 2.f);
    const float altoDisponible = std::max(0.f, fondoBounds.height - padding * 2.f);
    const float escalaX = anchoDisponible / static_cast<float>(texturaSize.x);
    const float escalaY = altoDisponible / static_cast<float>(texturaSize.y);
    const float escala = std::min(escalaX, escalaY);

    spCabezaJugador.setScale(escala, escala);

    const auto spriteBounds = spCabezaJugador.getGlobalBounds();
    spCabezaJugador.setPosition(
        fondoBounds.left + (fondoBounds.width - spriteBounds.width) / 2.f,
        fondoBounds.top + (fondoBounds.height - spriteBounds.height) / 2.f);
}

void Botonera::setPersonaje(int personaje)
{
    personajeActual = (personaje == 2) ? 2 : 1;

    std::string ruta = "recursos/imag/Jugadores/";
    if (personajeActual == 2)
    {
        ruta += "Chico_j2.png";
    }
    else
    {
        ruta += "Chico_j1.png";
    }

    if (!texturaCabezaJugador.loadFromFile(ruta))
    {
        std::cerr << "Error al cargar cabeza de jugador" << std::endl;
        return;
    }

    actualizarSpriteCabeza();
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
    window.draw(spCabezaJugador);
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
