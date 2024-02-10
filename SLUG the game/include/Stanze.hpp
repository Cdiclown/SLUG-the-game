#pragma once

#include "Nucleo.hpp"
#include "Creature.hpp"
#include "Lista.hpp"
#include "Slug.hpp"
#include "Muri.hpp"
#include "geometria.h"
#include "EventiStanze.hpp"
#include "Coda.hpp"
#include "Raccogli.hpp"


enum porta_pos
{
    PORTA_SUPERIORE,
    PORTA_DESTRA,
    PORTA_INFERIORE,
    PORTA_SINISTRA
};

struct porta
{
    int posizione;
    Stanza *stanza_successiva;
    bool bloccata;
};

int porta_in_questa_posizione(coordinate);

coordinate *posizione_porta(porta_pos);

class Stanza {
    public:
        // inizializzazione con lista di elementi
        Stanza(int id, Lista muri, Lista oggetti, Lista nuclei);
        Stanza(int id, Lista muri);
        Stanza(int id);

        // date le coordinate, restituisce l'elemento che la occupa, NULL se vuota
        Nucleo *get_elemento_in_questa_posizione(coordinate);
        int get_id();

        // aggiunge elementi alla stanza
        void add_Nucleo(Nucleo *);

        // aggiunge una creatura alla stanza
        void add_creatura(Creatura *);

        // aggiunge un muro alla stanza
        void add_muro(Muro *);

        void add_artefatti_a_terra(Raccogli *);

        // elimina un elemento o nemici dalla stanza
        void delete_elemento_stanza(Nucleo *);

        // restituisce una lista con tutti gli elementi della stanza
        Lista get_elemento_stanza(bool muri_too);

        Lista get_artefatti_a_terra();

        // restituisce una lista con tutti gli oggetti, se il booleano è `true` comprende anche Slug
        Lista get_oggetti(bool slug_too);

        // restituisce una lista contenente i muri della stanza
        Lista get_muri();

        struct porta *porta[4];
        Slug *p;

        // restituisce la stanza nella direzione selezionata, NULL se non c'è una porta
        Stanza *stanza_successiva(enum porta_pos); 
                                        
        // concatena un evento alla coda degli eventi
        void add_evento(EventoStanze *e);

        // toglie dalla coda un evento
        EventoStanze *get_evento();

        // svuota la stanza
        void svuota();

    private:
        int id;
        Lista oggetti;
        Lista nucleo;
        Lista muri;
        Lista artefatti_a_terra;
    
        Coda eventi;

};
