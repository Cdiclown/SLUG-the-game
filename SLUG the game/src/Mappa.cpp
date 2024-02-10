#include <cstddef>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Eventi.hpp"
#include "Mappa.h"
#include "GestioneStanze.h"

static struct mappa game_map;

static int difficulty;

static bool stanza_speciale_successiva = false; // ogni SPECIALE_FREQ stanze la prossima stanza generata è una stanza_speciale

struct mappa *inizializza_mappa(Slug *p, int livello)
{
    srand(time(0));

    Stanza *ptr_start_room = new Stanza(nuovo_id());
    for (int i=0; i<4; i++) {
        ptr_start_room->porta[i]=new porta;
        ptr_start_room->porta[i]->posizione=i; // PORTA_SUPERIORE ecc. hanno un valore intero tra 0 e 3 
        ptr_start_room->porta[i]->stanza_successiva=NULL;
        ptr_start_room->porta[i]->bloccata=false;
    }

    ptr_start_room->p=p;
    
    game_map.stanze=ptr_start_room;
    game_map.stanza_attuale=game_map.stanze;


    ptr_start_room->add_evento(new EvStanzaModificata()); //avviso lo schermo che c'è una nuova stanza da renderizzare
    return &game_map;
}

void cambia_stanza(Stanza *nuova_stanza)
{
    if (nuova_stanza != NULL) {
        //sposto il slug
        nuova_stanza->p=game_map.stanza_attuale->p;
        game_map.stanza_attuale->p=NULL;

        //cambio stanza attuale
        game_map.stanza_attuale=nuova_stanza;
        nuova_stanza->add_evento(new EvStanzaModificata());
        
        difficulty=game_map.stanza_attuale->p->get_punteggio()/10;

    }
}

// il gioco è impostato secondo una struttura ad anello, quindi se la visita ad anello passa per 3 stanze
// allora l'ultima porta deve portare alla stanza di partenza
void create_loop(Stanza *starting_room, int direzione, bool clockwise=true) {
    Stanza *r_ptr=starting_room;
    int next_porta,i;
    for(i=0; i<3;i++) {
        if(clockwise)
            next_porta=(direzione+i)%4;
        else
            next_porta=(direzione-i+4)%4;


        if (r_ptr->porta[next_porta] == NULL || r_ptr->porta[next_porta]->stanza_successiva == NULL)
            return;

        r_ptr = r_ptr->porta[next_porta]->stanza_successiva;
    }

    if(clockwise)
        next_porta=(direzione+i)%4;
    else
        next_porta=(direzione-i+4)%4;
    if(r_ptr->porta[next_porta]==NULL)
        return;

    r_ptr->porta[next_porta]->stanza_successiva=starting_room;
    starting_room->porta[(next_porta +2) % 4]->stanza_successiva = r_ptr;

}

Stanza *aggiungi_stanza(Stanza *r, enum porta_pos p) {
    int i=0;
    porta *d = r->porta[p];
    Stanza *nuova_stanza = stanza_speciale_successiva ? stanza_speciale() : stanza_random(difficulty);

    stanza_speciale_successiva = false;

    d->stanza_successiva=nuova_stanza;

    i = (d->posizione + 2) % 4;
    if (nuova_stanza->porta[i]==NULL)
        nuova_stanza->porta[i]=new porta;

    nuova_stanza->porta[i]->posizione=i;
    nuova_stanza->porta[i]->stanza_successiva=r;
    nuova_stanza->porta[i]->bloccata=false;

    for(int iter=0; iter<4; iter++) {
        create_loop(nuova_stanza, i, true);
        create_loop(nuova_stanza, i, false);
    }

    if(nuova_stanza->get_id() % SPECIALE_FREQ == SPECIALE_FREQ - 1)
        stanza_speciale_successiva = true;

    return nuova_stanza;
}


void distruggi_mappa(mappa m) {
    porta *d;
    int porta_reciproca;
    for(int i=0; i<4; i++) {
        d = m.stanza_attuale->porta[i];
        if (d==NULL || d->stanza_successiva == NULL)
            continue;
        porta_reciproca = (d->posizione + 2) % 4;
        d->stanza_successiva->porta[porta_reciproca]=NULL;
    }

    m.stanza_attuale->svuota();

    for (int i=0; i<4; i++) {
        d=m.stanza_attuale->porta[i];
        if (d!=NULL && d->stanza_successiva !=NULL) {
            distruggi_mappa({d->stanza_successiva, m.stanze});
            delete d;
            m.stanza_attuale->porta[i]=NULL;
        }
    }

    delete m.stanza_attuale;
}
