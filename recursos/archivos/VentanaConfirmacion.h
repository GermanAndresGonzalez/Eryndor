#pragma once

#include <SFML/Graphics.hpp>
#include <string>

// ---------------------------------------------------------------------------
// VentanaConfirmacion
// Abre una ventana modal bloqueante con un mensaje y dos botones.
// Mientras el diálogo está abierto, la ventana principal queda deshabilitada:
//   - En Windows: via EnableWindow() (WinAPI), que bloquea todos los controles
//     de la barra de título (minimizar, maximizar, cerrar) y los clics.
//   - En Linux/macOS: se vacía la cola de eventos acumulados al volver y la
//     ventana del diálogo se mantiene siempre al frente.
//
// Uso:
//   VentanaConfirmacion dialogo;
//   bool respuesta = dialogo.mostrar(ventanaPrincipal,
//                                    "Salir del juego",
//                                    "¿Deseas guardar antes de salir?");
// ---------------------------------------------------------------------------
class VentanaConfirmacion
{
public:
    VentanaConfirmacion();

    // Abre el diálogo modal.
    // ventanaPadre : ventana principal del juego (se deshabilita mientras
    //                el diálogo está abierto).
    // titulo       : texto en la barra de título de la ventana emergente.
    // mensaje      : texto visible dentro de la ventana, encima de los botones.
    // Devuelve true = "Sí", false = "No" o ventana cerrada.
    bool mostrar(sf::RenderWindow& ventanaPadre,
                 const std::string& titulo,
                 const std::string& mensaje);

private:
    void actualizarLayout(const sf::Vector2u& windowSize);
    static bool contienePunto(const sf::RectangleShape& rect, sf::Vector2f punto);

    // Deshabilita / habilita la ventana padre (implementación por plataforma).
    static void deshabilitarVentana(sf::RenderWindow& ventana);
    static void habilitarVentana   (sf::RenderWindow& ventana);

    // Vacía todos los eventos pendientes de la ventana padre para descartar
    // cualquier clic o tecla que el usuario haya hecho mientras el diálogo
    // estaba abierto (necesario en Linux/macOS donde no existe EnableWindow).
    static void limpiarEventosPendientes(sf::RenderWindow& ventana);

    // -----------------------------------------------------------------------
    // Recursos gráficos
    // -----------------------------------------------------------------------
    sf::Font font;

    sf::RectangleShape fondo;
    sf::Text           textoMensaje;

    sf::RectangleShape botonSi;
    sf::Text           textoSi;

    sf::RectangleShape botonNo;
    sf::Text           textoNo;

    // -----------------------------------------------------------------------
    // Constantes de diseño
    // -----------------------------------------------------------------------
    static constexpr unsigned int ANCHO_VENTANA      = 480u;
    static constexpr unsigned int ALTO_VENTANA       = 220u;
    static constexpr unsigned int CHAR_SIZE_MENSAJE  = 22u;
    static constexpr unsigned int CHAR_SIZE_BOTON    = 20u;
    static constexpr float        ANCHO_BOTON        = 120.f;
    static constexpr float        ALTO_BOTON         = 46.f;
    static constexpr float        SEPARACION_BOTONES = 30.f;
};
