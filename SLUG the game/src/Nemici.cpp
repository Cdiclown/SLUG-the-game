#include "Nemici.hpp"

Nemico::Nemico (coordinate pos,
                char display,
                const char descrizione[STR_LENGTH],
                stats s,
                int range_attacco,
                int intelligenza,
                int livello,
                int salute_scalare,
                int danno_scalare, Artefatto *d) : Creatura(pos, display, descrizione, s)
{
    this->intelligenza = intelligenza;
    this->salute += livello * salute_scalare;
    this->danno += livello * danno_scalare;
    this->range_attacco = range_attacco;
}

Nemico::Nemico(
    coordinate pos,
    char display,
    const char descrizione[STR_LENGTH],
    stats s,
    int range_attacco,
    int intelligenza, Artefatto *d) : Nemico(pos, display, descrizione, s, range_attacco, intelligenza, 0, 0, 0, d) {}

int Nemico::get_range_attacco() {
    return this->range_attacco;
    }
    
int Nemico::get_intelligenza() {
    return this->intelligenza;
    }