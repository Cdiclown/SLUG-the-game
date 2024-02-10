#include "Raccogli.hpp"

Raccogli::Raccogli(coordinate pos, char display, const char descrizione[], Artefatto *i) : Nucleo(pos, display, descrizione, true) {
    this->artefatto = i;
};

Raccogli::Raccogli(coordinate pos, Artefatto *i) : Raccogli(pos, i->get_display(), i->get_descrizione(), i){};

Artefatto *Raccogli::get_artefatto() {
    return this->artefatto;
}