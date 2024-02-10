#pragma once
#include "Slug.hpp"
#include "Stanze.hpp"
#include "Proiettile.hpp"
#include "Nemici.hpp"

// controlla la collisione con i muri esterni della stanza, con gli oggetti e con le porte
bool collisione(int x, int y, Stanza& r);

// controlla che sia Slug a voler attraversare la porta
bool slugsullaporta(coordinate pos, Stanza& r);

// controlla la collisione con i muri esterni della stanza
bool collisione_muro(coordinate pos, Stanza& r);

// controlla la collisione con gli oggetti
bool collisione_creatura(coordinate pos, Stanza& r);

// gestisce la collisione con le porte e il cambio di stanza
void collisione_porta(coordinate pos, Stanza& r);

// controlla che la prossima stanza esista ed elimina i proiettili dalla precedente
bool posizione_stanza_successiva(Stanza& r, enum porta_pos p);

// riposiziona Slug nella nuova stanza
void riposiziona_slug_nuova_stanza(coordinate pos, Stanza& r, enum porta_pos p, enum porta_pos p1);

// sottrae punti vita a Slug ad ogni danno subito
void danno_slug(Stanza& r, Proiettile *b);

// sottrae punti vita ai nemici ad ogni danno subito
void danno_creatura(Stanza& r, Proiettile *b, Creatura *e);

// crea un proiettile e lo inserisce in lista
void crea_proiettile(Creatura *e, enum direzione direzione);

// distrugge un proiettile quando entra in collisione
void distruggi_proiettile(Stanza& r, Proiettile *b);

// controlla che il nemico sia nel range del proiettile
bool nemico_nel_range(Stanza& r, Nemico *e);

// spara nella direzione scelta
void spara_in_direzione(Stanza& r, Proiettile *b);

// determina la direzione dello sparo del nemico
enum direzione direzione_sparo_nemico(Stanza& r, Nemico *e);

// controlla che la creatura passata sia un nemico
bool controlla_creatura(Stanza& r, Creatura *creatura);

// gestisce lo sparo dei proiettili
void proiettili_push(Stanza& r);

// gestisce il movimento dei proiettili
void proiettile_movimento(Stanza& r);

// gestisce il movimento dei nemici in base alla loro intelligenza
void oggetti_movimento(Stanza &r);

// gestisce il movimento dei nemici verso Slug
void muovi_in_direzione_slug(Stanza &r, Nemico *e);

// gestisce il movimento random dei nemici
void muovi_in_direzione_random(Stanza &r, Nemico *e);

// gestisce la raccolta degli artefatti
void raccogli_artefatto_da_terra(Stanza &r);

// gestisce il movimento dei nemici, lo sparo del proiettile e la raccolta degli artefatti nella stanza in input
void fai_stanza(Stanza *r); 

// controlla se Slug è morta
bool game_over(Slug p);