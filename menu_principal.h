#pragma once

#include "menu.h"

/**
 * @brief Menú principal del juego, hereda de Menu.
 *
 * Opciones: Jugar | Opciones | Acerca | Salir
 * Posición fija en (650, 230). Sonido de clic: Click.wav.
 *
 * Para reaccionar a la opción elegida, sobreescribe onSeleccion()
 * o lee getSeleccionado() / obtenerClickeado() desde la escena.
 */
class MenuPrincipal : public Menu {
public:
  /**
   * @param width  Ancho de la ventana (reservado para futuros ajustes de layout).
   * @param height Alto de la ventana (reservado para futuros ajustes de layout).
   */
  explicit MenuPrincipal(float width = 1280.f, float height = 720.f);
  ~MenuPrincipal() override = default;

protected:
  /**
   * @brief Hook llamado al hacer clic en un ítem.
   *        La escena contenedora (p. ej. EscenaMenu) puede sobreescribirlo
   *        mediante una subclase, o simplemente leer obtenerClickeado().
   */
  void onSeleccion(int indice) override;

private:
  sf::Font font;
};
