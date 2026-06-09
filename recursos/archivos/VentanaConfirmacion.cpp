#include "VentanaConfirmacion.h"

#include <iostream>

// ---------------------------------------------------------------------------
// Bloqueo de ventana por plataforma
// ---------------------------------------------------------------------------
#if defined(_WIN32)
    #ifndef WIN32_LEAN_AND_MEAN
        #define WIN32_LEAN_AND_MEAN
    #endif
    #ifndef NOMINMAX
        #define NOMINMAX
    #endif
    #include <windows.h>

    // En Windows, EnableWindow(false) deshabilita TODA interacción con la
    // ventana: botones de la barra de título, clics, teclado, etc.
    // La ventana queda visualmente "grisada" por el sistema operativo.
    void VentanaConfirmacion::deshabilitarVentana(sf::RenderWindow& ventana)
    {
        HWND hwnd = ventana.getSystemHandle();
        if (hwnd) EnableWindow(hwnd, FALSE);
    }

    void VentanaConfirmacion::habilitarVentana(sf::RenderWindow& ventana)
    {
        HWND hwnd = ventana.getSystemHandle();
        if (hwnd) EnableWindow(hwnd, TRUE);
    }

#else
    // En Linux / macOS SFML no expone una API equivalente a EnableWindow.
    // La estrategia es:
    //   1. Detener el renderizado de la ventana padre (no necesario, pero
    //      posible si se quisiera oscurecer).
    //   2. Al cerrar el diálogo, vaciar la cola de eventos acumulados para
    //      que ningún clic "fantasma" llegue al juego (ver limpiarEventosPendientes).
    // Los botones de la barra de título del SO siguen siendo visibles, pero
    // los eventos que generen serán descartados al regresar.
    void VentanaConfirmacion::deshabilitarVentana(sf::RenderWindow& /*ventana*/)
    {
        // No-op en Linux/macOS: el bloqueo se logra descartando eventos al volver.
    }

    void VentanaConfirmacion::habilitarVentana(sf::RenderWindow& /*ventana*/)
    {
        // No-op en Linux/macOS.
    }
#endif

// ---------------------------------------------------------------------------
// Limpia la cola de eventos de la ventana padre
// ---------------------------------------------------------------------------
void VentanaConfirmacion::limpiarEventosPendientes(sf::RenderWindow& ventana)
{
    sf::Event ev;
    while (ventana.pollEvent(ev)) { /* descartar */ }
}

// ---------------------------------------------------------------------------
// Paleta de colores
// ---------------------------------------------------------------------------
namespace
{
    const sf::Color COLOR_FONDO        (210, 210, 210);
    const sf::Color COLOR_BOTON_NORMAL ( 90, 140, 210);
    const sf::Color COLOR_BOTON_HOVER  ( 60, 110, 185);
    const sf::Color COLOR_BOTON_TEXTO  (255, 255, 255);
    const sf::Color COLOR_BORDE        (150, 150, 150);
    const sf::Color COLOR_TEXTO_MENSAJE( 40,  40,  40);
}

// ---------------------------------------------------------------------------
// Constructor
// ---------------------------------------------------------------------------
VentanaConfirmacion::VentanaConfirmacion()
{
    const char* rutasFuente[] = {
        "recursos/fuentes/AlexandriaFLF-Bold.ttf",
        "/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf",
        "/usr/share/fonts/truetype/liberation/LiberationSans-Regular.ttf",
        "C:/Windows/Fonts/arial.ttf"
    };

    bool fuenteCargada = false;
    for (const char* ruta : rutasFuente)
    {
        if (font.loadFromFile(ruta)) { fuenteCargada = true; break; }
    }
    if (!fuenteCargada)
        std::cerr << "VentanaConfirmacion: no se pudo cargar ninguna fuente.\n";

    fondo.setFillColor(COLOR_FONDO);
    fondo.setOutlineColor(COLOR_BORDE);
    fondo.setOutlineThickness(1.f);

    textoMensaje.setFont(font);
    textoMensaje.setCharacterSize(CHAR_SIZE_MENSAJE);
    textoMensaje.setFillColor(COLOR_TEXTO_MENSAJE);

    botonSi.setFillColor(COLOR_BOTON_NORMAL);
    botonSi.setSize(sf::Vector2f(ANCHO_BOTON, ALTO_BOTON));
    textoSi.setFont(font);
    textoSi.setCharacterSize(CHAR_SIZE_BOTON);
    textoSi.setFillColor(COLOR_BOTON_TEXTO);
    textoSi.setString("Si");

    botonNo.setFillColor(COLOR_BOTON_NORMAL);
    botonNo.setSize(sf::Vector2f(ANCHO_BOTON, ALTO_BOTON));
    textoNo.setFont(font);
    textoNo.setCharacterSize(CHAR_SIZE_BOTON);
    textoNo.setFillColor(COLOR_BOTON_TEXTO);
    textoNo.setString("No");
}

// ---------------------------------------------------------------------------
// mostrar
// ---------------------------------------------------------------------------
bool VentanaConfirmacion::mostrar(sf::RenderWindow& ventanaPadre,
                                   const std::string& titulo,
                                   const std::string& mensaje)
{
    // 1. Deshabilitar la ventana padre ANTES de crear el diálogo.
    deshabilitarVentana(ventanaPadre);

    sf::RenderWindow ventana(
        sf::VideoMode(ANCHO_VENTANA, ALTO_VENTANA),
        titulo,
        sf::Style::Titlebar | sf::Style::Close);
    ventana.setFramerateLimit(60);

    // 2. Mantener el diálogo siempre encima de la ventana padre.
#if defined(_WIN32)
    {
        HWND hwndDialogo = ventana.getSystemHandle();
        HWND hwndPadre   = ventanaPadre.getSystemHandle();
        if (hwndDialogo && hwndPadre)
        {
            // Establece la ventana padre a nivel de SO para que el diálogo
            // quede vinculado y siempre al frente.
            SetWindowLongPtr(hwndDialogo, GWLP_HWNDPARENT,
                             reinterpret_cast<LONG_PTR>(hwndPadre));
            SetWindowPos(hwndDialogo, HWND_TOP, 0, 0, 0, 0,
                         SWP_NOMOVE | SWP_NOSIZE);
        }
    }
#endif

    textoMensaje.setString(mensaje);
    actualizarLayout(ventana.getSize());

    bool resultado = false;

    while (ventana.isOpen())
    {
        sf::Event event;
        while (ventana.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                ventana.close();
                resultado = false;
                break;
            }

            if (event.type == sf::Event::MouseMoved)
            {
                const sf::Vector2f mouse(
                    static_cast<float>(event.mouseMove.x),
                    static_cast<float>(event.mouseMove.y));
                botonSi.setFillColor(contienePunto(botonSi, mouse) ? COLOR_BOTON_HOVER : COLOR_BOTON_NORMAL);
                botonNo.setFillColor(contienePunto(botonNo, mouse) ? COLOR_BOTON_HOVER : COLOR_BOTON_NORMAL);
            }

            if (event.type == sf::Event::MouseButtonReleased &&
                event.mouseButton.button == sf::Mouse::Left)
            {
                const sf::Vector2f mouse(
                    static_cast<float>(event.mouseButton.x),
                    static_cast<float>(event.mouseButton.y));
                if (contienePunto(botonSi, mouse))      { resultado = true;  ventana.close(); }
                else if (contienePunto(botonNo, mouse)) { resultado = false; ventana.close(); }
            }

            if (event.type == sf::Event::KeyPressed)
            {
                if      (event.key.code == sf::Keyboard::Return) { resultado = true;  ventana.close(); }
                else if (event.key.code == sf::Keyboard::Escape) { resultado = false; ventana.close(); }
            }
        }

        // Seguir renderizando la ventana padre mientras el diálogo está abierto
        // para que no quede congelada visualmente.
        ventanaPadre.display();

        ventana.clear(COLOR_FONDO);
        ventana.draw(fondo);
        ventana.draw(textoMensaje);
        ventana.draw(botonSi);   ventana.draw(textoSi);
        ventana.draw(botonNo);   ventana.draw(textoNo);
        ventana.display();
    }

    // 3. Habilitar la ventana padre y descartar eventos acumulados.
    habilitarVentana(ventanaPadre);
    limpiarEventosPendientes(ventanaPadre);

    // 4. Devolver el foco a la ventana padre.
    ventanaPadre.requestFocus();

    return resultado;
}

// ---------------------------------------------------------------------------
// actualizarLayout
// ---------------------------------------------------------------------------
void VentanaConfirmacion::actualizarLayout(const sf::Vector2u& windowSize)
{
    const float w = static_cast<float>(windowSize.x);
    const float h = static_cast<float>(windowSize.y);

    fondo.setPosition(0.f, 0.f);
    fondo.setSize(sf::Vector2f(w, h));

    {
        const auto bounds = textoMensaje.getLocalBounds();
        textoMensaje.setOrigin(bounds.left + bounds.width / 2.f,
                               bounds.top  + bounds.height / 2.f);
        textoMensaje.setPosition(w / 2.f, h * 0.35f);
    }

    const float totalBotones = ANCHO_BOTON * 2.f + SEPARACION_BOTONES;
    const float inicioX      = w / 2.f - totalBotones / 2.f;
    const float botonesY     = h * 0.62f;

    botonSi.setPosition(inicioX, botonesY);
    botonNo.setPosition(inicioX + ANCHO_BOTON + SEPARACION_BOTONES, botonesY);

    auto centrarTexto = [](sf::Text& texto, const sf::RectangleShape& boton)
    {
        const auto tb = texto.getLocalBounds();
        const auto bp = boton.getPosition();
        const auto bs = boton.getSize();
        texto.setOrigin(tb.left + tb.width / 2.f, tb.top + tb.height / 2.f);
        texto.setPosition(bp.x + bs.x / 2.f, bp.y + bs.y / 2.f);
    };

    centrarTexto(textoSi, botonSi);
    centrarTexto(textoNo, botonNo);
}

// ---------------------------------------------------------------------------
// contienePunto
// ---------------------------------------------------------------------------
bool VentanaConfirmacion::contienePunto(const sf::RectangleShape& rect,
                                         sf::Vector2f punto)
{
    return rect.getGlobalBounds().contains(punto);
}
