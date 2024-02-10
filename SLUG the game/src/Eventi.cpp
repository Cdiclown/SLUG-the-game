#include "Eventi.hpp"
#include "EventiStanze.hpp"
#include "geometria.h"

// CREATURA_MOSSA
EvCreaturaMossa::EvCreaturaMossa(coordinate old_pos, coordinate new_pos, char e) : EventoStanze(CREATURA_MOSSA) {
    this->data[0] = old_pos;
    this->data[1] = new_pos;
    this->ed = e;
}

// CREATURA_ELIMINATA
EvCreaturaEliminata::EvCreaturaEliminata(Creatura *e) : EventoStanze(CREATURA_ELIMINATA) {
    this->data = e;
}

void EvCreaturaEliminata::distruggi() {
    delete this->data;
}

// STANZA_MODIFICATA
EvStanzaModificata::EvStanzaModificata() : EventoStanze(STANZA_MODIFICATA) {}

// VITA_MODIFICATA_S
EvVitaModificataS::EvVitaModificataS(Slug *p) : EventoStanze(VITA_MODIFICATA_S) {
    this->data = p;
}

// VITA_DIMINUITA_C
EvVitaDiminuitaC::EvVitaDiminuitaC(Creatura *e) : EventoStanze(VITA_DIMINUITA_C) {
    this->data = e;
}

// INVENTARIO_MODIFICATO
EvInventarioModificato::EvInventarioModificato() : EventoStanze(INVENTARIO_MODIFICATO) {}

// CREATURA_RACCOLTA
EvCreaturaRaccolta::EvCreaturaRaccolta(Raccogli *i) : EventoStanze(CREATURA_RACCOLTA) {
    this->data = i;
}

void EvCreaturaRaccolta::distruggi() {
    delete this->data;
}

EvPunteggioModificato::EvPunteggioModificato(Slug *p) : EventoStanze(PUNTEGGIO_MODIFICATO) {
    this->data = p;
}
