#include "ventana_cueva.h"
#include "VentanaConfirmacion.h"

#include <iostream>

// -----------------------------------------------------------------------------
// Constructor / Destructor
// -----------------------------------------------------------------------------

VentanaCueva::VentanaCueva(const std::string& title,
                           unsigned int width,
                           unsigned int height,
                           const std::string& backgroundTexturePath,
                           const std::string& soundBufferPath)
    : backgroundTexturePath(backgroundTexturePath)
    , soundBufferPath(soundBufferPath)
{
    window.create(sf::VideoMode(width, height), title, sf::Style::Titlebar | sf::Style::Close);
    window.setVerticalSyncEnabled(true);
    /*
    closeButton.setSize({36.f, 36.f});
    closeButton.setFillColor(sf::Color(170, 40, 40));
    closeButton.setOutlineThickness(2.f);
    closeButton.setOutlineColor(sf::Color::White);
    */
    closeLineA.setFillColor(sf::Color::White);
    closeLineB.setFillColor(sf::Color::White);

    loadResources();
    updateLayout();

    sound.setBuffer(soundBuffer);
    sound.setLoop(true);
    sound.play();
}

VentanaCueva::~VentanaCueva()
{
    // sf::Sound debe detenerse antes de que se destruya el SoundBuffer.
    sound.stop();
}

// -----------------------------------------------------------------------------
// Loop principal (Template Method — no virtual)
// -----------------------------------------------------------------------------

void VentanaCueva::run()
{
    while (window.isOpen())
    {
        handleEvents();
        draw();
    }
}

// -----------------------------------------------------------------------------
// Implementaciones virtuales base
// -----------------------------------------------------------------------------

void VentanaCueva::loadResources()
{
    if (!backgroundTexture.loadFromFile(backgroundTexturePath))
    {
        std::cerr << "No se pudo cargar " << backgroundTexturePath << '\n';
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    if (!soundBuffer.loadFromFile(soundBufferPath))
    {
        std::cerr << "No se pudo cargar " << soundBufferPath << '\n';
    }
}

void VentanaCueva::updateLayout()
{
    const auto windowSize = window.getSize();

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        const auto textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }

    //closeButton.setPosition(static_cast<float>(windowSize.x) - 48.f, 12.f);

    //const auto buttonPos = closeButton.getPosition();

    closeLineA.setSize({24.f, 3.f});
    //closeLineA.setPosition(buttonPos.x + 6.f, buttonPos.y + 16.f);
    closeLineA.setRotation(45.f);

    closeLineB.setSize({24.f, 3.f});
    //closeLineB.setPosition(buttonPos.x + 6.f, buttonPos.y + 16.f);
    closeLineB.setRotation(-45.f);
}

void VentanaCueva::handleEvents()
{
    sf::Event event;
    while (window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            VentanaConfirmacion dialogo("", "Deseas volver al menu anterior?");
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
        /*
        if (event.type == sf::Event::MouseButtonPressed &&
                event.mouseButton.button == sf::Mouse::Left)
        {
            const auto mousePos = window.mapPixelToCoords({event.mouseButton.x, event.mouseButton.y});

            if (closeButton.getGlobalBounds().contains(mousePos))
            {
                window.close();
            }

        }
        */
    }
}

void VentanaCueva::draw()
{
    window.clear();
    if (backgroundTexture.getSize().x > 0)
    {
        window.draw(backgroundSprite);
    }
    //window.draw(closeButton);
    //window.draw(closeLineA);
    //window.draw(closeLineB);
}
