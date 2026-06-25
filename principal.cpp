
//#include "escena_menu.h"
#include "principal.h"
#include "VentanaConfirmacion.h"

#include <iostream>

namespace
{

}

MenuPrincipal2::MenuPrincipal2()
    : VentanaCueva("Las Profundidades de Eryndor",
                   1280,
                   720,
                   "./recursos/imag/Cueva/cueva_titulo.png",
                   "./recursos/sonido/dark-tunnel-ambience.flac")
    , menu(1280.f, 720.f)
      // //botoneraIzquierda(55.f, 390.f, 540.f, 250.f, sf::Color(0, 0, 0, 150), botoneraIzquierdaOpciones, 3)
      //, //botoneraDerecha(685.f, 390.f, 540.f, 250.f, sf::Color(0, 0, 0, 150), botoneraDerechaOpciones, 3)
{
    if (!pantallaJuegoTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png"))
    {
        std::cerr << "MenuPrincipal2: no se pudo cargar recursos/imag/cueva_1280x720.png\n";
    }
    else
    {
        pantallaJuegoSprite.setTexture(pantallaJuegoTexture);
    }
}

void MenuPrincipal2::updateLayout()
{
    VentanaCueva::updateLayout();

    if (pantallaJuegoTexture.getSize().x > 0 && pantallaJuegoTexture.getSize().y > 0)
    {
        const auto windowSize = window.getSize();
        const auto textureSize = pantallaJuegoTexture.getSize();
        pantallaJuegoSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }
}

void MenuPrincipal2::entrarAJuego()
{
    pantallaActual = Pantalla::Juego;
}

void MenuPrincipal2::volverAlMenu()
{
    pantallaActual = Pantalla::Menu;
}

void MenuPrincipal2::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            VentanaConfirmacion dialogo("", "Realmente deseas salir?");
            bool respuesta = dialogo.mostrar(window);
            if (respuesta)
            {
                window.close();
            }
        }

        if (event.type == sf::Event::Resized)
        {
            window.setView(sf::View(sf::FloatRect(
                                        0.f, 0.f,
                                        static_cast<float>(event.size.width),
                                        static_cast<float>(event.size.height))));
            updateLayout();
        }

        if (pantallaActual == Pantalla::Juego)
        {
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Escape)
            {
                volverAlMenu();
            }

            continue;
        }

        if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
        {
            const auto mousePos = window.mapPixelToCoords(
            {event.mouseButton.x, event.mouseButton.y});

            // Botón X de la ventana (comportamiento base)
            if (closeButton.getGlobalBounds().contains(mousePos))
            {
                VentanaConfirmacion dialogo("", "Realmente deseas salir?");
                bool respuesta = dialogo.mostrar(window);
                if (respuesta)
                {
                    window.close();
                }
                return;
            }

            int clickeado = menu.obtenerClickeado(
                                static_cast<int>(mousePos.x),
                                static_cast<int>(mousePos.y));

            if (clickeado >= 0)
            {
                if (clickeado == 0)
                {
                    entrarAJuego();
                }
                else
                {
                    opcionElegida = clickeado;
                    VentanaConfirmacion dialogo("", "Realmente deseas salir?");
                    bool respuesta = dialogo.mostrar(window);
                    if (respuesta)
                    {
                        window.close();
                    }
                }
            }
        }

        if (event.type == sf::Event::MouseMoved)
        {
            menu.obtenerHover(event.mouseMove.x, event.mouseMove.y);
        }

        if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Up)    menu.moverArriba();
            if (event.key.code == sf::Keyboard::Down)  menu.moverAbajo();

            if (event.key.code == sf::Keyboard::Return && menu.haySeleccion())
            {
                if (menu.getSeleccionado() == 0)
                {
                    entrarAJuego();
                }
                else
                {
                    opcionElegida = menu.getSeleccionado();
                    VentanaConfirmacion dialogo("", "Realmente deseas salir?");
                    bool respuesta = dialogo.mostrar(window);
                    if (respuesta)
                    {
                        window.close();
                    }
                }
            }
        }
    }
}

void MenuPrincipal2::draw()
{
    if (pantallaActual == Pantalla::Menu)
    {
        VentanaCueva::draw();
        menu.dibujar(window);
    }
    else
    {
        window.clear();
        if (pantallaJuegoTexture.getSize().x > 0)
        {
            window.draw(pantallaJuegoSprite);
        }
        //botoneraIzquierda.draw(window);
        //botoneraDerecha.draw(window);
    }
    window.display();
}

