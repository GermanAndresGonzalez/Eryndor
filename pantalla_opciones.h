#pragma once

#include <SFML/Graphics.hpp>

#include "pantalla_resultado.h"

class PantallaOpciones {
public:
    PantallaOpciones();

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

private:
    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Font    font;
    sf::Text    titulo;
    sf::Text    mensaje;
};