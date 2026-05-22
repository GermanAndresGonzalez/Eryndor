#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include "MenuPrincipal.h"

using namespace sf;

enum Estado { MENU, JUGANDO, OPCIONES, ACERCA };

int main()
{
    RenderWindow ventana(VideoMode(1280, 720), "Las Profundidades de Eryndor", Style::Default);
    ventana.setFramerateLimit(60);

    // --- Música ---
    Music musica;
    if (!musica.openFromFile("recursos/sonido/monsters-cave.flac"))
    {
        std::cerr << "No se pudo cargar recursos/sonido/monsters-cave.flac" << std::endl;
    }
    else
    {
        musica.setLoop(true);
        musica.setVolume(75.f);
        musica.play();
    }

    // --- Texturas ---
    Texture texturaPrincipal;
    if (!texturaPrincipal.loadFromFile("recursos/imag/cueva_titulo.png"))
        std::cerr << "No se encontro la imagen: recursos/imag/cueva_titulo.png" << std::endl;

    Texture texturaSecundaria;
    if (!texturaSecundaria.loadFromFile("recursos/imag/cueva.png"))
        std::cerr << "No se encontro la imagen: recursos/imag/cueva.png" << std::endl;

    RectangleShape fondo(Vector2f(1280, 720));
    fondo.setTexture(&texturaPrincipal);

    RectangleShape fondoJugar(Vector2f(1280, 720));
    fondoJugar.setTexture(&texturaSecundaria);

    RectangleShape fondoOpciones(Vector2f(1280, 720));
    fondoOpciones.setTexture(&texturaSecundaria);

    RectangleShape fondoAcerca(Vector2f(1280, 720));
    fondoAcerca.setTexture(&texturaSecundaria);

    // --- Menú y estado ---
    MenuPrincipal menuPrincipal(ventana.getSize().x, ventana.getSize().y);
    Estado estadoActual = MENU;

    // --- Loop principal ---
    while (ventana.isOpen())
    {
        // Hover del mouse (fuera del pollEvent para que sea continuo)
        if (estadoActual == MENU)
        {
            Vector2i posMouse = Mouse::getPosition(ventana);
            for (int i = 0; i < Max_main_menu; i++)
            {
                // ResaltarItem solo cambia color si el ítem es diferente al actual,
                // así no interfiere con la navegación por teclado
                if (menuPrincipal.EstaEnBounds(i, posMouse.x, posMouse.y))
                {
                    menuPrincipal.ResaltarItem(i);
                    break;
                }
            }
        }

        Event evento;
        while (ventana.pollEvent(evento))
        {
            if (evento.type == Event::Closed)
                ventana.close();

            if (evento.type == Event::KeyReleased)
            {
                if (estadoActual == MENU)
                {
                    if (evento.key.code == Keyboard::Up)
                        menuPrincipal.MoverArriba();
                    else if (evento.key.code == Keyboard::Down)
                        menuPrincipal.MoverAbajo();
                    else if (evento.key.code == Keyboard::Return)
                    {
                        int seleccion = menuPrincipal.MenuPrincipalPresionado();
                        if (seleccion == 0) estadoActual = JUGANDO;
                        if (seleccion == 1) estadoActual = OPCIONES;
                        if (seleccion == 2) estadoActual = ACERCA;
                        if (seleccion == 3) ventana.close();
                    }
                }
                else
                {
                    if (evento.key.code == Keyboard::Escape)
                        estadoActual = MENU;
                }
            }

            // Clic izquierdo del mouse
            if (evento.type == Event::MouseButtonReleased)
            {
                if (evento.mouseButton.button == Mouse::Left && estadoActual == MENU)
                {
                    int clickeado = menuPrincipal.ObtenerClickeado(
                        evento.mouseButton.x,
                        evento.mouseButton.y
                    );
                    if (clickeado == 0) estadoActual = JUGANDO;
                    if (clickeado == 1) estadoActual = OPCIONES;
                    if (clickeado == 2) estadoActual = ACERCA;
                    if (clickeado == 3) ventana.close();
                }
            }
        }

        // --- Render ---
        ventana.clear();

        switch (estadoActual)
        {
            case MENU:
                ventana.draw(fondo);
                menuPrincipal.dibujar(ventana);
                break;
            case JUGANDO:
                ventana.draw(fondoJugar);
                break;
            case OPCIONES:
                ventana.draw(fondoOpciones);
                break;
            case ACERCA:
                ventana.draw(fondoAcerca);
                break;
        }

        ventana.display();
    }

    return 0;
}
