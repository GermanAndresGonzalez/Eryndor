/*
#pragma once
#include <SFML/Graphics.hpp>
#include <string>

#include "botonera.h"
#include "Enemigos.h"
#include "inventario.h"
#include "item.h"

#include "partidas.h"
#include "personaje.h"
#include "pantalla_resultado.h"

class PantallaJugar {
public:
    PantallaJugar();
    ~PantallaJugar();

    PantallaJugar(const PantallaJugar&) = delete;
    PantallaJugar& operator=(const PantallaJugar&) = delete;

    PantallaResultado handleEvent(const sf::Event& event, sf::RenderWindow& window);
    void updateLayout(const sf::RenderWindow& window);
    void draw(sf::RenderWindow& window) const;
    void setJugadorSeleccionado(int jugadorSeleccionado);
    int getJugadorSeleccionado() const { return jugadorSeleccionado; }
    bool cargarPartidaPorId(int idPartida);
    bool cargarUltimaPartida();

private:
    void actualizarTextoJugador();
    void cargarJugadorSeleccionado();
    void cargarEnemigoAleatorio();
    void posicionarSpritesCombate(const sf::Vector2u& windowSize);
    void posicionarPanelInventario(const sf::Vector2u& windowSize);
    void reiniciarBatalla();
    void registrarMensaje(const std::string& mensaje);
    void actualizarTextosCombate();
    void posicionarPanelCombate(const sf::Vector2u& windowSize);
    void alinearTextoControles();
    void aplicarAtaqueJugador();
    void aplicarCuracionJugador();
    void turnoEnemigo();
    void actualizarTextoInventario();
    void inicializarPartidaYInventario();
    void guardarProgreso();

    sf::Texture backgroundTexture;
    sf::Sprite  backgroundSprite;
    sf::Texture jugadorTexture;
    sf::Sprite  jugadorSprite;
    sf::Texture enemigoTexture;
    sf::Sprite  enemigoSprite;
    sf::Vector2u ultimaVentanaSize {1280u, 720u};
    sf::Font    font;
    sf::Text    titulo;
    sf::Text    textoJugador;
    sf::Text    textoInstrucciones;
    sf::Text    textoEstadoHeroe;
    sf::Text    textoEstadoEnemigo;
    sf::Text    textoLogCombate;
    sf::Text    textoControles;
    sf::Text    textoInventario;
    sf::RectangleShape panelCombate;
    sf::RectangleShape panelInventario;

    //Botonera botoneraTexto;
    Botonera botoneraAcciones;
    int jugadorSeleccionado = 1;
    Personaje* heroe = nullptr;
    Enemigos* enemigo = nullptr;
    Inventario inventario;
    Partidas partidaActual;
    Item curaBasica;
    Item espadaInicial;
    Item armaduraInicial;
    Item dagaBasica;
    Item armaduraComun;
    Item armaduraEspecial;
    static constexpr std::size_t maxMensajesCombate = 8;
    std::string mensajesCombate[maxMensajesCombate];
    std::size_t cantidadMensajesCombate = 0;
    int turnoCombate = 0;
    bool combateFinalizado = false;
    bool victoria = false;
    int indiceEnemigo = 0;
    bool progresoInicializado = false;
};
*/
