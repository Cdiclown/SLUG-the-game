#pragma once
#include "Creature.hpp"
#include "Stanze.hpp"
enum direzione
{
    DOWN,
    UP,
    RIGHT,
    LEFT,
    NULLA
};

class Proiettile : public Creatura
{
protected:
    enum direzione d;
    int distanza_percorsa;

    effetto_mossa mossa(Stanza *r, int x, int y);

public:
    Proiettile(coordinate pos, int danno, direzione direzione, int range);

    int get_direzione();
    void set_direzione(enum direzione direzione);
    effetto_mossa mossa_su(Stanza *room);
    effetto_mossa mossa_giu(Stanza *room);
    effetto_mossa mossa_sinistra(Stanza *room);
    effetto_mossa mossa_destra(Stanza *room);
};