#include "pantalla_jugar.h"

#include <iostream>

namespace
// x,y, ancho, alto
{
const float coordenadasTexto[]= {0.f, 0.f, 1280.f, 100.f};
const float coordenadasFoto[]= {75.f, 500.f, 150.f, 125.f};
const float coordenadasAcciones[]= {650.f, 500.f, 450.f, 100.f};
//const float coordenadasAcciones[]= {650.f, 500.f, 500.f, 125.f};

const std::string acciones[] =
{
    "Mover",
    "Examinar",
    "Usar",
    "Mapa",
    "Inventario",
    "Volver"
};
}


PantallaJugar::PantallaJugar()
//: botoneraTexto(0.f, 0.f, 1280.f, 100.f, sf::Color(0, 0, 0, 150))
    : botoneraTexto(coordenadasTexto, sf::Color(0, 0, 0, 150))
    , botoneraFoto(coordenadasFoto, sf::Color(0, 0, 0, 150), 1)
    , botoneraAcciones(coordenadasAcciones, sf::Color(0, 0, 0, 150), acciones, 6)
{
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "PantallaJugar: no se pudo cargar la fuente\n";
    }

    if (!backgroundTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png"))
    {
        std::cerr << "PantallaJugar: no se pudo cargar recursos/imag/cueva_1280x720.png\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    titulo.setFont(font);
    titulo.setString("Pantalla Jugar");
    titulo.setCharacterSize(42);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);

    textoJugador.setFont(font);
    textoJugador.setCharacterSize(24);
    textoJugador.setFillColor(sf::Color::White);
    textoJugador.setOutlineColor(sf::Color::Black);
    textoJugador.setOutlineThickness(1.f);

    textoInstrucciones.setFont(font);
    textoInstrucciones.setString("Instrucciones");
    textoInstrucciones.setCharacterSize(24);
    textoInstrucciones.setFillColor(sf::Color::White);
    textoInstrucciones.setOutlineColor(sf::Color::Black);
    textoInstrucciones.setOutlineThickness(1.f);

    actualizarTextoJugador();
    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 110.f);
    textoInstrucciones.setPosition(750.f,620.f);
}

void PantallaJugar::setJugadorSeleccionado(int jugador)
{
    jugadorSeleccionado = (jugador == 2) ? 2 : 1;
    botoneraFoto.setPersonaje(jugadorSeleccionado);
    actualizarTextoJugador();
}

void PantallaJugar::actualizarTextoJugador()
{
    const std::string nombre = (jugadorSeleccionado == 2) ? "Lyra Voss" : "Kael Draven";
    textoJugador.setString("Personaje: " + nombre);
}

void PantallaJugar::updateLayout(const sf::RenderWindow& window)
{
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        const auto windowSize = window.getSize();
        const auto textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }

    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 92.f);
    textoInstrucciones.setPosition(750.f,620.f);
}

PantallaResultado PantallaJugar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
    {
        return PantallaResultado::VolverMenu;
    }

    if (event.type == sf::Event::MouseButtonPressed &&
            event.mouseButton.button == sf::Mouse::Left)
    {
        const auto mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
        const int clic = botoneraAcciones.obtenerClickeado(
                             static_cast<int>(mousePos.x),
                             static_cast<int>(mousePos.y));

        if (clic == 2)
        {
            return PantallaResultado::VolverMenu;
        }
    }

    return PantallaResultado::Nada;
}

void PantallaJugar::draw(sf::RenderWindow& window) const
{
    if (backgroundTexture.getSize().x > 0)
    {
        window.draw(backgroundSprite);
    }

    window.draw(titulo);
    window.draw(textoJugador);
    window.draw(textoInstrucciones);
    botoneraTexto.draw(window);
    botoneraFoto.draw(window);
    botoneraAcciones.draw(window);
}
