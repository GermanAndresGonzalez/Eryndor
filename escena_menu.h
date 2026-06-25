#pragma once

#include "ventana_cueva.h"
#include "pantalla_acerca.h"
#include "pantalla_Jugador.h"
#include "pantalla_jugar.h"
#include "pantalla_opciones.h"
#include "menu_principal.h"
#include "pantalla_explorar.h"
#include "pantalla_combate.h"

/**
 * @brief Escena del menú principal: hereda de VentanaCueva y contiene un MenuPrincipal.
 *
 * Patrón usado:
 *   - Herencia de VentanaCueva  → gestión de ventana, fondo y loop.
 *   - Composición de Menu     → lógica del menú desacoplada de la ventana.
 *
 * Para añadir más escenas (p. ej. EscenaOpciones), basta con:
 *   class EscenaOpciones : public VentanaCueva { ... }
 * y agregar el menú correspondiente como miembro.
 */
class EscenaMenu : public VentanaCueva {
public:
  EscenaMenu();
  ~EscenaMenu() override = default;

  /**
   * @brief Opción elegida por el usuario tras run().
   *  0 = Jugar | 1 = Opciones | 2 = Acerca | 3 = Salir | -1 = ninguna
   */
  int getOpcionElegida() const { return opcionElegida; }

protected:
  void handleEvents() override;
  void draw()         override;
  void updateLayout() override;

private:
  enum class Pantalla {
    Menu,
    Combate,
    Explorar,
    Jugador,
    Juego,
    Opciones,
    Acerca
  };

  void entrarAJuego();
  void entrarASeleccionJugador();
  void entrarAOpciones();
  void entrarAAcerca();
  void volverAlMenu();
  void cargarPartidaDesdeOpciones();

  MenuPrincipal menu;
  PantallaJugador pantallaJugador;
  PantallaJugar    pantallaJugar;
  PantallaOpciones pantallaOpciones;
  PantallaAcerca   pantallaAcerca;
  PantallaExplorar pantallaExplorar;
  PantallaCombate pantallaCombate;

  Pantalla      pantallaActual = Pantalla::Menu;
  int           opcionElegida = -1;
  int           jugadorSeleccionado = 1;
};
