#pragma once

#include <string>

#include "Enemigos.h"
#include "inventario.h"
#include "item.h"
#include "partidas.h"
#include "personaje.h"

// ---------------------------------------------------------------------------
// Exploracion
// Encapsula toda la lógica de un combate por turnos entre un Personaje y un
// Enemigos. No conoce SFML ni ningún elemento gráfico.
//
// Uso típico desde PantallaJugar:
//   combate.setJugadorSeleccionado(id);
//   combate.reiniciarBatalla();          // carga héroe, enemigo, inventario
//   combate.aplicarAtaqueJugador();      // devuelve mensajes nuevos
//   const auto& msgs = combate.getMensajes();
// ---------------------------------------------------------------------------
class Exploracion
{
public:
    // -----------------------------------------------------------------------
    // Construcción
    // -----------------------------------------------------------------------
    Exploracion();
    ~Exploracion();

    Exploracion(const Exploracion&)            = delete;
    Exploracion& operator=(const Exploracion&) = delete;

    // -----------------------------------------------------------------------
    // Configuración previa al combate
    // -----------------------------------------------------------------------

    // Establece qué jugador se usa (1 = Kael Draven, 2 = Lyra Voss).
    void setJugadorSeleccionado(int id);
    int  getJugadorSeleccionado() const { return jugadorSeleccionado; }

    // Intenta cargar una partida guardada por su id; devuelve true si existe.
    bool cargarPartidaPorId(int idPartida);

    // Carga la última partida registrada en el archivo; devuelve true si existe.
    bool cargarUltimaPartida();

    // -----------------------------------------------------------------------
    // Ciclo de combate (los métodos que PantallaJugar debe llamar)
    // -----------------------------------------------------------------------
    void cargarJugadorSeleccionado();
    void cargarEnemigoAleatorio();
    void reiniciarBatalla();
    void aplicarAtaqueJugador();
    void aplicarCuracionJugador();
    void turnoEnemigo();
    void inicializarPartidaYInventario();

    // Persiste la partida e inventario actuales en disco.
    void guardarProgreso();

    // -----------------------------------------------------------------------
    // Consultas de estado (usadas por PantallaJugar para actualizar la UI)
    // -----------------------------------------------------------------------
    bool esCombateFinalizado() const { return combateFinalizado; }
    bool esVictoria()          const { return victoria; }
    int  getTurnoCombate()     const { return turnoCombate; }
    int  getIndiceEnemigo()    const { return indiceEnemigo; }
    int  getIdPartida()        const { return partidaActual.getId(); }
    bool isProgresoInicializado() const { return progresoInicializado; }

    // Punteros de solo lectura al héroe y al enemigo actuales (pueden ser
    // nullptr antes de llamar a reiniciarBatalla).
    const Personaje* getHeroe()   const { return heroe; }
    const Enemigos*  getEnemigo() const { return enemigo; }
    const Inventario& getInventario() const { return inventario; }

    // Log de mensajes del combate (para que PantallaJugar los muestre).
    static constexpr std::size_t MAX_MENSAJES = 8;
    const std::string* getMensajes()         const { return mensajesCombate; }
    std::size_t        getCantidadMensajes()  const { return cantidadMensajesCombate; }

    // Ruta de imagen que corresponde al enemigo actual (vacía si no hay).
    const char* getRutaImagenEnemigo() const;

    // Nombre del jugador seleccionado.
    const char* getNombreJugador() const;

private:
    // -----------------------------------------------------------------------
    // Helpers internos
    // -----------------------------------------------------------------------
    void registrarMensaje(const std::string& mensaje);

    // -----------------------------------------------------------------------
    // Estado de la lógica
    // -----------------------------------------------------------------------
    int  jugadorSeleccionado    = 1;
    int  turnoCombate           = 0;
    bool combateFinalizado      = false;
    bool victoria               = false;
    int  indiceEnemigo          = 0;
    bool progresoInicializado   = false;

    Personaje* heroe   = nullptr;
    Enemigos*  enemigo = nullptr;

    Inventario inventario;
    Partidas   partidaActual;

    // Ítems que el héroe puede equipar / consumir
    Item curaBasica;
    Item espadaInicial;
    Item armaduraInicial;
    Item dagaBasica;
    Item armaduraComun;
    Item armaduraEspecial;

    std::string mensajesCombate[MAX_MENSAJES];
    std::size_t cantidadMensajesCombate = 0;
};
