#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif
#include "Stanze.hpp"

struct coordinate_interfaccia
{
    int ampiezza_laterale,
        altezza_inferiore,
        altezza_slugstats,
        altezza_legenda,
        altezza_inventario,
        ampiezza_listanemici,
        start_x,
        start_y,
        start_x_laterale,
        start_y_inferiore;
};

class Interfaccia
{
private:
    WINDOW *wstanza, *slugstats, *legenda, *listanemici, *inventario;
    Stanza *r;
    coordinate_interfaccia i_coords;

    // stampa le porte della stanza
    void print_porte(porta *porte[]);

public:
    Interfaccia() = default;
    Interfaccia(WINDOW *, WINDOW *, WINDOW *, WINDOW *, WINDOW *, coordinate_interfaccia);

    // aggiorna il puntatore con quello della stanza da visualizzare
    void set_stanza(Stanza *r);
    
    // controlla e gestisce gli eventi presenti nella coda
    void gestisci_eventi();

    // gestione delle singole finestre (wstanza, slugstats, legenda, listanemici, inventario) della schermata di gioco

    // pulisce lo schermo, visualizza la stanza e i suoi elementi
    void visualizza_stanza();

    // visualizza la finestra in cui sono presenti le statistiche del giocatore
    void visualizza_slugstats();

    // visualizza la finestra in cui è presente la legenda del gioco
    void visualizza_legenda();

    // visualizza la finestra in cui è presente l'elenco dei nemici nella stanza
    void visualizza_listanemici();

    // visualizza la finestra in cui è presente l'inventario del giocatore
    void visualizza_inventario();
};
