#pragma once
#include "geometria.h"
#include "costanti.h"

class Nucleo {
protected:
    coordinate pos;
    char display;
    char descrizione[STR_LENGTH];
    bool attraversabile;

public:
    Nucleo(coordinate pos, char display, const char descrizione[STR_LENGTH], bool attraversabile = false);
    int get_x();
    int get_y();
    char get_display();
    char *get_descrizione();
    void get_descrizione(char[STR_LENGTH]);
    bool controlla_attraversabile();
};
