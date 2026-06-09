#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#include "pantalla_resultado.h"

class PantallaOpciones {
public:
    PantallaOpciones();
    ~PantallaOpciones();

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    bool cargarPartidaPorId(int idPartida);

private:
    int intCantBotones;
    void posicionarElementos(const sf::Vector2u& windowSize);
    void posicionarPanelInventario(const sf::Vector2u& windowSize);
    void resaltarBoton(int indice);
    void actualizarTextoInventario();
    sf::RectangleShape* botonesPartidas;
    sf::Text* textoBotonesPartidas;


    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Font    font;
    sf::Text    titulo;
    sf::Text    mensaje;
    sf::Text    botones[2];
    sf::Text textoInventario;
    sf::RectangleShape marcoBotones[2];
    int botonSeleccionado = -1;
    sf::RectangleShape panelInventario;
    std::string mensajeEstado;
};
