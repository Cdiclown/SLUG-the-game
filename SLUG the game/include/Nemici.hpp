#pragma once
#include <cstddef>
#include "Creature.hpp"
#include "Artefatti.hpp"

class Nemico : public Creatura
{
protected:
    int range_attacco;
    int salute_scalare;
    int danno_scalare;
    int intelligenza;

public:
    Nemico(coordinate pos, char display, const char descrizione[STR_LENGTH], stats, int range_attacco, int intelligenza, int livello, int salute_scalare, int danno_scalare, Artefatto * = NULL);
    Nemico(coordinate pos, char display, const char descrizione[STR_LENGTH], stats, int range_attacco, int intelligenza, Artefatto * = NULL); // per i nemici che non hanno livello

    int get_range_attacco();
    int get_intelligenza();
};
