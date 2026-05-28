#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "botonera.h"
#include "Enemigos.h"
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

private:
    void actualizarTextoJugador();
    void cargarJugadorSeleccionado();
    void cargarEnemigoAleatorio();
    void posicionarSpritesCombate(const sf::Vector2u& windowSize);
    void reiniciarBatalla();
    void registrarMensaje(const std::string& mensaje);
    void actualizarTextosCombate();
    void posicionarPanelCombate(const sf::Vector2u& windowSize);
    void alinearTextoControles();
    void aplicarAtaqueJugador();
    void aplicarCuracionJugador();
    void turnoEnemigo();

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
    sf::RectangleShape panelCombate;

    //Botonera botoneraTexto;
    Botonera botoneraAcciones;
    int jugadorSeleccionado = 1;
    Personaje* heroe = nullptr;
    Enemigos* enemigo = nullptr;
    std::vector<std::string> mensajesCombate;
    int pocionesRestantes = 3;
    int turnoCombate = 0;
    bool combateFinalizado = false;
    bool victoria = false;
    int indiceEnemigo = 0;
};
