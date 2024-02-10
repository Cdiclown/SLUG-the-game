#include "Proiettile.hpp"
#include "fisica.h"
#include "costanti.h"
#include "Eventi.hpp"

Proiettile::Proiettile(coordinate pos, int danno, direzione direzione, int range) : Creatura(pos, bullet_display, bullet_d, {danno, 5000, 0, 180, range})
{
    this->d = direzione;
    this->distanza_percorsa = 0;
}

int Proiettile::get_direzione() { return this->d; }

void Proiettile::set_direzione(enum direzione direzione) { this->d = direzione; };

effetto_mossa Proiettile::mossa(Stanza *r, int x, int y)
{
    effetto_mossa out = Creatura::mossa(r, x, y);
    if (this->distanza_percorsa >= this->range && out != TIMEOUT)
        return COLLISION;
    if (out == MOVEMENT)
        distanza_percorsa += 1;
    return out; 
}

effetto_mossa Proiettile::mossa_su(Stanza *room) { return this->mossa(room, 0, -1); }

effetto_mossa Proiettile::mossa_giu(Stanza *room) { return this->mossa(room, 0, 1); }

effetto_mossa Proiettile::mossa_sinistra(Stanza *room) { return this->mossa(room, -1, 0); }

effetto_mossa Proiettile::mossa_destra(Stanza *Stanza) { return this->mossa(Stanza, 1, 0); }