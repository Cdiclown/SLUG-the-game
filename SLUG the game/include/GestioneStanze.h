#pragma once
#include "Stanze.hpp"

#define TIPI_STANZA 3
#define SPECIALE_FREQ 10

// genera una stanza random con nemici della difficoltà in input
Stanza *stanza_random(int difficulty);

// genera una stanza speciale con il Serpente
Stanza *stanza_speciale();

// aggiunge alla stanza nemici di difficoltà proporzionale al parametro in input
Stanza *aggiungi_nemici(Stanza* r, int difficulty);

// aggiunge le chiavi e le pozioni alla stanza
Stanza *aggiungi_artefatti(Stanza *r);

// chiude 0, 1 o 2 porte della stanza in input
Stanza *chiudi_porte(Stanza *r);

// genera un id per la nuova stanza
int nuovo_id();

// restituisce un set di coordinate libere nella stanza in input
coordinate coordinate_libere(Stanza& r);