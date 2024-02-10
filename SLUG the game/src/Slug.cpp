#include "Slug.hpp"
#include "Eventi.hpp"
#include "costanti.h"
#include "Stanze.hpp"
#include <cstddef>

Slug::Slug(coordinate pos) : Slug(pos, slug_display) {}

Slug::Slug(
    coordinate pos,
    char display) : Creatura(pos, display, slug_s, {slug_danno, slug_salute, slug_as, slug_ms, slug_range})
{
    this->inv = {{}, 0, Pozione(lvl1, 10), Chiave(1)};
    for (int i = 0; i < slug_inventory_slots; i++)
        this->inv.artefatti[i] = NULL;

    this->max_salute = slug_salute;
    this->punteggio = 0;
}

int Slug::get_max_salute() {
    return this->max_salute;
    }
int Slug::get_punteggio() {
    return this->punteggio;
    }
void Slug::set_salute(int h) {
    if (h > this->max_salute)
        this->salute = this->max_salute;
    else
        this->salute = h;
}

void Slug::modifica_salute(int h) {
    if (this->salute + h > this->max_salute)
        this->salute = this->max_salute;
    else
        this->salute += h;
}

void Slug::set_punteggio(int punteggio) {
    this->punteggio += punteggio;
}

inventario Slug::get_inventory() {
    return this->inv;
}

void Slug::add_artefatto(int slot, Artefatto *i) {
    if (slot >= slug_inventory_slots)
        return;
    this->inv.artefatti[slot] = i;
    this->inv.artefatto_n += 1;
    add_stats(i->get_stats());
}

void Slug::add_artefatto(Artefatto *i) {
    int slot = 0;
    while (inv.artefatti[slot] != NULL)
        slot += 1;

    add_artefatto(slot, i);
}

Artefatto *Slug::remove_artefatto(int slot) {
    if (inv.artefatti[slot] == NULL)
        return NULL;
    this->inv.artefatto_n -= 1;
    Artefatto *temp = inv.artefatti[slot];
    inv.artefatti[slot] = NULL;
    add_stats(temp->get_stats(true));
    return temp;
}

Artefatto *Slug::remove_artefatto(Artefatto *artefatto) {
    int slot = -1;
    for (int i = 0; i < slug_inventory_slots; i++)
        if (artefatto == inv.artefatti[i])
        {
            slot = i;
            break;
        }

    if (slot == -1)
        return NULL;
    return remove_artefatto(slot);
}

void Slug::add_pozione(Stanza *r, Pozione *p) {
    int lvl = p->get_livello();
    if (lvl > this->inv.pozis.get_livello())
        inv.pozis.set_livello(lvl);
    inv.pozis.add_utilizzi(p->get_n_utilizzi());
    delete p;
    r->add_evento(new EvInventarioModificato());
}

void Slug::use_pozione(Stanza *room) {
    if (salute == max_salute)
        return;
    int cura = this->inv.pozis.use();
    modifica_salute(cura);
    room->add_evento(new EvVitaModificataS(this));
    room->add_evento(new EvInventarioModificato());
}

void Slug::add_chiave(Stanza *r, Chiave *chiave) {
    this->inv.chiavi.add_utilizzi(chiave->get_n_utilizzi());
    delete chiave;
    r->add_evento(new EvInventarioModificato());
}

bool Slug::use_chiave(Stanza *room) {
    bool used = this->inv.chiavi.use();
    if (used)
        room->add_evento(new EvInventarioModificato());
    return used;
}

void Slug::add_stats(stats s) {
    this->danno += s.danno;
    this->salute += s.salute;
    this->max_salute += s.salute;
    this->attacco_vel /= s.attacco_vel;
    this->movimento_vel /= s.movimento_vel;
    this->range += s.range;
}