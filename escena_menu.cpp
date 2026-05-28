#include "escena_menu.h"

#include <iostream>

EscenaMenu::EscenaMenu()
  : VentanaCueva("Las Profundidades de Eryndor",
         1280,
         720,
         "./recursos/imag/Cueva/cueva_titulo.png",
         "./recursos/sonido/dark-tunnel-ambience.flac")
    , menu(1280.f, 720.f)
{}

void EscenaMenu::updateLayout()
{
  VentanaCueva::updateLayout();

  pantallaJugador.updateLayout(window);
  pantallaJugar.updateLayout(window);
  pantallaOpciones.updateLayout(window);
  pantallaAcerca.updateLayout(window);
}

void EscenaMenu::entrarAJuego()
{
  pantallaActual = Pantalla::Juego;
}

void EscenaMenu::entrarASeleccionJugador()
{
  pantallaJugador.limpiarSeleccion();
  pantallaActual = Pantalla::Jugador;
}

void EscenaMenu::entrarAOpciones()
{
  pantallaActual = Pantalla::Opciones;
}

void EscenaMenu::entrarAAcerca()
{
  pantallaActual = Pantalla::Acerca;
}

void EscenaMenu::volverAlMenu()
{
  pantallaActual = Pantalla::Menu;
}

void EscenaMenu::handleEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
  {
    if (event.type == sf::Event::Closed) {
      window.close();
    }

    if (event.type == sf::Event::Resized) {
      window.setView(sf::View(sf::FloatRect(
          0.f, 0.f,
          static_cast<float>(event.size.width),
          static_cast<float>(event.size.height))));
      updateLayout();
    }

    if (pantallaActual == Pantalla::Juego) {
      if (pantallaJugar.handleEvent(event, window) == PantallaResultado::VolverMenu) {
        volverAlMenu();
      }
      continue;
    }

    if (pantallaActual == Pantalla::Jugador) {
      const auto resultadoJugador = pantallaJugador.handleEvent(event, window);

      if (resultadoJugador == PantallaResultado::VolverMenu) {
        volverAlMenu();
        continue;
      }

      if (resultadoJugador == PantallaResultado::SeleccionHecha) {
        jugadorSeleccionado = pantallaJugador.getJugadorSeleccionado();
        pantallaJugar.setJugadorSeleccionado(jugadorSeleccionado);
        entrarAJuego();
      }

      continue;
    }

    if (pantallaActual == Pantalla::Opciones) {
      if (pantallaOpciones.handleEvent(event, window) == PantallaResultado::VolverMenu) {
        volverAlMenu();
      }
      continue;
    }

    if (pantallaActual == Pantalla::Acerca) {
      if (pantallaAcerca.handleEvent(event, window) == PantallaResultado::VolverMenu) {
        volverAlMenu();
      }
      continue;
    }

    if (event.type == sf::Event::MouseButtonPressed &&
        event.mouseButton.button == sf::Mouse::Left)
    {
      const auto mousePos = window.mapPixelToCoords(
          {event.mouseButton.x, event.mouseButton.y});

      // Botón X de la ventana (comportamiento base)
      if (closeButton.getGlobalBounds().contains(mousePos)) {
        window.close();
        return;
      }

      int clickeado = menu.obtenerClickeado(
          static_cast<int>(mousePos.x),
          static_cast<int>(mousePos.y));

      if (clickeado >= 0) {
        if (clickeado == 0) {
          entrarASeleccionJugador();
        } else if (clickeado == 1) {
          entrarAOpciones();
        } else if (clickeado == 2) {
          entrarAAcerca();
        } else {
          opcionElegida = clickeado;
          window.close();
        }
      }
    }

    if (event.type == sf::Event::MouseMoved) {
      menu.obtenerHover(event.mouseMove.x, event.mouseMove.y);
    }

    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Up)    menu.moverArriba();
      if (event.key.code == sf::Keyboard::Down)  menu.moverAbajo();

      if (event.key.code == sf::Keyboard::Return && menu.haySeleccion()) {
        if (menu.getSeleccionado() == 0) {
          entrarASeleccionJugador();
        } else if (menu.getSeleccionado() == 1) {
          entrarAOpciones();
        } else if (menu.getSeleccionado() == 2) {
          entrarAAcerca();
        } else {
          opcionElegida = menu.getSeleccionado();
          window.close();
        }
      }
    }
  }
}

void EscenaMenu::draw()
{
  if (pantallaActual == Pantalla::Menu) {
    VentanaCueva::draw();
    menu.dibujar(window);
  } else if (pantallaActual == Pantalla::Jugador) {
    window.clear();
    pantallaJugador.draw(window);
  } else if (pantallaActual == Pantalla::Juego) {
    window.clear();
    pantallaJugar.draw(window);
  } else if (pantallaActual == Pantalla::Opciones) {
    window.clear();
    pantallaOpciones.draw(window);
  } else if (pantallaActual == Pantalla::Acerca) {
    window.clear();
    pantallaAcerca.draw(window);
  }
  window.display();
}
