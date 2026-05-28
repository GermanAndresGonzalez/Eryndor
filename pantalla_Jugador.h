#pragma once

#include <SFML/Graphics.hpp>

#include "pantalla_resultado.h"

class PantallaJugador {
public:
    PantallaJugador();

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    void limpiarSeleccion();
    int getJugadorSeleccionado() const { return jugadorSeleccionado; }

private:
    void ubicarElementos(const sf::Vector2u& windowSize);
    void actualizarHover(const sf::Vector2f& mousePos);

    sf::Font font;
    sf::Text titulo;
    sf::Text leyendaJugador1;
    sf::Text leyendaJugador2;
    sf::Texture texturaJugador1;
    sf::Texture texturaJugador2;
    sf::Sprite spriteJugador1;
    sf::Sprite spriteJugador2;
    sf::RectangleShape marcoJugador1;
    sf::RectangleShape marcoJugador2;
    bool hoverJugador1 = false;
    bool hoverJugador2 = false;
    int jugadorSeleccionado = 0;
};