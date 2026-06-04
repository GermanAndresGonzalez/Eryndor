#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "pantalla_resultado.h"

class PantallaOpciones {
public:
    PantallaOpciones();

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

private:
    void posicionarElementos(const sf::Vector2u& windowSize);
    void resaltarBoton(int indice);

    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Font    font;
    sf::Text    titulo;
    sf::Text    mensaje;
    sf::Text    botones[2];
    sf::RectangleShape marcoBotones[2];
    int botonSeleccionado = -1;
    std::string mensajeEstado;
};