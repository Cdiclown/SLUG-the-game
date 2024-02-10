#include "Nucleo.hpp"
#include <cstring>

Nucleo::Nucleo(coordinate pos, char display, const char descrizione[STR_LENGTH], bool attraversabile)
{
    this->pos = pos;
    this->display = display;
    this->attraversabile = attraversabile;
    strcpy(this->descrizione, descrizione);
}

int Nucleo::get_x() { return pos.x; }

int Nucleo::get_y() { return pos.y; }

char Nucleo::get_display() { return display; }

char *Nucleo::get_descrizione()
{
    char *desc = new char[STR_LENGTH];
    strcpy(desc, this->descrizione);
    return desc;
}

void Nucleo::get_descrizione(char d[STR_LENGTH]) { strcpy(d, this->descrizione); }

bool Nucleo::controlla_attraversabile() { return attraversabile; }