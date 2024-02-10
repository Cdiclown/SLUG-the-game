#include "Schermo.hpp"

#include <iostream>
#include <locale.h>
#ifdef _WIN32 
#include <Windows.h>
#else
#include <unistd.h>
#endif

#define DEFAULT 0

Schermo::Schermo()
{
    setlocale(LC_ALL, "");
    initscr();
    cbreak();             
    noecho();             
    curs_set(0);          
    keypad(stdscr, true); 
    clear();
    getmaxyx(stdscr, stdscr_altezza, stdscr_ampiezza);

    refresh();
}

void Schermo::start_menugioco()
{
    game_menu = newwin(ALTEZZA_STANZA, AMPIEZZA_STANZA *2, 10, 10);
    wrefresh(game_menu);

    this->mg = Menu(game_menu, stdscr_ampiezza / 2, stdscr_altezza / 2);
}

void Schermo::start_interfacciagioco(Stanza *r)
{
    nodelay(stdscr, TRUE);

    int ampiezza_laterale = 22,
        altezza_inferiore = 10,
        altezza_slugstats = 10,
        altezza_inventario = 6,
        altezza_legenda = ALTEZZA_STANZA + altezza_inferiore - altezza_slugstats - altezza_inventario,
        ampiezza_listanemici = AMPIEZZA_STANZA/2,
        start_x = 1,
        start_y = 0,
        start_x_laterale = AMPIEZZA_STANZA + 1 + start_x,
        start_y_inferiore = ALTEZZA_STANZA;

    wstanza = newwin(ALTEZZA_STANZA, AMPIEZZA_STANZA, start_y, start_x);
    slugstats = newwin(altezza_slugstats, AMPIEZZA_STANZA/2, start_y_inferiore + start_y, AMPIEZZA_STANZA/2 +1);
    legenda = newwin(altezza_legenda, ampiezza_laterale, start_y, start_x_laterale);
    inventario = newwin(altezza_inventario, ampiezza_laterale, altezza_legenda + start_y, start_x_laterale);
    listanemici = newwin(altezza_inferiore, ampiezza_listanemici, start_y_inferiore + start_y, start_x);
    box(wstanza, 0, 0);
    box(slugstats, 0, 0);
    box(legenda, 0, 0);
    box(inventario, 0, 0);
    box(listanemici, 0, 0);

    wnoutrefresh(wstanza);
    wnoutrefresh(slugstats);
    wnoutrefresh(legenda);
    wnoutrefresh(listanemici);
    wnoutrefresh(inventario);
    doupdate();

    this->ig = Interfaccia(wstanza, slugstats, legenda, listanemici, inventario,
                             {ampiezza_laterale,
                              altezza_inferiore,
                              altezza_slugstats,
                              altezza_legenda,
                              altezza_inventario,
                              ampiezza_listanemici,
                              start_x,
                              start_y,
                              start_x_laterale,
                              start_y_inferiore});
    this->ig.set_stanza(r);
    this->ig.visualizza_stanza();
    this->ig.visualizza_inventario();
    this->ig.visualizza_legenda();
    this->ig.visualizza_listanemici();
    this->ig.visualizza_slugstats();
}

void Schermo::start_gamecomandi()
{
    comandi = newwin(stdscr_altezza, stdscr_ampiezza, 0, 0);
    wrefresh(comandi);
    this->cg = Comandi(comandi);
}

int Schermo::print_game_over()
{
    wclear(inventario);
    wclear(legenda);
    wclear(listanemici);
    wclear(wstanza);
    wclear(slugstats);

    wnoutrefresh(inventario);
    wnoutrefresh(legenda);
    wnoutrefresh(listanemici);
    wnoutrefresh(wstanza);
    wnoutrefresh(slugstats);
    doupdate();

/*
  .-_'''-.      ____    ,---.    ,---.    .-''-.              ,-----.    ,---.  ,---.   .-''-.  .-------.     
 '_( )_   \   .'  __ `. |    \  /    |  .'_ _   \           .'  .-,  '.  |   /  |   | .'_ _   \ |  _ _   \    
|(_ o _)|  ' /   '  \  \|  ,  \/  ,  | / ( ` )   '         / ,-.|  \ _ \ |  |   |  .'/ ( ` )   '| ( ' )  |    
. (_,_)/___| |___|  /  ||  |\_   /|  |. (_ o _)  |        ;  \  '_ /  | :|  | _ |  |. (_ o _)  ||(_ o _) /    
|  |  .-----.   _.-`   ||  _( )_/ |  ||  (_,_)___|        |  _`,/ \ _/  ||  _( )_  ||  (_,_)___|| (_,_).' __  
'  \  '-   .'.'   _    || (_ o _) |  |'  \   .---.        : (  '\_/ \   ;\ (_ o._) /'  \   .---.|  |\ \  |  | 
 \  `-'`   | |  _( )_  ||  (_,_)  |  | \  `-'    /         \ `"/  \  ) /  \ (_,_) /  \  `-'    /|  | \ `'   / 
  \        / \ (_ o _) /|  |      |  |  \       /           '. \_/``".'    \     /    \       / |  |  \    /  
   `'-...-'   '.(_,_).' '--'      '--'   `'-..-'              '-----'       `---`      `'-..-'  ''-'   `'-'   
*/

    int text_altezza = 17, text_ampiezza = 42, current_y = (stdscr_altezza - text_altezza) / 2 - 3, current_x = (stdscr_ampiezza - text_ampiezza) / 2;
    nodelay(stdscr, FALSE);
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "  .-_'''-.      ____    ,---.    ,---.    .-''-.  ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", " '_( )_   \\   .'  __ `. |    \\  /    |  .'_ _   \\           ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "|(_ o _)|  ' /   '  \\  \\|  ,  \\/  ,  | / ( ` )   '         ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", ". (_,_)/___| |___|  /  ||  |\\_   /|  |. (_ o _)  |          ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "|  |  .-----.   _.-`   ||  _( )_/ |  ||  (_,_)___|    ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "'  \\  '-   .'.'   _    || (_ o _) |  |'  \\   .---.   ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", " \\  `-'`   | |  _( )_  ||  (_,_)  |  | \\  `-'    /    ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "  \\        / \\ (_ o _) /|  |      |  |  \\       /      ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "   `'-...-'   '.(_,_).' '--'      '--'   `'-..-'       ");
    current_y += 2;
    mvprintw(current_y, current_x, "%s", "   ,-----.    ,---.  ,---.   .-''-.  .-------.     ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", " .'  .-,  '.  |   /  |   | .'_ _   \\ |  _ _   \\   ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "/ ,-.|  \\ _ \\ |  |   |  .'/ ( ` )   '| ( ' )  | ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "|  _`,/ \\ _/  ||  _( )_  ||  (_,_)___|| (_,_).' ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", ": (  '\\_/ \\   ;\\ (_ o._) /'  \\   .---.|  |\\ \\   ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", " \\ `/  \\  ) /   \\ (_,_) /  \\  `-'    /|  | \\ `'");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "  '. \\_/`` .'    \\     /    \\       / |  |  \\   \\ ");
    current_y += 1;
    mvprintw(current_y, current_x, "%s", "    '-----'       `---`      `'-..-'  ''-'   `'-'");
    mvprintw(stdscr_altezza - 5, 0, "Premi %c per ricominciare o %c per tornare al terminale...", tasto_nuova_partita, tasto_esci);
    refresh();
    int chiave;
    do
        chiave = getch();
    while (chiave != tasto_nuova_partita && chiave != tasto_esci);
    return chiave;
}

void Schermo::stop_schermo() {
    endwin();
}