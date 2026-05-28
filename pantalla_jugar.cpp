#include "pantalla_jugar.h"

#include <algorithm>
#include <iostream>
#include <memory>
#include <random>
#include <sstream>

namespace
// x,y, ancho, alto
{
const float coordenadasTexto[]= {2.f, 2.f, 1278.f, 100.f};
const float coordenadasAcciones[]= {650.f, 560.f, 450.f, 100.f};

const std::string acciones[] =
{
    "[A] Atacar",
    "[C] Curar",
    "[R] Rendirse"
};

struct PlantillaEnemigo
{
    const char* imagen;
    const char* nombre;
    const char* descripcion;
    int vidaMaxima;
    int defensa;
    int ataque;
    int oroOtorgado;
    int expOtorgada;
};

const PlantillaEnemigo plantillasEnemigos[] =
{
    {"recursos/imag/Enemigos/aracnido.png", "Aracnido", "Una bestia de multiples patas.", 80, 5, 15, 30, 20},
    {"recursos/imag/Enemigos/engendro.png", "Engendro", "Una criatura deformada por la cueva.", 100, 8, 18, 40, 35},
    {"recursos/imag/Enemigos/serpiente.png", "Serpiente", "Un reptil rapido y venenoso.", 70, 4, 20, 25, 15}
};

std::mt19937& generadorAleatorio()
{
    static std::mt19937 generador{std::random_device{}()};
    return generador;
}

int numeroAleatorio(int minimo, int maximo)
{
    std::uniform_int_distribution<int> distribucion(minimo, maximo);
    return distribucion(generadorAleatorio());
}

std::string unirMensajes(const std::vector<std::string>& mensajes)
{
    std::ostringstream salida;
    const std::size_t limite = 5;
    const std::size_t inicio = mensajes.size() > limite ? mensajes.size() - limite : 0;

    for (std::size_t i = inicio; i < mensajes.size(); ++i)
    {
        salida << mensajes[i];
        if (i + 1 < mensajes.size())
        {
            salida << '\n';
        }
    }

    return salida.str();
}

sf::Vector2f centrarSpriteConLimite(sf::Sprite& sprite, const sf::Texture& textura,
                                    const sf::Vector2u& windowSize, float maxAncho, float maxAlto,
                                    float offsetY = 0.f)
{
    if (textura.getSize().x == 0 || textura.getSize().y == 0)
    {
        return sf::Vector2f(0.f, 0.f);
    }

    const float escalaX = maxAncho / static_cast<float>(textura.getSize().x);
    const float escalaY = maxAlto / static_cast<float>(textura.getSize().y);
    const float escala = std::min(escalaX, escalaY);
    sprite.setScale(escala, escala);

    const auto bounds = sprite.getGlobalBounds();
    const float posX = static_cast<float>(windowSize.x) / 2.f - bounds.width / 2.f;
    const float posY = static_cast<float>(windowSize.y) / 2.f - bounds.height / 2.f + offsetY;
    sprite.setPosition(posX, posY);

    return sf::Vector2f(bounds.width, bounds.height);
}
}


PantallaJugar::PantallaJugar()
    //: botoneraTexto(coordenadasTexto, sf::Color(0, 0, 0, 150))
    : botoneraAcciones(coordenadasAcciones, sf::Color(0, 0, 0, 150), acciones, 3)
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
    titulo.setString("Batalla por turnos entre:");
    titulo.setCharacterSize(42);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);

    textoJugador.setFont(font);
    textoJugador.setCharacterSize(24);
    textoJugador.setFillColor(sf::Color::White);
    textoJugador.setOutlineColor(sf::Color::Black);
    textoJugador.setOutlineThickness(1.f);

    cargarJugadorSeleccionado();
    /*
    textoInstrucciones.setFont(font);
    textoInstrucciones.setString("Batalla por turnos");
    textoInstrucciones.setCharacterSize(24);
    textoInstrucciones.setFillColor(sf::Color::White);
    textoInstrucciones.setOutlineColor(sf::Color::Black);
    textoInstrucciones.setOutlineThickness(1.f);
    */
    textoEstadoHeroe.setFont(font);
    textoEstadoHeroe.setCharacterSize(20);
    textoEstadoHeroe.setFillColor(sf::Color::White);
    textoEstadoHeroe.setOutlineColor(sf::Color::Black);
    textoEstadoHeroe.setOutlineThickness(1.f);

    textoEstadoEnemigo.setFont(font);
    textoEstadoEnemigo.setCharacterSize(20);
    textoEstadoEnemigo.setFillColor(sf::Color::White);
    textoEstadoEnemigo.setOutlineColor(sf::Color::Black);
    textoEstadoEnemigo.setOutlineThickness(1.f);

    textoLogCombate.setFont(font);
    textoLogCombate.setCharacterSize(19);
    textoLogCombate.setFillColor(sf::Color::White);
    textoLogCombate.setOutlineColor(sf::Color::Black);
    textoLogCombate.setOutlineThickness(1.f);

    textoControles.setFont(font);
    textoControles.setCharacterSize(18);
    textoControles.setFillColor(sf::Color::White);
    textoControles.setOutlineColor(sf::Color::Black);
    textoControles.setOutlineThickness(1.f);

    panelCombate.setFillColor(sf::Color(0, 0, 0, 170));
    panelCombate.setOutlineThickness(2.f);
    panelCombate.setOutlineColor(sf::Color::White);

    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 92.f);
    //textoInstrucciones.setPosition(60.f, 130.f);

    reiniciarBatalla();
}

void PantallaJugar::cargarEnemigoAleatorio()
{
    indiceEnemigo = numeroAleatorio(0, 2);
    const auto& plantilla = plantillasEnemigos[indiceEnemigo];

    if (!enemigoTexture.loadFromFile(plantilla.imagen))
    {
        std::cerr << "PantallaJugar: no se pudo cargar " << plantilla.imagen << '\n';
        return;
    }

    enemigoSprite.setTexture(enemigoTexture, true);
    posicionarPanelCombate(ultimaVentanaSize);

    enemigo.reset(new Enemigos(
        plantilla.vidaMaxima,
        plantilla.vidaMaxima,
        plantilla.defensa,
        plantilla.ataque,
        indiceEnemigo + 1,
        plantilla.oroOtorgado,
        plantilla.expOtorgada,
        plantilla.nombre,
        plantilla.descripcion));
}

void PantallaJugar::cargarJugadorSeleccionado()
{
    const char* ruta = (jugadorSeleccionado == 2)
        ? "recursos/imag/Jugadores/Cabeza_jugador2.png"
        : "recursos/imag/Jugadores/Cabeza_jugador1.png";

    if (!jugadorTexture.loadFromFile(ruta))
    {
        std::cerr << "PantallaJugar: no se pudo cargar " << ruta << '\n';
        return;
    }

    jugadorSprite.setTexture(jugadorTexture, true);
}

void PantallaJugar::posicionarSpritesCombate(const sf::Vector2u& windowSize)
{
    if (jugadorTexture.getSize().x == 0 || jugadorTexture.getSize().y == 0 ||
        enemigoTexture.getSize().x == 0 || enemigoTexture.getSize().y == 0)
    {
        return;
    }

    const float maxAncho = 140.f;
    const float maxAlto = 140.f;
    const float separacion = 100.f;
    const float centroY = static_cast<float>(windowSize.y) / 2.f - 70.f;

    const float escalaJugadorX = maxAncho / static_cast<float>(jugadorTexture.getSize().x);
    const float escalaJugadorY = maxAlto / static_cast<float>(jugadorTexture.getSize().y);
    const float escalaJugador = std::min(escalaJugadorX, escalaJugadorY);
    jugadorSprite.setScale(escalaJugador, escalaJugador);

    const float escalaEnemigoX = maxAncho / static_cast<float>(enemigoTexture.getSize().x);
    const float escalaEnemigoY = maxAlto / static_cast<float>(enemigoTexture.getSize().y);
    const float escalaEnemigo = std::min(escalaEnemigoX, escalaEnemigoY);
    enemigoSprite.setScale(escalaEnemigo, escalaEnemigo);

    const auto boundsJugadorLocal = jugadorSprite.getLocalBounds();
    const auto boundsEnemigoLocal = enemigoSprite.getLocalBounds();

    jugadorSprite.setOrigin(
        boundsJugadorLocal.left + boundsJugadorLocal.width / 2.f,
        boundsJugadorLocal.top + boundsJugadorLocal.height / 2.f);

    enemigoSprite.setOrigin(
        boundsEnemigoLocal.left + boundsEnemigoLocal.width / 2.f,
        boundsEnemigoLocal.top + boundsEnemigoLocal.height / 2.f);

    const auto boundsJugador = jugadorSprite.getGlobalBounds();
    const auto boundsEnemigo = enemigoSprite.getGlobalBounds();

    const float totalAncho = boundsJugador.width + separacion + boundsEnemigo.width;
    const float inicioX = static_cast<float>(windowSize.x) / 2.f - totalAncho / 2.f;

    jugadorSprite.setPosition(inicioX + boundsJugador.width / 2.f, centroY);
    enemigoSprite.setPosition(inicioX + boundsJugador.width + separacion + boundsEnemigo.width / 2.f, centroY);
}

void PantallaJugar::reiniciarBatalla()
{
    const char* nombreHeroe = (jugadorSeleccionado == 2) ? "Lyra Voss" : "Kael Draven";
    heroe.reset(new Personaje(nombreHeroe, 5, 100, 20, 10, 50, false));
    pocionesRestantes = 3;
    turnoCombate = 0;
    combateFinalizado = false;
    victoria = false;
    mensajesCombate.clear();

    actualizarTextoJugador();
    cargarJugadorSeleccionado();
    cargarEnemigoAleatorio();
    posicionarSpritesCombate(ultimaVentanaSize);
    posicionarPanelCombate(ultimaVentanaSize);
    registrarMensaje("La batalla comienza contra " + std::string(enemigo->getnombre()) + ".");
    registrarMensaje("Usa A para atacar, C para curar y R para rendirte.");
    actualizarTextosCombate();
}

void PantallaJugar::setJugadorSeleccionado(int jugador)
{
    jugadorSeleccionado = (jugador == 2) ? 2 : 1;
    cargarJugadorSeleccionado();
    reiniciarBatalla();
}

void PantallaJugar::actualizarTextoJugador()
{
    const std::string nombre = (jugadorSeleccionado == 2) ? "Lyra Voss" : "Kael Draven";
    textoJugador.setString("Personaje elegido: " + nombre);
}

void PantallaJugar::registrarMensaje(const std::string& mensaje)
{
    mensajesCombate.push_back(mensaje);
    while (mensajesCombate.size() > 8)
    {
        mensajesCombate.erase(mensajesCombate.begin());
    }
}

void PantallaJugar::actualizarTextosCombate()
{
    if (heroe)
    {
        textoEstadoHeroe.setString(
            std::string("Jugador: ") + heroe->getNombre() +
            "  HP: " + std::to_string(heroe->getVidaActual()) + "/" + std::to_string(heroe->getVidaMaxima()) +
            "  ATK: " + std::to_string(heroe->getAtaque()) +
            "  DEF: " + std::to_string(heroe->getDefensa()) +
            "  Oro: " + std::to_string(heroe->getOro()));
    }

    if (enemigo)
    {
        textoEstadoEnemigo.setString(
            std::string("Enemigo: ") + enemigo->getnombre() +
            "  HP: " + std::to_string(enemigo->getVidaActual()) + "/" + std::to_string(enemigo->getVidaMaxima()) +
            "  ATK: " + std::to_string(enemigo->getAtaque()) +
            "  DEF: " + std::to_string(enemigo->getDefensa()));
    }

    textoLogCombate.setString(unirMensajes(mensajesCombate));

    if (combateFinalizado)
    {
        textoControles.setString("Pulsa ESC para volver a la pantalla anterior.");
    }
    else
    {
        textoControles.setString("[A] Atacar   [C] Curar   [R] Rendirse");
    }

    alinearTextoControles();
}

void PantallaJugar::posicionarPanelCombate(const sf::Vector2u& windowSize)
{
    const float panelAncho = static_cast<float>(windowSize.x) - 160.f;
    const float panelAlto = 190.f;
    const auto enemigoBounds = enemigoSprite.getGlobalBounds();
    float panelY = enemigoBounds.top + enemigoBounds.height + 38.f;
    const float limiteInferior = static_cast<float>(windowSize.y) - panelAlto - 20.f;

    if (panelY > limiteInferior)
    {
        panelY = limiteInferior;
    }

    panelCombate.setPosition(80.f, panelY);
    panelCombate.setSize(sf::Vector2f(panelAncho, panelAlto));

    textoEstadoHeroe.setPosition(96.f, panelY + 12.f);
    textoEstadoEnemigo.setPosition(96.f, panelY + 38.f);
    textoLogCombate.setPosition(96.f, panelY + 70.f);

    alinearTextoControles();
}

void PantallaJugar::alinearTextoControles()
{
    const auto panelPos = panelCombate.getPosition();
    const auto panelSize = panelCombate.getSize();
    const auto bounds = textoControles.getLocalBounds();

    textoControles.setOrigin(bounds.left + bounds.width, bounds.top);
    textoControles.setPosition(panelPos.x + panelSize.x - 20.f, panelPos.y + panelSize.y - 30.f);
}

void PantallaJugar::aplicarAtaqueJugador()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    turnoCombate++;
    registrarMensaje("--- Turno " + std::to_string(turnoCombate) + " ---");

    int danio = heroe->atacar();
    danio += numeroAleatorio(-5, 5);
    if (danio < 0)
    {
        danio = 0;
    }

    const bool critico = numeroAleatorio(0, 99) < 20;
    if (critico)
    {
        danio *= 2;
        registrarMensaje("¡GOLPE CRÍTICO!");
    }

    enemigo->recibirDanio(danio);
    registrarMensaje(std::string(heroe->getNombre()) + " ataca por " + std::to_string(danio) + " de danio.");

    if (enemigo->estaEliminado())
    {
        victoria = true;
        combateFinalizado = true;
        heroe->agregarOro(enemigo->getoroOtorgado());
        registrarMensaje(std::string("¡") + heroe->getNombre() + " ha vencido a " + enemigo->getnombre() + "!");
        registrarMensaje("Oro obtenido: " + std::to_string(enemigo->getoroOtorgado()) +
                         " (total: " + std::to_string(heroe->getOro()) + ")");
        actualizarTextosCombate();
        return;
    }

    turnoEnemigo();
    actualizarTextosCombate();
}

void PantallaJugar::aplicarCuracionJugador()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    if (pocionesRestantes <= 0)
    {
        registrarMensaje("¡No te quedan curaciones! Atacas por inercia.");
        aplicarAtaqueJugador();
        return;
    }

    turnoCombate++;
    registrarMensaje("--- Turno " + std::to_string(turnoCombate) + " ---");

    const int curacion = 25 + numeroAleatorio(0, 10);
    heroe->curar(curacion);
    pocionesRestantes--;
    registrarMensaje(std::string(heroe->getNombre()) + " se cura " + std::to_string(curacion) + " puntos de vida.");

    turnoEnemigo();
    actualizarTextosCombate();
}

void PantallaJugar::turnoEnemigo()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    int danioEnemigo = enemigo->atacar();
    danioEnemigo += numeroAleatorio(-5, 5);
    if (danioEnemigo < 0)
    {
        danioEnemigo = 0;
    }

    heroe->recibirDanio(danioEnemigo);
    registrarMensaje(std::string(enemigo->getnombre()) + " ataca por " + std::to_string(danioEnemigo) + " de danio.");

    if (heroe->estaEliminado())
    {
        combateFinalizado = true;
        victoria = false;
        registrarMensaje(std::string(heroe->getNombre()) + " ha sido derrotado...");
    }
}

void PantallaJugar::updateLayout(const sf::RenderWindow& window)
{
    ultimaVentanaSize = window.getSize();

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        const auto windowSize = window.getSize();
        const auto textureSize = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(windowSize.x) / static_cast<float>(textureSize.x),
            static_cast<float>(windowSize.y) / static_cast<float>(textureSize.y));
    }

    if (enemigoTexture.getSize().x > 0 && enemigoTexture.getSize().y > 0)
    {
        posicionarSpritesCombate(ultimaVentanaSize);
        posicionarPanelCombate(ultimaVentanaSize);
    }

    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 92.f);
    //textoInstrucciones.setPosition(60.f, 130.f);

    actualizarTextosCombate();
}

PantallaResultado PantallaJugar::handleEvent(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            return PantallaResultado::VolverJugador;
        }

        if (!combateFinalizado)
        {
            if (event.key.code == sf::Keyboard::A)
            {
                aplicarAtaqueJugador();
            }
            else if (event.key.code == sf::Keyboard::C)
            {
                aplicarCuracionJugador();
            }
            else if (event.key.code == sf::Keyboard::R)
            {
                registrarMensaje(std::string("Te has rendido. ") + enemigo->getnombre() + " gana.");
                actualizarTextosCombate();
                return PantallaResultado::VolverJugador;
            }
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

    if (jugadorTexture.getSize().x > 0)
    {
        window.draw(jugadorSprite);
    }

    if (enemigoTexture.getSize().x > 0)
    {
        window.draw(enemigoSprite);
    }

    window.draw(panelCombate);
    window.draw(textoEstadoHeroe);
    window.draw(textoEstadoEnemigo);
    window.draw(textoLogCombate);
    window.draw(textoControles);

    window.draw(titulo);
    window.draw(textoJugador);
    //window.draw(textoInstrucciones);
    //botoneraTexto.draw(window);
}
