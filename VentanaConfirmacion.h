#pragma once
#include <SFML/Graphics.hpp>

class VentanaConfirmacion {
public:
    VentanaConfirmacion(const std::string& titulo, const std::string& mensaje);

    // Devuelve true si el usuario presiona "Sí", false si "No" o cierra
    bool mostrar(sf::RenderWindow& window);
    void resaltarBoton(int i);

private:
    sf::Texture fondoTexture;
    sf::Sprite  fondoSprite;
    sf::RectangleShape fondo;
    sf::Text textoTitulo;
    sf::Text textoMensaje;
    sf::Font font;

    sf::RectangleShape botonSi;
    sf::RectangleShape botonNo;
    sf::Text textoSi;
    sf::Text textoNo;

    void centrarTexto(sf::Text& texto, const sf::RectangleShape& rect);
};
