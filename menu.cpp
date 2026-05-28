#include "menu.h"

#include <iostream>

// -----------------------------------------------------------------------------
// Constructor
// -----------------------------------------------------------------------------

Menu::Menu(unsigned int tamCaracter,
           float        espaciado,
           sf::Color    colorNormal,
           sf::Color    colorResaltado)
    : tamCaracter(tamCaracter)
    , espaciado(espaciado)
    , colorNormal(colorNormal)
    , colorResaltado(colorResaltado)
{}

// -----------------------------------------------------------------------------
// Inicialización de ítems (llamada desde el constructor de la clase hija)
// -----------------------------------------------------------------------------

void Menu::initOpciones(const sf::Font&                 font,
                        const std::string                opciones[],
                        std::size_t                      cantidadOpciones,
                        float origenX,
                        float origenY)
{
  items.clear();
  items.reserve(cantidadOpciones);

  for (std::size_t i = 0; i < cantidadOpciones; ++i) {
    sf::Text texto;
    texto.setFont(font);
    texto.setString(opciones[i]);
    texto.setCharacterSize(tamCaracter);
    texto.setFillColor(colorNormal);
    texto.setOutlineColor(colorNormal);
    texto.setOutlineThickness(1.f);
    texto.setPosition(origenX, origenY + espaciado * static_cast<float>(i));
    items.push_back(std::move(texto));
  }
}

// -----------------------------------------------------------------------------
// Dibujo
// -----------------------------------------------------------------------------

void Menu::dibujar(sf::RenderWindow& window)
{
  for (auto& item : items) {
    window.draw(item);
  }
}

// -----------------------------------------------------------------------------
// Navegación por teclado
// -----------------------------------------------------------------------------

void Menu::moverArriba()
{
  if (items.empty()) return;

  if (seleccionado >= 0)
    items[seleccionado].setFillColor(colorNormal);

  seleccionado = (seleccionado <= 0)
                   ? static_cast<int>(items.size()) - 1
                   : seleccionado - 1;

  items[seleccionado].setFillColor(colorResaltado);
  reproducirSonido();
}

void Menu::moverAbajo()
{
  if (items.empty()) return;

  if (seleccionado >= 0)
    items[seleccionado].setFillColor(colorNormal);

  seleccionado = (seleccionado + 1) % static_cast<int>(items.size());

  items[seleccionado].setFillColor(colorResaltado);
  reproducirSonido();
}

// -----------------------------------------------------------------------------
// Interacción con mouse
// -----------------------------------------------------------------------------

int Menu::obtenerHover(int mouseX, int mouseY)
{
  for (int i = 0; i < static_cast<int>(items.size()); ++i) {
    if (items[i].getGlobalBounds().contains(
            static_cast<float>(mouseX),
            static_cast<float>(mouseY)))
    {
      resaltarItem(i);
      return i;
    }
  }
  return -1;
}

int Menu::obtenerClickeado(int mouseX, int mouseY)
{
  for (int i = 0; i < static_cast<int>(items.size()); ++i) {
    if (items[i].getGlobalBounds().contains(
            static_cast<float>(mouseX),
            static_cast<float>(mouseY)))
    {
      resaltarItem(i);
      reproducirSonido();
      onSeleccion(i);   // hook para la clase hija
      return i;
    }
  }
  return -1;
}

// -----------------------------------------------------------------------------
// Helpers internos
// -----------------------------------------------------------------------------

void Menu::resaltarItem(int i)
{
  if (i == seleccionado) return;

  if (seleccionado >= 0)
    items[seleccionado].setFillColor(colorNormal);

  seleccionado = i;
  items[seleccionado].setFillColor(colorResaltado);
}

void Menu::reproducirSonido()
{
  if (soundLoaded) sound.play();
}
