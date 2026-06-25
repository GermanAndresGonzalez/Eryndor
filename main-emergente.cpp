#include <SFML/Graphics.hpp>
#include <iostream>

#include "VentanaConfirmacion.h"

int main()
{
    sf::RenderWindow ventanaPrincipal(
        sf::VideoMode(800, 600),
        "Ventana principal",
        sf::Style::Default);
    ventanaPrincipal.setFramerateLimit(60);

    sf::Font font;
    font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf");

    sf::Text instrucciones;
    instrucciones.setFont(font);
    instrucciones.setCharacterSize(22);
    instrucciones.setFillColor(sf::Color::White);
    instrucciones.setString("Presiona ENTER para abrir el dialogo de confirmacion.");
    instrucciones.setPosition(60.f, 270.f);

    sf::Text resultado;
    resultado.setFont(font);
    resultado.setCharacterSize(26);
    resultado.setPosition(60.f, 320.f);

    VentanaConfirmacion dialogo;

    while (ventanaPrincipal.isOpen())
    {
        sf::Event event;
        while (ventanaPrincipal.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                ventanaPrincipal.close();

            if (event.type == sf::Event::KeyPressed &&
                event.key.code == sf::Keyboard::Return)
            {
                // Se pasa la ventana principal para que sea deshabilitada.
                bool respuesta = dialogo.mostrar(
                    ventanaPrincipal,
                    "Confirmar accion",
                    "Estas seguro de que deseas continuar?");

                if (respuesta)
                {
                    resultado.setFillColor(sf::Color::Green);
                    resultado.setString("Respondiste: Si (true)");
                }
                else
                {
                    resultado.setFillColor(sf::Color(220, 60, 60));
                    resultado.setString("Respondiste: No (false)");
                }

                std::cout << "Resultado: " << (respuesta ? "true" : "false") << '\n';
            }
        }

        ventanaPrincipal.clear(sf::Color(50, 50, 50));
        ventanaPrincipal.draw(instrucciones);
        ventanaPrincipal.draw(resultado);
        ventanaPrincipal.display();
    }

    return 0;
}
