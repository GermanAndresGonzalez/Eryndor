#pragma once

#include <SFML/Graphics.hpp>
#include <string>

#include "botonera.h"
#include "Combate.h"          // <-- nueva clase de lógica pura
#include "pantalla_resultado.h"

// ---------------------------------------------------------------------------
// PantallaExplorar
// Responsabilidad: presentación gráfica del combate.
// Toda la lógica de combate (turnos, daño, inventario, persistencia) vive
// en la clase Combate, que PantallaExplorar posee como miembro.
// ---------------------------------------------------------------------------
class PantallaExplorar
{
public:
    PantallaExplorar();
    ~PantallaExplorar();

    PantallaExplorar(const PantallaExplorar&)            = delete;
    PantallaExplorar& operator=(const PantallaExplorar&) = delete;

    // -----------------------------------------------------------------------
    // Interfaz pública (igual que antes)
    // -----------------------------------------------------------------------
    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;

    void setJugadorSeleccionado(int jugadorSeleccionado);
    int  getJugadorSeleccionado() const { return combate.getJugadorSeleccionado(); }

    bool cargarPartidaPorId(int idPartida);
    bool cargarUltimaPartida();

private:
    // -----------------------------------------------------------------------
    // Helpers de presentación (solo UI, sin lógica de juego)
    // -----------------------------------------------------------------------
    void actualizarTextoJugador();
    void recargarSpriteJugador();          // carga textura según jugador activo
    void recargarSpriteEnemigo();          // carga textura según enemigo activo
    void posicionarSpritesCombate(const sf::Vector2u& windowSize);
    void posicionarPanelInventario(const sf::Vector2u& windowSize);
    void posicionarPanelCombate(const sf::Vector2u& windowSize);
    void alinearTextoControles();
    void actualizarTextosCombate();        // sincroniza todos los sf::Text con Combate
    void actualizarTextoInventario();

    // -----------------------------------------------------------------------
    // Lógica de juego (delegada a Combate; estos wrappers actualizan la UI
    // después de que la lógica haya corrido)
    // -----------------------------------------------------------------------
    void accionAtacar();
    void accionCurar();

    // -----------------------------------------------------------------------
    // Recursos gráficos
    // -----------------------------------------------------------------------
    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Texture jugadorTexture;
    sf::Sprite  jugadorSprite;
    sf::Texture enemigoTexture;
    sf::Sprite  enemigoSprite;

    sf::Vector2u ultimaVentanaSize {1280u, 720u};
    sf::Font     font;

    sf::Text textoJugador;
    sf::Text titulo;
    sf::Text textoEstadoHeroe;
    sf::Text textoEstadoEnemigo;
    sf::Text textoLogCombate;
    sf::Text textoControles;
    sf::Text textoInventario;

    sf::RectangleShape panelCombate;
    sf::RectangleShape panelInventario;

    Botonera botoneraAcciones;

    // -----------------------------------------------------------------------
    // Lógica de combate (separada de la presentación)
    // -----------------------------------------------------------------------
    Combate combate;
};
