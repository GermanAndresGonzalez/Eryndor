#include "MenuPrincipal.h"

MenuPrincipal::MenuPrincipal(float width, float height)
{
    if (!font.loadFromFile("recursos/fuentes/AlexandriaFLF-Bold.ttf"))
    {
        cout << "No se encontró la fuente";
    }

    const int x = 650;
    const int y = 230;
    const int tamCaracter = 55;
    const int espacioEntreOpciones = 75;
    const int cantOpciones = 4;
    const string opciones[cantOpciones] = {"Jugar", "Opciones", "Acerca", "Salir"};

    for (int i = 0; i < cantOpciones; i++)
    {
        menuPrincipal[i].setFont(font);
        menuPrincipal[i].setFillColor(Color::White);
        menuPrincipal[i].setString(opciones[i]);
        menuPrincipal[i].setCharacterSize(tamCaracter);
        menuPrincipal[i].setOutlineColor(Color::White);
        menuPrincipal[i].setOutlineThickness(1.0f);
        menuPrincipal[i].setPosition(x, y + espacioEntreOpciones * i);
    }

    MenuPrincipalSeleccionado = -1;

    // Cargar efecto de sonido para navegación
    if (!soundBuffer.loadFromFile("recursos/sonido/Click.wav"))
    {
        std::cerr << "No se pudo cargar recursos/sonido/Click.wav\n";
        soundLoaded = false;
    }
    else
    {
        sound.setBuffer(soundBuffer);
        soundLoaded = true;
    }
}

MenuPrincipal::~MenuPrincipal()
{
}

void MenuPrincipal::dibujar(RenderWindow& window)
{
    for (int i = 0; i < Max_main_menu; ++i)
    {
        window.draw(menuPrincipal[i]);
    }
}

// Resalta el ítem i y desresalta el anterior.
// Usado tanto por teclado como por hover del mouse.
void MenuPrincipal::ResaltarItem(int i)
{
    if (i == MenuPrincipalSeleccionado) return; // ya está resaltado, nada que hacer

    if (MenuPrincipalSeleccionado != -1)
        menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::White);

    MenuPrincipalSeleccionado = i;
    menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::Blue);
}

// Devuelve el índice del ítem clickeado, o -1 si no se hizo clic en ninguno.
int MenuPrincipal::ObtenerClickeado(int mouseX, int mouseY)
{
    for (int i = 0; i < Max_main_menu; i++)
    {
        if (menuPrincipal[i].getGlobalBounds().contains(
                static_cast<float>(mouseX),
                static_cast<float>(mouseY)))
        {
            ResaltarItem(i);
            if (soundLoaded) sound.play();
            return i;
        }
    }
    return -1;
}

void MenuPrincipal::MoverArriba()
{
    if (MenuPrincipalSeleccionado != -1)
        menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::White);

    MenuPrincipalSeleccionado--;

    if (MenuPrincipalSeleccionado < 0)
        MenuPrincipalSeleccionado = Max_main_menu - 1;

    menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::Blue);

    if (soundLoaded) sound.play();
}

void MenuPrincipal::MoverAbajo()
{
    if (MenuPrincipalSeleccionado != -1)
        menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::White);

    MenuPrincipalSeleccionado++;

    if (MenuPrincipalSeleccionado >= Max_main_menu)
        MenuPrincipalSeleccionado = 0;

    menuPrincipal[MenuPrincipalSeleccionado].setFillColor(Color::Blue);

    if (soundLoaded) sound.play();
}

bool MenuPrincipal::EstaEnBounds(int i, int mouseX, int mouseY)
{
    return menuPrincipal[i].getGlobalBounds().contains(
        static_cast<float>(mouseX),
        static_cast<float>(mouseY)
    );
}
