#pragma once

#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>

#include <cstddef>
#include <string>

/**
 * @brief Clase base genérica para menús con SFML.
 *
 * Gestiona una lista de ítems de texto, navegación por teclado/mouse
 * y un sonido de clic opcional.
 *
 * Las clases hijas deben:
 *  - Llamar a initOpciones() desde su constructor para cargar las opciones.
 *  - Sobreescribir dibujar() si necesitan elementos visuales extra.
 *  - Sobreescribir onSeleccion() para reaccionar a la opción elegida.
 */
class Menu {
public:
  /**
   * @param tamCaracter    Tamaño de fuente de los ítems.
   * @param espaciado      Píxeles entre cada ítem.
   * @param colorNormal    Color de texto en estado normal.
   * @param colorResaltado Color de texto cuando el ítem está seleccionado.
   */
  Menu(unsigned int tamCaracter    = 55,
       float        espaciado      = 75.f,
       sf::Color    colorNormal    = sf::Color::White,
       sf::Color    colorResaltado = sf::Color::Blue);

  virtual ~Menu() = default;

  // -------------------------------------------------------------------------
  // Interfaz pública
  // -------------------------------------------------------------------------

  /// Dibuja todos los ítems en la ventana. Sobreescribir para añadir extras.
  virtual void dibujar(sf::RenderWindow& window);

  /// Mueve la selección hacia arriba (con wrap-around).
  virtual void moverArriba();

  /// Mueve la selección hacia abajo (con wrap-around).
  virtual void moverAbajo();

  /**
   * @brief Detecta si el mouse está sobre algún ítem y lo resalta.
   * @return Índice del ítem bajo el cursor, o -1 si ninguno.
   */
  virtual int obtenerHover(int mouseX, int mouseY);

  /**
   * @brief Detecta un clic sobre un ítem, lo resalta y llama a onSeleccion().
   * @return Índice del ítem clickeado, o -1 si ninguno.
   */
  virtual int obtenerClickeado(int mouseX, int mouseY);

  /// Devuelve el índice actualmente seleccionado (-1 = ninguno).
  int getSeleccionado() const { return seleccionado; }

  /// Indica si hay un ítem seleccionado.
  bool haySeleccion() const { return seleccionado >= 0; }

  // -------------------------------------------------------------------------
  // Hook virtual — las hijas reaccionan a la selección confirmada
  // -------------------------------------------------------------------------

  /**
   * @brief Llamado automáticamente cuando el usuario hace clic en un ítem.
   *        Las clases hijas lo sobreescriben para ejecutar la acción.
   * @param indice Ítem seleccionado.
   */
  virtual void onSeleccion(int indice) {}

protected:
  // -------------------------------------------------------------------------
  // Helpers para las clases hijas
  // -------------------------------------------------------------------------

  /**
   * @brief Inicializa los ítems del menú. Llamar desde el constructor hijo.
   * @param font     Fuente ya cargada.
   * @param opciones Textos de las opciones.
   * @param origenX  Posición X del primer ítem.
   * @param origenY  Posición Y del primer ítem.
   */
  void initOpciones(const sf::Font&                  font,
                    const std::string                 opciones[],
                    std::size_t                       cantidadOpciones,
                    float origenX,
                    float origenY);

  /// Resalta el ítem i y desresalta el anterior.
  void resaltarItem(int i);

  /// Reproduce el sonido de clic si fue cargado correctamente.
  void reproducirSonido();

  // -------------------------------------------------------------------------
  // Miembros protegidos
  // -------------------------------------------------------------------------
  static constexpr std::size_t maxItems = 16;
  sf::Text items[maxItems];
  std::size_t cantidadItems = 0;

  sf::SoundBuffer soundBuffer;
  sf::Sound       sound;
  bool            soundLoaded = false;

  int             seleccionado  = -1;
  unsigned int    tamCaracter;
  float           espaciado;
  sf::Color       colorNormal;
  sf::Color       colorResaltado;
};
