#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>

using namespace std;
using namespace sf;

#define Max_main_menu 4

class MenuPrincipal
{
public:
    MenuPrincipal(float width, float height);

    void dibujar(RenderWindow& window);
    void MoverArriba();
    void MoverAbajo();
    void ResaltarItem(int i);
    bool EstaEnBounds(int i, int mouseX, int mouseY);
    int  ObtenerClickeado(int mouseX, int mouseY);

    int MenuPrincipalPresionado()
    {
        return MenuPrincipalSeleccionado;
    }

    ~MenuPrincipal();

private:
    int MenuPrincipalSeleccionado;
    Font font;
    Text menuPrincipal[Max_main_menu];
    SoundBuffer soundBuffer;
    Sound sound;
    bool soundLoaded;
};
