#include <cstdlib>
#include <cstddef>
#include "GestioneStanze.h"
#include "Nemici.hpp"
#include "ListaNemici.hpp"

static int id=0;

int nuovo_id() {
    return id++;
}

Stanza *stanza_speciale() {
    Stanza *r = new Stanza(nuovo_id());

    int lv = r->get_id()/10;
    Nemico *special;
    Artefatto *i;

    special = new Serpente(coordinate_libere(*r), 0, i);
    r->add_creatura(special);

    return r;
}

// rappresentazione grafica della stanza 1
//  _____  _____
// |            |
// |            |
//
// |            |
// |_____  _____|
//

Stanza *room0() {

    Stanza *r = new Stanza(nuovo_id());

    for (int i=0; i<4; i++) {
        r->porta[i]=new porta;
        r->porta[i]->posizione=i; // PORTA_SUPERIORE ecc. hanno un valore intero tra 0 e 3
        r->porta[i]->stanza_successiva=NULL;
        r->porta[i]->bloccata=false;
    }

    return r;
}

// rappresentazione grafica della stanza 1
//   _____  _____
//  |         |  |
//  |         |  |
//      |     |
//  |   |        |
//  |___|_  _____|
//

Stanza *room1() {

    Lista wl = Lista();

    int xshift = (1.0/5.0)* AMPIEZZA_STANZA;
    int yshift =  (1.0/3.0)* ALTEZZA_STANZA;

    int xw1 = xshift + rand()%xshift;
    int yw1 = yshift + rand()%yshift;
    int l = ALTEZZA_STANZA - yw1 - 2;

    line lw1 = { { xw1, yw1} , true, l};
    line lw2 = { {AMPIEZZA_STANZA - xw1, 1}, true, l};
    Muro *w1 = new Muro(lw1);
    Muro *w2 = new Muro(lw2);

    wl.push(w1);
    wl.push(w2);

    Stanza *r = new Stanza(nuovo_id(), wl);

    for (int i=0; i<4; i++) {
        r->porta[i]=new porta;
        r->porta[i]->posizione=i; // PORTA_SUPERIORE ecc. hanno un valore intero tra 0 e 3
        r->porta[i]->stanza_successiva=NULL;
        r->porta[i]->bloccata=false;
    }

    return r;
}

// rappresentazione grafica della stanza 2
//  _____  _____
// |   |        |
// |            |
//     |
// |   |        |
// |___|_  _____|
//

Stanza *room2() {

    Lista wl = Lista();

    int xshift = 0.3 * AMPIEZZA_STANZA;

    int x1 = (.2)* AMPIEZZA_STANZA + rand()%xshift -2;
    int y1 = 1;
    int l1 = 1 + rand()%(ALTEZZA_STANZA-3);

    int x2 = x1;
    int y2 = l1 + 4;
    int l2 = ALTEZZA_STANZA - y2 - 2;

    line lw1 = { { x1, y1} , true, l1};
    line lw2 = { { x2, y2}, true, l2};
    Muro *w1 = new Muro(lw1);
    Muro *w2 = new Muro(lw2);

    wl.push(w1);
    wl.push(w2);

    Stanza *r = new Stanza(nuovo_id(), wl);

    for (int i=0; i<4; i++) {
        r->porta[i]=new porta;
        r->porta[i]->posizione=i; // PORTA_SUPERIORE ecc. hanno un valore intero tra 0 e 3
        r->porta[i]->stanza_successiva=NULL;
        r->porta[i]->bloccata=false;
    }

    return r;
}

#define return_room_N(N) case N: return chiudi_porte(aggiungi_nemici( aggiungi_artefatti( room ## N()), difficulty)); break;

Stanza *stanza_random(int difficulty) {
    switch (rand()%TIPI_STANZA) {
        return_room_N(0);
        return_room_N(1);
        return_room_N(2);
        default:
            return new Stanza(nuovo_id());
    }
}

coordinate coordinate_libere(Stanza& r) {
    int x,y;
    do{
        x=1 + rand()%(AMPIEZZA_STANZA-1);
        y=1 + rand()%(ALTEZZA_STANZA-1);
    } while(r.get_elemento_in_questa_posizione({x,y})!=NULL);

    return {x,y};
}

Stanza *aggiungi_artefatti(Stanza *r) {

    const int pozione_probabitilty = pot_prob;
    const int chiave_probability = chiave_prob;
    coordinate c;
    Pozione *p;
    Chiave *k;
    Raccogli *i;

    while(rand()%100 < pozione_probabitilty) {
        c = coordinate_libere(*r);
        
        p = new Pozione();
        i = new Raccogli(c,p);
        r->add_artefatti_a_terra(i);
    }

    while(rand()%100 < chiave_probability) {
        c = coordinate_libere(*r);

        k = new Chiave();
        i = new Raccogli(c,k);
        r->add_artefatti_a_terra(i);
    }

    return r;
}

Stanza *aggiungi_nemici(Stanza* r, int difficulty) {
    int lv,i=difficulty;
    coordinate p;
    Nemico *h;

    while(i>=0) {
        p=coordinate_libere(*r);

        lv=rand()%(i+1);
        i-=lv+1; //entità di livello 0 (virtualmente) potrebbero essere generate infinitamente

        switch (rand()%4) {
			case 0: h = new Oca(p,lv); break;
			case 1: h = new Pollo(p,lv); break;
			case 2: h = new Riccio(p,lv); break;
            case 3: h = new Lucertola(p,lv); break;
        }

        r->add_creatura(h);
    }
    return r;
}

Stanza *chiudi_porte(Stanza *r) {

    int porta_closed = rand() % 2;
    int i=0;
    porta *d;

    while (i<porta_closed) {
        d=r->porta[rand()%4];
        
        if(d==NULL) //porta non esistente, riprova
            continue;

        d->bloccata=true;
        i++;
    }
    return r;
}