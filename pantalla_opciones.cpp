#include "pantalla_opciones.h"

#include "archivos.h"
#include "partidas.h"


#include <algorithm>
#include <cstring>
#include <iostream>
#include <sstream>

namespace
{
const char* archivoPartidas    = "recursos/archivos/partidas.dat";
Partidas partidaActual;

}
PantallaOpciones::PantallaOpciones()
{
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "PantallaOpciones: no se pudo cargar la fuente\n";
    }

    if (!backgroundTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png"))
    {
        std::cerr << "PantallaOpciones: no se pudo cargar recursos/imag/cueva_1280x720.png\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }
    auto configurarTexto = [&](sf::Text& t, unsigned int size)
    {
        t.setFont(font);
        t.setCharacterSize(size);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1.f);
    };

    configurarTexto(textoInventario,    18);

    titulo.setFont(font);
    titulo.setString("Opciones de partida");
    titulo.setCharacterSize(42);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);

    panelInventario.setFillColor(sf::Color(0, 0, 0, 170));
    panelInventario.setOutlineThickness(2.f);
    panelInventario.setOutlineColor(sf::Color::White);

    mensaje.setFont(font);
    mensaje.setString("Presiona C para cargar la partida guardada o V para volver.");
    mensaje.setCharacterSize(24);
    mensaje.setFillColor(sf::Color::White);
    mensaje.setOutlineColor(sf::Color::Black);
    mensaje.setOutlineThickness(1.f);



    const std::string etiquetas[] = {"Cargar partida", "Volver"};
    for (int i = 0; i < 2; ++i)
    {
        botones[i].setFont(font);
        botones[i].setString(etiquetas[i]);
        botones[i].setCharacterSize(34);
        botones[i].setFillColor(sf::Color::White);
        botones[i].setOutlineColor(sf::Color::Black);
        botones[i].setOutlineThickness(1.5f);

        marcoBotones[i].setFillColor(sf::Color(0, 0, 0, 150));
        marcoBotones[i].setOutlineColor(sf::Color::White);
        marcoBotones[i].setOutlineThickness(2.f);
    }

    posicionarElementos(sf::Vector2u{1280u, 720u});
    posicionarPanelInventario(sf::Vector2u{1280u, 720u});
    actualizarTextoInventario();
}

PantallaOpciones::~PantallaOpciones()
{
    delete[] botonesPartidas;
    delete[] textoBotonesPartidas;
}

void PantallaOpciones::updateLayout(const sf::RenderWindow& window)
{
    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        const auto windowSize = window.getSize();
        const auto textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }

    posicionarElementos(window.getSize());
    posicionarPanelInventario(window.getSize());
    actualizarTextoInventario();

}


void PantallaOpciones::posicionarPanelInventario(const sf::Vector2u& windowSize)
{
    const float panelAncho = 320.f;
    const float panelAlto  = 260.f;
    const float panelX     = 80.f;
    const float panelY     = static_cast<float>(windowSize.y) / 2.f - panelAlto / 2.f - 60.f;

    panelInventario.setPosition(panelX, panelY);
    panelInventario.setSize(sf::Vector2f(panelAncho, panelAlto));
    textoInventario.setPosition(panelX + 20.f, panelY + 18.f);
}

void PantallaOpciones::actualizarTextoInventario()
{
    std::ostringstream salida;

    ArchivoBinario<Partidas> archivoPartidasBin(archivoPartidas);

    int cantRegistros=archivoPartidasBin.ContarRegistros();
    if (cantRegistros == 0)
    {
        salida << "No hay partidas encontradas.";
        return;
    }
    else
    {

        salida << "Ultimas " << cantRegistros << " partidas:\n";
        textoInventario.setString(salida.str());
        int limite =(cantRegistros>10) ? cantRegistros-10:0;

        intCantBotones=(cantRegistros>10) ? 10:cantRegistros;
        botonesPartidas = new sf::RectangleShape[intCantBotones];
        textoBotonesPartidas = new sf::Text[intCantBotones];

        if (botonesPartidas==nullptr)
        {
            exit(0);
        }
        Partidas partida;
        for (int i = cantRegistros - 1; i >= limite; i--)
        {
            if (archivoPartidasBin.BuscarPorID(i, partida))
                //if (!partida.estaEliminada())
                {
                    botonesPartidas[i].setSize(sf::Vector2f(150,50));
                    botonesPartidas[i].setFillColor(sf::Color(0, 0, 0, 150));
                    botonesPartidas[i].setPosition(100.f, 100.f + i * 70.f);

                    textoBotonesPartidas[i].setFont(font);
                    textoBotonesPartidas[i].setCharacterSize(20);
                    textoBotonesPartidas[i].setFillColor(sf::Color::White);
                    std::string textoPartida= "Partida #" + std::to_string(partida.getId());
                    textoBotonesPartidas[i].setString(textoPartida);


                    //salida << "Numero de partida: " << partida.getId() << "\n";
                }
        }
    }


    //salida << "\n " << "Cantidad de registros: " << archivoPartidasBin.ContarRegistros() << "\n";




}


void PantallaOpciones::posicionarElementos(const sf::Vector2u& windowSize)
{
    const float botonX = static_cast<float>(windowSize.x) / 2.f - 120.f;
    const float botonY = 230.f;
    const float separacion = 75.f;

    titulo.setPosition(60.f, 40.f);
    mensaje.setPosition(60.f, 110.f);



    for (int i = 0; i < 2; ++i)
    {
        const float currentY = botonY + separacion * static_cast<float>(i);
        const auto bounds = botones[i].getLocalBounds();
        botones[i].setPosition(botonX, currentY);
        botones[i].setOrigin(bounds.left, bounds.top);

        marcoBotones[i].setPosition(botonX - 18.f, currentY - 10.f);
        marcoBotones[i].setSize(sf::Vector2f(280.f, 56.f));
    }
}

void PantallaOpciones::resaltarBoton(int indice)
{
    botonSeleccionado = indice;
    botones[0].setFillColor(sf::Color::White);
    botones[1].setFillColor(sf::Color::White);
    if (indice >= 0 && indice < 2)
    {
        botones[indice].setFillColor(sf::Color(120, 200, 255));
    }
}

PantallaResultado PantallaOpciones::handleEvent(const sf::Event& event, sf::RenderWindow&)
{
    if (event.type == sf::Event::MouseMoved)
    {
        for (int i = 0; i < 2; ++i)
        {
            if (marcoBotones[i].getGlobalBounds().contains(static_cast<float>(event.mouseMove.x), static_cast<float>(event.mouseMove.y)))
            {
                resaltarBoton(i);
                break;
            }
        }
    }

    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        const sf::Vector2f mousePos(static_cast<float>(event.mouseButton.x), static_cast<float>(event.mouseButton.y));

        for (int i = 0; i < 2; ++i)
        {
            if (marcoBotones[i].getGlobalBounds().contains(mousePos))
            {
                resaltarBoton(i);

                if (i == 0)
                {
                    ArchivoBinario<Partidas> archivoPartidas("recursos/archivos/partidas.dat");
                    if (archivoPartidas.ContarRegistros() == 0)
                    {
                        mensaje.setString("No hay partida guardada.");
                        return PantallaResultado::Nada;
                    }

                    return PantallaResultado::CargarPartida;
                }

                return PantallaResultado::VolverMenu;
            }
        }
    }

    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::C)
        {
            ArchivoBinario<Partidas> archivoPartidas("recursos/archivos/partidas.dat");
            if (archivoPartidas.ContarRegistros() == 0)
            {
                mensaje.setString("No hay partida guardada.");
                return PantallaResultado::Nada;
            }

            resaltarBoton(0);
            return PantallaResultado::CargarPartida;
        }

        if (event.key.code == sf::Keyboard::V || event.key.code == sf::Keyboard::Escape)
        {
            resaltarBoton(1);
            return PantallaResultado::VolverMenu;
        }

        if (event.key.code == sf::Keyboard::Return && botonSeleccionado >= 0)
        {
            if (botonSeleccionado == 0)
            {
                ArchivoBinario<Partidas> archivoPartidas("recursos/archivos/partidas.dat");
                if (archivoPartidas.ContarRegistros() == 0)
                {
                    mensaje.setString("No hay partida guardada.");
                    return PantallaResultado::Nada;
                }

                return PantallaResultado::CargarPartida;
            }

            return PantallaResultado::VolverMenu;
        }
    }

    return PantallaResultado::Nada;
}

void PantallaOpciones::draw(sf::RenderWindow& window) const
{
    if (backgroundTexture.getSize().x > 0)
    {
        window.draw(backgroundSprite);
    }


    window.draw(titulo);
    window.draw(mensaje);
    for (int i = 0; i < 2; ++i)
    {
        window.draw(marcoBotones[i]);
        window.draw(botones[i]);
    }
    window.draw(panelInventario);
    window.draw(textoInventario);
    for (int i = 0; i < intCantBotones; i++)
    {
        window.draw(botonesPartidas[i]);
        window.draw(textoBotonesPartidas[i]);
    }

}

bool PantallaOpciones::cargarPartidaPorId(int idPartida)
{

    ArchivoBinario<Partidas> archivoPartidasBin(archivoPartidas);

    if (!archivoPartidasBin.BuscarPorID(idPartida, partidaActual))
    {
        return false;
    }
    std::cout << archivoPartidasBin.ContarRegistros();
    return true;
}
