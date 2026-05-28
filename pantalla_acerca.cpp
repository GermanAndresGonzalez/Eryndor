#include "pantalla_acerca.h"

#include <iostream>

PantallaAcerca::PantallaAcerca()
{
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf")) {
        std::cerr << "PantallaAcerca: no se pudo cargar la fuente\n";
    }

    if (!backgroundTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png")) {
        std::cerr << "PantallaAcerca: no se pudo cargar recursos/imag/cueva_1280x720.png\n";
    } else {
        backgroundSprite.setTexture(backgroundTexture);
    }

    titulo.setFont(font);
    titulo.setString("Acerca de");
    titulo.setCharacterSize(42);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);
    titulo.setPosition(60.f, 40.f);

    mensaje.setFont(font);
    mensaje.setString("Pantalla en construccion. Presiona ESC para volver.");
    mensaje.setCharacterSize(24);
    mensaje.setFillColor(sf::Color::White);
    mensaje.setOutlineColor(sf::Color::Black);
    mensaje.setOutlineThickness(1.f);
    mensaje.setPosition(60.f, 110.f);
}

void PantallaAcerca::updateLayout(const sf::RenderWindow& window)
{
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0) {
        const auto windowSize = window.getSize();
        const auto textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }
}

PantallaResultado PantallaAcerca::handleEvent(const sf::Event& event, sf::RenderWindow&)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        return PantallaResultado::VolverMenu;
    }

    return PantallaResultado::Nada;
}

void PantallaAcerca::draw(sf::RenderWindow& window) const
{
    if (backgroundTexture.getSize().x > 0) {
        window.draw(backgroundSprite);
    }

    window.draw(titulo);
    window.draw(mensaje);
}
