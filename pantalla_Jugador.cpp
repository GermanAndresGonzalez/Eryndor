#include "pantalla_Jugador.h"

#include <algorithm>
#include <iostream>

namespace
{
const float maxFotoAncho = 240.f;
const float maxFotoAlto = 240.f;
const float separacionFotos = 90.f;

void centrarTexto(sf::Text& texto)
{
    const auto bounds = texto.getLocalBounds();
    texto.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
}
}

PantallaJugador::PantallaJugador()
{
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf")) {
        std::cerr << "PantallaJugador: no se pudo cargar la fuente\n";
    }

    if (!texturaJugador1.loadFromFile("recursos/imag/Jugadores/Cabeza_jugador1.png")) {
        std::cerr << "PantallaJugador: no se pudo cargar Cabeza_jugador1.png\n";
    }

    if (!texturaJugador2.loadFromFile("recursos/imag/Jugadores/Cabeza_jugador2.png")) {
        std::cerr << "PantallaJugador: no se pudo cargar Cabeza_jugador2.png\n";
    }

    spriteJugador1.setTexture(texturaJugador1);
    spriteJugador2.setTexture(texturaJugador2);

    titulo.setFont(font);
    titulo.setString("Elige tu personaje");
    titulo.setCharacterSize(44);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);

    leyendaJugador1.setFont(font);
    leyendaJugador1.setString("Kael Draven");
    leyendaJugador1.setCharacterSize(24);
    leyendaJugador1.setFillColor(sf::Color::White);
    leyendaJugador1.setOutlineColor(sf::Color::Black);
    leyendaJugador1.setOutlineThickness(1.f);

    leyendaJugador2.setFont(font);
    leyendaJugador2.setString("Lyra Voss");
    leyendaJugador2.setCharacterSize(24);
    leyendaJugador2.setFillColor(sf::Color::White);
    leyendaJugador2.setOutlineColor(sf::Color::Black);
    leyendaJugador2.setOutlineThickness(1.f);

    marcoJugador1.setFillColor(sf::Color::Transparent);
    marcoJugador1.setOutlineColor(sf::Color::White);
    marcoJugador1.setOutlineThickness(0.f);

    marcoJugador2.setFillColor(sf::Color::Transparent);
    marcoJugador2.setOutlineColor(sf::Color::White);
    marcoJugador2.setOutlineThickness(0.f);

    ubicarElementos(sf::Vector2u{1280u, 720u});
}

void PantallaJugador::limpiarSeleccion()
{
    jugadorSeleccionado = 0;
}

void PantallaJugador::ubicarElementos(const sf::Vector2u& windowSize)
{
    const float centroX = static_cast<float>(windowSize.x) / 2.f;
    const float fotosY = static_cast<float>(windowSize.y) / 2.f - 140.f;
    const float tituloY = 55.f;

    titulo.setPosition(centroX, tituloY);
    centrarTexto(titulo);

    auto prepararSprite = [&](sf::Sprite& sprite, sf::RectangleShape& marco, const sf::Texture& textura) -> sf::Vector2f
    {
        if (textura.getSize().x == 0 || textura.getSize().y == 0) {
            sprite.setScale(1.f, 1.f);
            sprite.setPosition(0.f, fotosY);
            marco.setPosition(0.f, fotosY);
            marco.setSize(sf::Vector2f(maxFotoAncho, maxFotoAlto));
            return sf::Vector2f(maxFotoAncho, maxFotoAlto);
        }

        const float escalaX = maxFotoAncho / static_cast<float>(textura.getSize().x);
        const float escalaY = maxFotoAlto / static_cast<float>(textura.getSize().y);
        const float escala = std::min(escalaX, escalaY);

        sprite.setScale(escala, escala);
        const auto bounds = sprite.getGlobalBounds();
        marco.setSize(sf::Vector2f(bounds.width, bounds.height));
        return sf::Vector2f(bounds.width, bounds.height);
    };

    const auto tamanio1 = prepararSprite(spriteJugador1, marcoJugador1, texturaJugador1);
    const auto tamanio2 = prepararSprite(spriteJugador2, marcoJugador2, texturaJugador2);

    const float anchoGrupo = tamanio1.x + separacionFotos + tamanio2.x;
    const float inicioX = centroX - anchoGrupo / 2.f;
    const float centroFoto1 = inicioX + tamanio1.x / 2.f;
    const float centroFoto2 = inicioX + tamanio1.x + separacionFotos + tamanio2.x / 2.f;

    spriteJugador1.setPosition(centroFoto1 - tamanio1.x / 2.f, fotosY);
    spriteJugador2.setPosition(centroFoto2 - tamanio2.x / 2.f, fotosY);
    marcoJugador1.setPosition(spriteJugador1.getPosition());
    marcoJugador2.setPosition(spriteJugador2.getPosition());

    leyendaJugador1.setPosition(centroFoto1, fotosY + tamanio1.y + 30.f);
    leyendaJugador2.setPosition(centroFoto2, fotosY + tamanio2.y + 30.f);
    centrarTexto(leyendaJugador1);
    centrarTexto(leyendaJugador2);

    marcoJugador1.setOutlineThickness(hoverJugador1 || jugadorSeleccionado == 1 ? 4.f : 0.f);
    marcoJugador2.setOutlineThickness(hoverJugador2 || jugadorSeleccionado == 2 ? 4.f : 0.f);
}

void PantallaJugador::actualizarHover(const sf::Vector2f& mousePos)
{
    hoverJugador1 = spriteJugador1.getGlobalBounds().contains(mousePos);
    hoverJugador2 = spriteJugador2.getGlobalBounds().contains(mousePos);

    marcoJugador1.setOutlineThickness(hoverJugador1 || jugadorSeleccionado == 1 ? 4.f : 0.f);
    marcoJugador2.setOutlineThickness(hoverJugador2 || jugadorSeleccionado == 2 ? 4.f : 0.f);
}

PantallaResultado PantallaJugador::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape) {
        limpiarSeleccion();
        return PantallaResultado::VolverMenu;
    }

    if (event.type == sf::Event::MouseMoved) {
        actualizarHover(window.mapPixelToCoords({event.mouseMove.x, event.mouseMove.y}));
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        const auto mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

        if (spriteJugador1.getGlobalBounds().contains(mousePos)) {
            jugadorSeleccionado = 1;
            actualizarHover(mousePos);
            return PantallaResultado::SeleccionHecha;
        }

        if (spriteJugador2.getGlobalBounds().contains(mousePos)) {
            jugadorSeleccionado = 2;
            actualizarHover(mousePos);
            return PantallaResultado::SeleccionHecha;
        }
    }

    return PantallaResultado::Nada;
}

void PantallaJugador::updateLayout(const sf::RenderWindow& window)
{
    ubicarElementos(window.getSize());
}

void PantallaJugador::draw(sf::RenderWindow& window) const
{
    window.draw(titulo);
    window.draw(spriteJugador1);
    window.draw(spriteJugador2);
    window.draw(marcoJugador1);
    window.draw(marcoJugador2);
    window.draw(leyendaJugador1);
    window.draw(leyendaJugador2);
}
