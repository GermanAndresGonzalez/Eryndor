#include "exploracion.h"

#include "archivos.h"

#include <algorithm>
#include <iostream>
#include <random>
#include <sstream>

// ---------------------------------------------------------------------------
// Constantes internas del módulo
// ---------------------------------------------------------------------------
namespace
{
// IDs de ítems
const int idCuraBasica       = 1;
const int idEspadaInicial    = 2;
const int idArmaduraInicial  = 3;
const int idDagaBasica       = 4;
const int idArmaduraComun    = 5;
const int idArmaduraEspecial = 6;

// Rutas de archivos de persistencia
const char* archivoPartidas    = "recursos/archivos/partidas.dat";
const char* archivoInventarios = "recursos/archivos/inventarios.dat";

// Definiciones de ítems (instancias compartidas de solo lectura)


// Plantilla de enemigo


// Generador aleatorio (singleton de módulo)
std::mt19937& generadorAleatorio()
{
    static std::mt19937 gen{std::random_device{}()};
    return gen;
}

int numeroAleatorio(int minimo, int maximo)
{
    std::uniform_int_distribution<int> dist(minimo, maximo);
    return dist(generadorAleatorio());
}
} // namespace

// ---------------------------------------------------------------------------
// Constructor / destructor
// ---------------------------------------------------------------------------
Exploracion::Exploracion()
     //curaBasica      (curaBasicaDefinida),
      //espadaInicial   (espadaInicialDefinida),
      //armaduraInicial (armaduraInicialDefinida),
      //dagaBasica      (dagaBasicaDefinida),
      //armaduraComun   (armaduraComunDefinida),
      //armaduraEspecial(armaduraEspecialDefinida)
{
}

Exploracion::~Exploracion()
{
    guardarProgreso();
    //delete heroe;
    //delete enemigo;
}

// ---------------------------------------------------------------------------
// Configuración
// ---------------------------------------------------------------------------

const char* Exploracion::getNombreJugador() const
{
    return (jugadorSeleccionado == 2) ? "Lyra Voss" : "Kael Draven";
}


//setJugadorSeleccionado


// ---------------------------------------------------------------------------
// Carga desde archivo
// ---------------------------------------------------------------------------
bool Exploracion::cargarPartidaPorId(int idPartida)
{
    ArchivoBinario<Partidas>  archivoPartidasBin(archivoPartidas);
    ArchivoBinario<Inventario> archivoInventariosBin(archivoInventarios);

    if (!archivoPartidasBin.BuscarPorID(idPartida, partidaActual))
    {
        return false;
    }

    if (!archivoInventariosBin.BuscarPorID(idPartida, inventario))
    {
        return false;
    }

    jugadorSeleccionado   = (partidaActual.getIdPersonaje() == 2) ? 2 : 1;
    inventario.setId(partidaActual.getId());
    progresoInicializado  = true;

    reiniciarBatalla();
    return true;
}

bool Exploracion::cargarUltimaPartida()
{
    ArchivoBinario<Partidas> archivoPartidasBin(archivoPartidas);
    const int ultimoId = archivoPartidasBin.ContarRegistros();

    if (ultimoId <= 0)
    {
        return false;
    }

    return cargarPartidaPorId(ultimoId);
}

// ---------------------------------------------------------------------------
// Lógica de combate
// ---------------------------------------------------------------------------
void Exploracion::cargarJugadorSeleccionado()
{
    // Esta función en la versión original solo cargaba la textura del jugador.
    // En la clase de lógica pura no hay texturas, por lo que este método
    // existe para mantener la interfaz que PantallaJugar espera y puede
    // usarse para cualquier inicialización futura ligada al jugador.
    // PantallaJugar debe cargar la imagen usando getNombreJugador() o
    // getRutaImagenJugador() (ver comentario en Exploracion.h).
}

void Exploracion::cargarEnemigoAleatorio()
{
    indiceEnemigo = numeroAleatorio(0, 2);
    //const auto& plantilla = plantillasEnemigos[indiceEnemigo];
    /*
    Enemigos* nuevoEnemigo = new Enemigos(
        plantilla.vidaMaxima,
        plantilla.vidaMaxima,
        plantilla.defensa,
        plantilla.ataque,
        indiceEnemigo + 1,
        plantilla.oroOtorgado,
        plantilla.expOtorgada,
        plantilla.nombre,
        plantilla.descripcion);
    */
    delete enemigo;
    //enemigo = nuevoEnemigo;
}

void Exploracion::reiniciarBatalla()
{
    if (!progresoInicializado)
    {
        inicializarPartidaYInventario();
    }

    Personaje* nuevoHeroe = new Personaje(getNombreJugador(), 5, 100, 20, 10, 50, false);
    delete heroe;
    heroe = nuevoHeroe;
    heroe->equiparArma(&espadaInicial);
    heroe->equiparArmadura(&armaduraInicial);

    if (progresoInicializado)
    {
        partidaActual.idPersonaje = (jugadorSeleccionado == 2) ? 2 : 1;
        inventario.setId(partidaActual.getId());
    }

    turnoCombate           = 0;
    combateFinalizado      = false;
    victoria               = false;
    cantidadMensajesCombate = 0;

    cargarEnemigoAleatorio();
    guardarProgreso();

    registrarMensaje("La batalla comienza contra " + std::string(enemigo->getnombre()) + ".");
    registrarMensaje("Usa A para atacar, C para curar y R para rendirte.");
}

void Exploracion::inicializarPartidaYInventario()
{
    ArchivoBinario<Partidas> archivoPartidasBin(archivoPartidas);
    const int nuevoId    = archivoPartidasBin.GenerarID();
    const int idPersonaje = (jugadorSeleccionado == 2) ? 2 : 1;

    partidaActual = Partidas(nuevoId, idPersonaje, 1);
    partidaActual.GuardarPartida(archivoPartidas);

    inventario = Inventario();
    inventario.setId(partidaActual.getId());
    inventario.agregarItem(idCuraBasica,      2);
    inventario.agregarItem(idEspadaInicial,   1);
    inventario.agregarItem(idArmaduraInicial, 1);
    inventario.GuardarInventario(archivoInventarios);

    progresoInicializado = true;
}

void Exploracion::aplicarAtaqueJugador()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    turnoCombate++;
    registrarMensaje("--- Turno " + std::to_string(turnoCombate) + " ---");

    int danio = heroe->atacar() + numeroAleatorio(-5, 5);
    if (danio < 0) danio = 0;

    const bool critico = (numeroAleatorio(0, 99) < 20);
    if (critico)
    {
        danio *= 2;
        registrarMensaje("GOLPE CRITICO!");
    }

    enemigo->recibirDanio(danio);
    registrarMensaje(std::string(heroe->getNombre()) + " ataca por " +
                     std::to_string(danio) + " de danio.");

    if (enemigo->estaEliminado())
    {
        victoria          = true;
        combateFinalizado = true;
        heroe->agregarOro(enemigo->getoroOtorgado());
        registrarMensaje(std::string("!") + heroe->getNombre() +
                         " ha vencido a " + enemigo->getnombre() + "!");
        registrarMensaje("Oro obtenido: " + std::to_string(enemigo->getoroOtorgado()) +
                         " (total: " + std::to_string(heroe->getOro()) + ")");
        return;
    }

    turnoEnemigo();
}

void Exploracion::aplicarCuracionJugador()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    if (!inventario.tieneCantidadNecesaria(idCuraBasica, 1))
    {
        registrarMensaje("No hay cura disponible");
        return;
    }

    turnoCombate++;
    registrarMensaje("--- Turno " + std::to_string(turnoCombate) + " ---");

    const int curacion = 25 + numeroAleatorio(0, 10);
    if (!heroe->curar(curacion))
    {
        registrarMensaje(std::string(heroe->getNombre()) + " ya tiene la vida al maximo.");
        turnoCombate--;
        return;
    }

    inventario.quitarItem(idCuraBasica, 1);
    inventario.GuardarInventario(archivoInventarios);
    registrarMensaje(std::string(heroe->getNombre()) + " se cura " +
                     std::to_string(curacion) + " puntos de vida.");

    turnoEnemigo();
}

void Exploracion::turnoEnemigo()
{
    if (!heroe || !enemigo || combateFinalizado)
    {
        return;
    }

    int danioEnemigo = enemigo->atacar() + numeroAleatorio(-5, 5);
    if (danioEnemigo < 0) danioEnemigo = 0;

    heroe->recibirDanio(danioEnemigo);
    registrarMensaje(std::string(enemigo->getnombre()) + " ataca por " +
                     std::to_string(danioEnemigo) + " de danio.");

    if (heroe->estaEliminado())
    {
        combateFinalizado = true;
        victoria          = false;
        registrarMensaje(std::string(heroe->getNombre()) + " ha sido derrotado...");
    }
}

// ---------------------------------------------------------------------------
// Persistencia
// ---------------------------------------------------------------------------
void Exploracion::guardarProgreso()
{
    if (!progresoInicializado)
    {
        return;
    }

    partidaActual.GuardarPartida(archivoPartidas);
    inventario.setId(partidaActual.getId());
    inventario.GuardarInventario(archivoInventarios);
}

// ---------------------------------------------------------------------------
// Helpers privados
// ---------------------------------------------------------------------------
void Exploracion::registrarMensaje(const std::string& mensaje)
{
    if (cantidadMensajesCombate < MAX_MENSAJES)
    {
        mensajesCombate[cantidadMensajesCombate++] = mensaje;
    }
    else
    {
        for (std::size_t i = 1; i < MAX_MENSAJES; ++i)
        {
            mensajesCombate[i - 1] = mensajesCombate[i];
        }
        mensajesCombate[MAX_MENSAJES - 1] = mensaje;
    }
}
