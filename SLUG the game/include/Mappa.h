#pragma once
#include "Stanze.hpp"

struct mappa
{
    Stanza *stanza_attuale;
    // puntatore alla prima stanza
    Stanza *stanze;
};

// inizializza la mappa, inserisce Slug in una stanza vuota e restituisce un puntatore alla mappa
mappa *inizializza_mappa(Slug *p, int livello);

// cambia la stanza in quella passata per indirizzo dalla funzione
void cambia_stanza(Stanza *nuova_stanza);

// aggiunge una stanza dopo la porta (posizione in input)
Stanza *aggiungi_stanza(Stanza *r, enum porta_pos p);

// dealloca le stanze e distrugge la mappa (-> NULL)
void distruggi_mappa(mappa);