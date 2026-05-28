#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "botonera.h"
#include "pantalla_resultado.h"

class PantallaJugar {
public:
    PantallaJugar();

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void setJugadorSeleccionado(int jugadorSeleccionado);
    int getJugadorSeleccionado() const { return jugadorSeleccionado; }

private:
    void actualizarTextoJugador();

    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Font    font;
    sf::Text    titulo;
    sf::Text    textoJugador;

    Botonera botoneraTexto;
    Botonera botoneraFoto;
    Botonera botoneraAcciones;
    int jugadorSeleccionado = 1;
};
