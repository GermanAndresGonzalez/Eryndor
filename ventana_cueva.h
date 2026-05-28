#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <string>

/**
 * @brief Clase base para ventanas del juego "Las Profundidades de Eryndor".
 *
 * Proporciona la estructura principal del loop de juego (patrón Template Method).
 * Las clases derivadas pueden sobreescribir loadResources(), updateLayout(),
 * handleEvents() y draw() para personalizar el comportamiento de cada escena.
 */
class VentanaCueva {
public:
  /**
   * @brief Constructor. Crea la ventana SFML y llama a loadResources() y updateLayout().
   * @param title Título de la ventana.
   * @param width Ancho inicial de la ventana.
   * @param height Alto inicial de la ventana.
   */
  VentanaCueva(const std::string& title = "Las Profundidades de Eryndor",
             unsigned int width = 1280,
             unsigned int height = 720,
             const std::string& backgroundTexturePath = "./recursos/imag/cueva_titulo.png",
             const std::string& soundBufferPath = "./recursos/sonido/dark-tunnel-ambience.flac");

  /// Destructor virtual obligatorio para clases base polimórficas.
  virtual ~VentanaCueva();

  /**
   * @brief Inicia el loop principal. No debe sobreescribirse en clases hijas
   *        salvo que se necesite un loop completamente distinto.
   *
   * Patrón Template Method: llama secuencialmente a handleEvents() y draw()
   * mientras la ventana esté abierta.
   */
  void run();

protected:
  // -------------------------------------------------------------------------
  // Métodos virtuales — las clases hijas los sobreescriben según necesiten
  // -------------------------------------------------------------------------

  /**
   * @brief Carga texturas, sonidos y cualquier otro recurso necesario.
   *        La implementación base carga el fondo de cueva y el audio de ambiente.
   */
  virtual void loadResources();

  /**
   * @brief Recalcula posiciones y escalas al cambiar el tamaño de la ventana.
   *        La implementación base reescala el fondo y reposiciona el botón de cierre.
   */
  virtual void updateLayout();

  /**
   * @brief Procesa los eventos de SFML (cierre, redimensión, clic del ratón).
   *        Las clases hijas pueden añadir eventos adicionales llamando primero
   *        a CaveWindow::handleEvents() si desean conservar el comportamiento base.
   */
  virtual void handleEvents();

  /**
   * @brief Dibuja todos los elementos en pantalla.
   *        Las clases hijas deben llamar a CaveWindow::draw() si quieren conservar
   *        el fondo y el botón de cierre, o reimplementarlo por completo.
   */
  virtual void draw();

  // -------------------------------------------------------------------------
  // Miembros protegidos — accesibles desde las clases hijas
  // -------------------------------------------------------------------------
  sf::RenderWindow   window;

  sf::Texture        backgroundTexture;
  sf::Sprite         backgroundSprite;

  sf::SoundBuffer    soundBuffer;
  sf::Sound          sound;

  sf::RectangleShape closeButton;
  sf::RectangleShape closeLineA;
  sf::RectangleShape closeLineB;

  std::string        backgroundTexturePath;
  std::string        soundBufferPath;
};
