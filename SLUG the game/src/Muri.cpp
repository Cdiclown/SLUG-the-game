#include "Muri.hpp"
#include "Nucleo.hpp"
#include "costanti.h"

Muro::Muro(line l) : Nucleo(l.p_iniziale, char_migliorato(l), "muro"){
    this->lunghezza_linea=l.length;
    this->verticale=l.verticale;
}

bool Muro::controlla_muro(coordinate p) {
    if (
        verticale
        && p.x == pos.x
        && pos.y <= p.y && p.y <= (pos.y + lunghezza_linea)
        ) return true;
    else if (
        !verticale
        && p.y == pos.y
        && pos.x <= p.x && p.x <= (pos.x + lunghezza_linea)
            ) return true;
    else return false;
}

int Muro::get_lunghezza_linea() {
    return this->lunghezza_linea;
}

bool Muro::get_orientamento() {
    return this->verticale;
}

char Muro::char_migliorato(line l) {
    if (l.verticale) return display_muro_v;
    else return display_muro_h;
}