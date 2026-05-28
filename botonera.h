#pragma once

#include <SFML/Graphics.hpp>
#include <cstddef>
#include <string>

class Botonera
{
private:
    sf::RectangleShape fondo;       // Rectángulo transparente
    sf::Text botones[9];            // Array fijo de hasta 9 botones
    int cantidadBotones;            // Cuántos botones se usan
    sf::Font fuente;                // Fuente para los textos
    sf::Sprite spCabezaJugador;      // Sprite para la cabeza del jugador

public:
    // Constructor 1: solo rectángulo
    //Botonera(float x, float y, float ancho, float alto, sf::Color color);
    Botonera(const float coordenadas[], sf::Color color);
    Botonera(const float coordenadas[], sf::Color color, int personaje);

    // Constructor 2: rectángulo + arreglo de strings
    Botonera(const float coordenadas[], sf::Color color,
             const std::string etiquetas[], int n);

    // Destructor
    ~Botonera();

    // Dibujar en la ventana
    void draw(sf::RenderWindow& window) const;

    // Devuelve el índice del botón clickeado, o -1 si no hubo clic.
    int obtenerClickeado(int mouseX, int mouseY) const;
};


