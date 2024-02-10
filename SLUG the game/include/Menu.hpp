#pragma once

#ifdef _WIN32
#include <ncursesw/ncurses.h>
#else
#include <ncurses.h>
#endif

#define STRLEN 20

enum elementimenu {
    NUOVA_PARTITA,
    COMANDI,
    ESCI,
};

class Menu {
private:
    WINDOW *win;
    int numero_opzioni,
        opzione_selezionata,
        ampiezza,
        altezza;
    char menus[ESCI + 1][STRLEN];

public:
    Menu() = default;
    Menu(WINDOW *, int, int);
    void disegna();
    void seleziona_artefatto_successivo();
    void seleziona_artefatto_precedente();
    int get_artefatto_selezionato();
    void pulisci();
};