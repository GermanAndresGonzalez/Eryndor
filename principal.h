#pragma once
#include "ventana_cueva.h"
#include "botonera.h"
#include "menu_principal.h"
#include "principal.h"

class MenuPrincipal2 : public VentanaCueva
{

public:
    MenuPrincipal2();
    ~MenuPrincipal2() override = default;
    int getOpcionElegida() const
    {
        return opcionElegida;
    }

protected:
    void handleEvents() override;
    void draw()         override;
    void updateLayout() override;

private:
    enum class Pantalla {
        Menu,
        Juego
    };

    void entrarAJuego();
    void volverAlMenu();

    MenuPrincipal menu;
    //Botonera      botoneraIzquierda;
    //Botonera      botoneraDerecha;
    sf::Texture   pantallaJuegoTexture;
    sf::Sprite    pantallaJuegoSprite;
    Pantalla      pantallaActual = Pantalla::Menu;
    int           opcionElegida = -1;
};





