#include "pantalla_explorar.h"

//#include "exploracion.h"

#include <algorithm>
#include <iostream>
#include <sstream>

// ---------------------------------------------------------------------------
// Constantes de presentación
// ---------------------------------------------------------------------------
namespace
{
const float coordenadasAcciones[] = {650.f, 560.f, 450.f, 100.f};

const std::string acciones[] =
{
    "[A] Atacar",
    "[C] Curar",
    "[R] Rendirse"
};

// Convierte el array de mensajes del Combate en un único string con saltos
// de línea (muestra solo los últimos 5).
std::string unirMensajes(const std::string* mensajes, std::size_t cantidad)
{
    std::ostringstream salida;
    const std::size_t limite = 5;
    const std::size_t inicio = cantidad > limite ? cantidad - limite : 0;

    for (std::size_t i = inicio; i < cantidad; ++i)
    {
        salida << mensajes[i];
        if (i + 1 < cantidad)
        {
            salida << '\n';
        }
    }
    return salida.str();
}
} // namespace

// ---------------------------------------------------------------------------
// Constructor / destructor
// ---------------------------------------------------------------------------
PantallaExplorar::PantallaExplorar()
    : botoneraAcciones(coordenadasAcciones, sf::Color(0, 0, 0, 150), acciones, 3)
{
    // -- Fuente --------------------------------------------------------------
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        std::cerr << "PantallaExplorar: no se pudo cargar la fuente\n";
    }

    // -- Fondo ---------------------------------------------------------------
    if (!backgroundTexture.loadFromFile("recursos/imag/Cueva/cueva_1280x720.png"))
    {
        std::cerr << "PantallaExplorar: no se pudo cargar el fondo\n";
    }
    else
    {
        backgroundSprite.setTexture(backgroundTexture);
    }

    // -- Textos --------------------------------------------------------------
    auto configurarTexto = [&](sf::Text& t, unsigned int size)
    {
        t.setFont(font);
        t.setCharacterSize(size);
        t.setFillColor(sf::Color::White);
        t.setOutlineColor(sf::Color::Black);
        t.setOutlineThickness(1.f);
    };

    titulo.setFont(font);
    titulo.setCharacterSize(42);
    titulo.setFillColor(sf::Color::White);
    titulo.setOutlineColor(sf::Color::Black);
    titulo.setOutlineThickness(2.f);
    titulo.setString("Batalla por turnos numero: 0");

    configurarTexto(textoJugador,       24);
    configurarTexto(textoEstadoHeroe,   20);
    configurarTexto(textoEstadoEnemigo, 20);
    configurarTexto(textoLogCombate,    19);
    configurarTexto(textoControles,     18);
    configurarTexto(textoInventario,    18);
    textoJugador.setString("Personaje elegido: Kael Draven");

    // -- Paneles -------------------------------------------------------------
    panelCombate.setFillColor(sf::Color(0, 0, 0, 170));
    panelCombate.setOutlineThickness(2.f);
    panelCombate.setOutlineColor(sf::Color::White);

    panelInventario.setFillColor(sf::Color(0, 0, 0, 170));
    panelInventario.setOutlineThickness(2.f);
    panelInventario.setOutlineColor(sf::Color::White);

    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 92.f);

    posicionarPanelInventario(ultimaVentanaSize);
}

PantallaExplorar::~PantallaExplorar()
{
    // Combate guarda el progreso en su propio destructor.
}

// ---------------------------------------------------------------------------
// Configuración pública
// ---------------------------------------------------------------------------
void PantallaExplorar::setJugadorSeleccionado(int id)
{
    combate.setJugadorSeleccionado(id);
    recargarSpriteJugador();
    combate.reiniciarBatalla();
    recargarSpriteEnemigo();
    posicionarSpritesCombate(ultimaVentanaSize);
    posicionarPanelCombate(ultimaVentanaSize);
    actualizarTextoJugador();
    actualizarTextosCombate();
    actualizarTextoInventario();
    titulo.setString("Batalla por turnos numero: " +
                     std::to_string(combate.getIdPartida()));
    posicionarPanelInventario(ultimaVentanaSize);
}

bool PantallaExplorar::cargarPartidaPorId(int idPartida)
{
    if (!combate.cargarPartidaPorId(idPartida))
    {
        return false;
    }

    recargarSpriteJugador();
    recargarSpriteEnemigo();
    posicionarSpritesCombate(ultimaVentanaSize);
    posicionarPanelCombate(ultimaVentanaSize);
    actualizarTextoJugador();
    actualizarTextosCombate();
    actualizarTextoInventario();
    titulo.setString("Batalla por turnos numero: " +
                     std::to_string(combate.getIdPartida()));
    return true;
}

bool PantallaExplorar::cargarUltimaPartida()
{
    if (!combate.cargarUltimaPartida())
    {
        return false;
    }
    recargarSpriteJugador();
    recargarSpriteEnemigo();
    posicionarSpritesCombate(ultimaVentanaSize);
    posicionarPanelCombate(ultimaVentanaSize);
    actualizarTextoJugador();
    actualizarTextosCombate();
    actualizarTextoInventario();
    titulo.setString("Batalla por turnos numero: " +
                     std::to_string(combate.getIdPartida()));
    return true;
}

// ---------------------------------------------------------------------------
// Ciclo principal
// ---------------------------------------------------------------------------
PantallaResultado PantallaExplorar::handleEvent(const sf::Event& event,
                                              sf::RenderWindow& window)
{
    if (event.type == sf::Event::KeyPressed)
    {
        if (event.key.code == sf::Keyboard::Escape)
        {
            combate.guardarProgreso();
            return PantallaResultado::VolverJugador;
        }

        if (!combate.esCombateFinalizado())
        {
            if (event.key.code == sf::Keyboard::A)
            {
                accionAtacar();
            }
            else if (event.key.code == sf::Keyboard::C)
            {
                accionCurar();
            }
            else if (event.key.code == sf::Keyboard::R)
            {
                combate.guardarProgreso();
                return PantallaResultado::VolverJugador;
            }
        }
    }
    return PantallaResultado::Nada;
}

void PantallaExplorar::updateLayout(const sf::RenderWindow& window)
{
    ultimaVentanaSize = window.getSize();

    if (backgroundTexture.getSize().x > 0 && backgroundTexture.getSize().y > 0)
    {
        const auto ws = window.getSize();
        const auto ts = backgroundTexture.getSize();
        backgroundSprite.setScale(
            static_cast<float>(ws.x) / static_cast<float>(ts.x),
            static_cast<float>(ws.y) / static_cast<float>(ts.y));
    }

    if (enemigoTexture.getSize().x > 0 && enemigoTexture.getSize().y > 0)
    {
        posicionarSpritesCombate(ultimaVentanaSize);
        posicionarPanelCombate(ultimaVentanaSize);
    }

    posicionarPanelInventario(ultimaVentanaSize);

    titulo.setPosition(60.f, 40.f);
    textoJugador.setPosition(60.f, 92.f);

    actualizarTextosCombate();
}

void PantallaExplorar::draw(sf::RenderWindow& window) const
{
    if (backgroundTexture.getSize().x > 0)
    {
        window.draw(backgroundSprite);
    }

    window.draw(panelInventario);
    window.draw(textoInventario);

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
}

// ---------------------------------------------------------------------------
// Acciones de combate (wrappers: lógica → Combate, UI → aquí)
// ---------------------------------------------------------------------------
void PantallaExplorar::accionAtacar()
{
    combate.aplicarAtaqueJugador();
    actualizarTextosCombate();
}

void PantallaExplorar::accionCurar()
{
    combate.aplicarCuracionJugador();
    actualizarTextosCombate();
    actualizarTextoInventario();
}

// ---------------------------------------------------------------------------
// Carga de sprites
// ---------------------------------------------------------------------------
void PantallaExplorar::recargarSpriteJugador()
{
    const char* ruta = (combate.getJugadorSeleccionado() == 2)
        ? "recursos/imag/Jugadores/Cabeza_jugador2.png"
        : "recursos/imag/Jugadores/Cabeza_jugador1.png";

    if (!jugadorTexture.loadFromFile(ruta))
    {
        std::cerr << "PantallaExplorar: no se pudo cargar " << ruta << '\n';
        return;
    }
    jugadorSprite.setTexture(jugadorTexture, true);
}

void PantallaExplorar::recargarSpriteEnemigo()
{
    const char* ruta = combate.getRutaImagenEnemigo();
    if (!enemigoTexture.loadFromFile(ruta))
    {
        std::cerr << "PantallaExplorar: no se pudo cargar " << ruta << '\n';
        return;
    }
    enemigoSprite.setTexture(enemigoTexture, true);
    posicionarPanelCombate(ultimaVentanaSize);
}

// ---------------------------------------------------------------------------
// Posicionamiento de sprites
// ---------------------------------------------------------------------------
void PantallaExplorar::posicionarSpritesCombate(const sf::Vector2u& windowSize)
{
    if (jugadorTexture.getSize().x == 0 || enemigoTexture.getSize().x == 0)
    {
        return;
    }

    const float maxAncho  = 140.f;
    const float maxAlto   = 140.f;
    const float separacion = 100.f;
    const float centroY   = static_cast<float>(windowSize.y) / 2.f - 70.f;

    auto escalarSprite = [&](sf::Sprite& spr, const sf::Texture& tex)
    {
        const float sx = maxAncho / static_cast<float>(tex.getSize().x);
        const float sy = maxAlto  / static_cast<float>(tex.getSize().y);
        spr.setScale(std::min(sx, sy), std::min(sx, sy));
    };

    escalarSprite(jugadorSprite, jugadorTexture);
    escalarSprite(enemigoSprite, enemigoTexture);

    auto centrarOrigen = [](sf::Sprite& spr)
    {
        const auto b = spr.getLocalBounds();
        spr.setOrigin(b.left + b.width / 2.f, b.top + b.height / 2.f);
    };

    centrarOrigen(jugadorSprite);
    centrarOrigen(enemigoSprite);

    const auto bj = jugadorSprite.getGlobalBounds();
    const auto be = enemigoSprite.getGlobalBounds();

    const float totalAncho = bj.width + separacion + be.width;
    const float inicioX    = static_cast<float>(windowSize.x) / 2.f - totalAncho / 2.f;

    jugadorSprite.setPosition(inicioX + bj.width / 2.f, centroY);
    enemigoSprite.setPosition(inicioX + bj.width + separacion + be.width / 2.f, centroY);
}

// ---------------------------------------------------------------------------
// Posicionamiento de paneles
// ---------------------------------------------------------------------------
void PantallaExplorar::posicionarPanelCombate(const sf::Vector2u& windowSize)
{
    const float panelAncho    = static_cast<float>(windowSize.x) - 160.f;
    const float panelAlto     = 190.f;
    const auto  enemigoBounds = enemigoSprite.getGlobalBounds();
    float panelY              = enemigoBounds.top + enemigoBounds.height + 38.f;
    const float limiteInferior = static_cast<float>(windowSize.y) - panelAlto + 20.f;

    if (panelY > limiteInferior)
    {
        panelY = limiteInferior;
    }

    panelCombate.setPosition(80.f, panelY);
    panelCombate.setSize(sf::Vector2f(panelAncho, panelAlto));

    textoEstadoHeroe.setPosition  (96.f, panelY + 12.f);
    textoEstadoEnemigo.setPosition(96.f, panelY + 38.f);
    textoLogCombate.setPosition   (96.f, panelY + 70.f);

    alinearTextoControles();
}

void PantallaExplorar::posicionarPanelInventario(const sf::Vector2u& windowSize)
{
    const float panelAncho = 320.f;
    const float panelAlto  = 160.f;
    const float panelX     = 80.f;
    const float panelY     = static_cast<float>(windowSize.y) / 2.f - panelAlto / 2.f - 60.f;

    panelInventario.setPosition(panelX, panelY);
    panelInventario.setSize(sf::Vector2f(panelAncho, panelAlto));
    textoInventario.setPosition(panelX + 20.f, panelY + 18.f);
}

void PantallaExplorar::alinearTextoControles()
{
    const auto panelPos  = panelCombate.getPosition();
    const auto panelSize = panelCombate.getSize();
    const auto bounds    = textoControles.getLocalBounds();

    textoControles.setOrigin(bounds.left + bounds.width, bounds.top);
    textoControles.setPosition(panelPos.x + panelSize.x - 20.f,
                               panelPos.y + panelSize.y - 30.f);
}

// ---------------------------------------------------------------------------
// Actualización de textos de UI
// ---------------------------------------------------------------------------
void PantallaExplorar::actualizarTextoJugador()
{
    textoJugador.setString(
        std::string("Personaje elegido: ") + combate.getNombreJugador());
}

void PantallaExplorar::actualizarTextosCombate()
{
    const Personaje* heroe   = combate.getHeroe();
    const Enemigos*  enemigo = combate.getEnemigo();

    if (heroe)
    {
        textoEstadoHeroe.setString(
            std::string("Jugador: ") + heroe->getNombre() +
            "  HP: "  + std::to_string(heroe->getVidaActual()) + "/" +
                        std::to_string(heroe->getVidaMaxima()) +
            "  ATK: " + std::to_string(heroe->getAtaque()) +
            "  DEF: " + std::to_string(heroe->getDefensa()) +
            "  Oro: " + std::to_string(heroe->getOro()));
    }

    if (enemigo)
    {
        textoEstadoEnemigo.setString(
            std::string("Enemigo: ") + enemigo->getnombre() +
            "  HP: "  + std::to_string(enemigo->getVidaActual()) + "/" +
                        std::to_string(enemigo->getVidaMaxima()) +
            "  ATK: " + std::to_string(enemigo->getAtaque()) +
            "  DEF: " + std::to_string(enemigo->getDefensa()));
    }

    textoLogCombate.setString(
        unirMensajes(combate.getMensajes(), combate.getCantidadMensajes()));

    actualizarTextoInventario();

    textoControles.setString(
        combate.esCombateFinalizado()
            ? "Pulsa ESC para volver a la pantalla anterior."
            : "[A] Atacar   [C] Curar   [R] Rendirse");

    alinearTextoControles();
}

void PantallaExplorar::actualizarTextoInventario()
{
    // IDs e ítems visibles en el panel de inventario
    struct EntradaVisible { int id; const char* etiqueta; };
    static const EntradaVisible entradas[] =
    {
        {1, "Curas"},
        {4, "Daga"},
        {2, "Espada"},
        {5, "Armadura comun"},
        {6, "Armadura especial"}
    };

    std::ostringstream salida;
    salida << "Inventario:";
    for (const auto& e : entradas)
    {
        salida << '\n' << e.etiqueta << ": "
               << combate.getInventario().obtenerCantidad(e.id);
    }
    textoInventario.setString(salida.str());
}
