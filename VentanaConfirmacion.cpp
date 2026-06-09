#include "VentanaConfirmacion.h"
#include <iostream>

VentanaConfirmacion::VentanaConfirmacion(const std::string& titulo, const std::string& mensaje)
{
    if (!fondoTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png"))
    {
        std::cerr << "PantallaJugar: no se pudo cargar el fondo\n";
    }
    else
    {
        fondoSprite.setTexture(fondoTexture);
    }




    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "No se pudo cargar la fuente\n";
    }

    // Fondo semitransparente
    fondo.setSize(sf::Vector2f(600.f, 300.f));
    fondo.setFillColor(sf::Color(0, 0, 0, 180));
    fondo.setOutlineColor(sf::Color::White);
    fondo.setOutlineThickness(2.f);
    fondo.setPosition(340.f, 210.f); // centrado aprox en 1280x720

    textoTitulo.setFont(font);
    textoTitulo.setString(titulo);
    textoTitulo.setCharacterSize(28);
    textoTitulo.setFillColor(sf::Color::White);

    textoMensaje.setFont(font);
    textoMensaje.setString(mensaje);
    textoMensaje.setCharacterSize(22);
    textoMensaje.setFillColor(sf::Color::White);

    // Botón Sí
    botonSi.setSize(sf::Vector2f(120.f, 50.f));

    botonSi.setFillColor(sf::Color(50, 58, 122));

    botonSi.setPosition(fondo.getPosition().x + 100.f, fondo.getPosition().y + 200.f);

    textoSi.setFont(font);
    textoSi.setString("Si");
    textoSi.setCharacterSize(22);
    textoSi.setFillColor(sf::Color::White);
    centrarTexto(textoSi, botonSi);

    // Botón No
    botonNo.setSize(sf::Vector2f(120.f, 50.f));

    botonNo.setFillColor(sf::Color(50, 58, 122));
    botonNo.setPosition(fondo.getPosition().x + 380.f, fondo.getPosition().y + 200.f);

    textoNo.setFont(font);
    textoNo.setString("No");
    textoNo.setCharacterSize(22);
    textoNo.setFillColor(sf::Color::White);
    centrarTexto(textoNo, botonNo);





    // Posicionar textos
    textoTitulo.setPosition(fondo.getPosition().x + 20.f, fondo.getPosition().y + 30.f);

    //centrarTexto(textoMensaje,fondo);
    textoMensaje.setPosition(fondo.getPosition().x + 35.f, fondo.getPosition().y + 70.f);
}

void VentanaConfirmacion::centrarTexto(sf::Text& texto, const sf::RectangleShape& rect)
{
    auto bounds = texto.getLocalBounds();
    texto.setOrigin(bounds.left + bounds.width / 2.f, bounds.top + bounds.height / 2.f);
    texto.setPosition(rect.getPosition().x + rect.getSize().x / 2.f,
                      rect.getPosition().y + rect.getSize().y / 2.f);
}

bool VentanaConfirmacion::mostrar(sf::RenderWindow& window)
{
    // Loop modal dentro de la misma ventana
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
                return false;
            }
            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            {
                sf::Vector2f mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});
                if (botonSi.getGlobalBounds().contains(mousePos))
                {
                    return true;  // ✅ Sí
                }
                if (botonNo.getGlobalBounds().contains(mousePos))
                {
                    return false; // ❌ No
                }
            }
        }

        // Dibujar overlay encima de la ventana principal
        //window.clear(sf::Color::Black); // ⚠️ opcional: si querés mantener lo que había, no hagas clear
        window.draw(fondoSprite);
        window.draw(fondo);
        window.draw(textoTitulo);
        window.draw(textoMensaje);
        window.draw(botonSi);
        window.draw(botonNo);
        window.draw(textoSi);
        window.draw(textoNo);
        window.display();
    }
    return false;
}
