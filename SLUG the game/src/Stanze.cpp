#include <cstddef>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include "Nucleo.hpp"
#include "Creature.hpp"
#include "Slug.hpp"
#include "Stanze.hpp"
#include "Lista.hpp"
#include "EventiStanze.hpp"
#include "Muri.hpp"
#include "geometria.h"

int porta_in_questa_posizione(coordinate p) {
    if(p.x == 0 && p.y == (ALTEZZA_STANZA/2) || p.x == 0 && p.y == (ALTEZZA_STANZA/2) - 1)
        return PORTA_SINISTRA;
    else if(p.x == AMPIEZZA_STANZA-1 && p.y == (ALTEZZA_STANZA/2) || p.x ==  AMPIEZZA_STANZA-1 && p.y == (ALTEZZA_STANZA/2) - 1)
        return PORTA_DESTRA;
    else if(p.x == AMPIEZZA_STANZA/2 && p.y == 0 || p.x ==  (AMPIEZZA_STANZA/2) - 1 && p.y == 0)
        return PORTA_SUPERIORE;
    else if(p.x == AMPIEZZA_STANZA/2 && p.y == (ALTEZZA_STANZA-1) || p.x ==  (AMPIEZZA_STANZA/2) - 1 && p.y == (ALTEZZA_STANZA-1))
        return PORTA_INFERIORE;
    else
        return -1;
}

Stanza::Stanza(int id, Lista muri, Lista oggetti, Lista nuclei) : Stanza(id, muri) {
    this->oggetti = Lista(oggetti.head);
    this->nucleo = Lista(nuclei.head);
}

Stanza::Stanza(int id, Lista muri) {
    this->id = id;

    this->p = NULL;

    for (int i = 0; i < 4; i++)
        this->porta[i] = NULL;

    this->oggetti = Lista();
    this->nucleo = Lista();
    this->muri = Lista(muri.head);
}

Stanza::Stanza(int id) {
    this->id = id;

    this->p = NULL;

    for (int i = 0; i < 4; i++)
        this->porta[i] = NULL;

    this->oggetti = Lista();
    this->nucleo = Lista();
    this->muri = Lista();
}

Nucleo *Stanza::get_elemento_in_questa_posizione(coordinate p) {
    node *currentNode;
    Nucleo *nucleo_elm;

    if (this->p != NULL && this->p->get_x() == p.x && this->p->get_y() == p.y)
        return (Nucleo *)this->p;

    for (currentNode = this->oggetti.head; currentNode != NULL; currentNode = currentNode->next)
    {
        nucleo_elm = (Nucleo *) currentNode->elemento;
        if (nucleo_elm->get_x() == p.x && nucleo_elm->get_y() == p.y)
            return (Nucleo *) currentNode->elemento;
    }

    for (currentNode = this->nucleo.head; currentNode != NULL; currentNode = currentNode->next)
    {
        nucleo_elm = ((Nucleo *)currentNode->elemento);
        if (nucleo_elm->get_x() == p.x && nucleo_elm->get_y() == p.y)
            return (Nucleo *) currentNode->elemento;
    }

    for (currentNode = this->muri.head; currentNode != NULL; currentNode = currentNode->next)
    {
        Muro* w = (Muro*) currentNode->elemento;
        if (w->controlla_muro(p))
            return (Nucleo *)currentNode->elemento;
    }

    for (currentNode = this->artefatti_a_terra.head; currentNode != NULL; currentNode = currentNode->next)
    {
        nucleo_elm = (Nucleo *) currentNode->elemento;
        if (nucleo_elm->get_x() == p.x && nucleo_elm->get_y() == p.y)
            return (Nucleo *) currentNode->elemento;
    }
    return NULL;
}

int Stanza::get_id() {
    return this->id;
}

void Stanza::add_Nucleo(Nucleo *e) {
    this->nucleo.push(e);
}

void Stanza::add_creatura(Creatura *e) {
    this->oggetti.push(e);
}

void Stanza::add_muro(Muro *e) {
    this->muri.push(e);
}

void Stanza::add_artefatti_a_terra(Raccogli *i) {
    this->artefatti_a_terra.push(i);
}

void Stanza::delete_elemento_stanza(Nucleo *m) {
    if (oggetti.elimina_elemento(m))
        return;
    else if (nucleo.elimina_elemento(m))
        return;
    else if(artefatti_a_terra.elimina_elemento(m))
        return;
    else
        muri.elimina_elemento(m);
}

Lista Stanza::get_elemento_stanza(bool muri_too) {
    Lista l = get_oggetti(true);
    Lista c = Lista(nucleo.head);
    Lista i = get_artefatti_a_terra();

    l.concatena(c);
    l.concatena(i);
    if (muri_too) {
        Lista w = Lista(muri.head);
        l.concatena(w);
    }
    return l;
}

Lista Stanza::get_oggetti(bool slug_too) {
    Lista l = Lista(oggetti.head);
    if (slug_too)
        l.push(p);
    return l;
}

Lista Stanza::get_muri() {
    return Lista(muri.head);
}

Lista Stanza::get_artefatti_a_terra() {
    return Lista(artefatti_a_terra.head);
}


void Stanza::add_evento(EventoStanze *e) {
    this->eventi.enqueue((void *)e);
}

EventoStanze *Stanza::get_evento() {
    return (EventoStanze *)this->eventi.dequeue();
}

Stanza *Stanza::stanza_successiva(enum porta_pos p) {
    if (this->porta[p] != NULL)
        return this->porta[p]->stanza_successiva;
    else {
        exit(EXIT_FAILURE);
    }
}

void Stanza::svuota() {
#define list_distruggi(list,type) for (;;) {    \
        type *e = ( type *) list.pop();         \
        if (e==NULL)                            \
            break;                              \
        delete e;                               \
    }                                           \

    list_distruggi(this->nucleo, Nucleo);

    list_distruggi(this->oggetti,Creatura);
    list_distruggi(this->muri,Muro);
    list_distruggi(this->artefatti_a_terra,Raccogli);

    for(;;) {
        EventoStanze *e = (EventoStanze*) this->eventi.dequeue();
        if (e == NULL)
            break;
        delete e;
    }
}