#pragma once
#include "Creature.hpp"
#include "Artefatti.hpp"
#include "geometria.h"

struct inventario
{
    Artefatto *artefatti[slug_inventory_slots];
    int artefatto_n;
    Pozione pozis;
    Chiave chiavi;
};

class Slug : public Creatura
{
protected:
    int max_salute;
    int punteggio;
    inventario inv;

    // incrementa le statistiche dei Slug se i valori sono positivi e le decrementa se sono negativi
    void add_stats(stats s);

public:
    Slug(coordinate pos);
    Slug(coordinate pos, char display);
    int get_max_salute();
    int get_punteggio();
    void set_salute(int salute);
    void modifica_salute(int salute);
    void set_punteggio(int punteggio);

    inventario get_inventory();

    // inserisce un artefatto in uno slot dell'inventario in particolare
    void add_artefatto(int slot, Artefatto *);

    // inserisce un artefatto nel primo slot dell'inventario libero
    void add_artefatto(Artefatto *);

    // rimuove l'artefatto nello slot dell'inventario indicato, se è presente
    Artefatto *remove_artefatto(int slot);

    // rimuove l'artefatto se è presente nell'inventario
    Artefatto *remove_artefatto(Artefatto *);

    // aggiunge la pozione all'inventario e la elimina dalla stanza
    void add_pozione(Stanza *, Pozione *);

    // rimuove un utilizzo alle pozioni e cura Slug se non ha la vita al massimo
    void use_pozione(Stanza *room);

    // aggiunge la chiave all'inventario e la elimina dalla stanza
    void add_chiave(Stanza *, Chiave *);
    
    // rimuove un utilizzo alla chiave se ne ha, e restituisce se è stata usato oppure no
    bool use_chiave(Stanza *room);
};
