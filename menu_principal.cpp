#include "menu_principal.h"

#include <iostream>

MenuPrincipal::MenuPrincipal(float width, float height)
{
  // --- Fuente ---
  if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf")) {
    std::cerr << "MenuPrincipal: no se encontró la fuente\n";
  }

  // --- Sonido de clic ---
  if (!soundBuffer.loadFromFile("recursos/sonido/Click.wav")) {
    std::cerr << "MenuPrincipal: no se pudo cargar recursos/sonido/Click.wav\n";
    soundLoaded = false;
  } else {
    sound.setBuffer(soundBuffer);
    soundLoaded = true;
  }

  // --- Opciones ---
  const std::string opciones[] = {"Jugar", "Opciones", "Acerca", "Salir"};
  initOpciones(font, opciones, 4, 650.f, 230.f);
}

void MenuPrincipal::onSeleccion(int indice)
{
  // Implementación mínima; la escena contenedora leerá getSeleccionado()
  // o sobreescribirá este método en una subclase de MenuPrincipal.
  (void)indice;
}
