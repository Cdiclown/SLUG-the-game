#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#include "Menu.hpp"
#include "Interfaccia.hpp"
#include "Comandi.hpp"

class Schermo
{
private:
    int stdscr_ampiezza, stdscr_altezza;

public:
    WINDOW *wstanza, *slugstats, *legenda, *listanemici, *inventario, *game_menu, *comandi, *slug;
        
    Menu mg;
    Interfaccia ig;
    Comandi cg;

    Schermo();

    void start_menugioco();
    
    void start_interfacciagioco(Stanza *);
    
    void start_gamecomandi();
    
    int print_game_over();
    
    void stop_schermo();
};