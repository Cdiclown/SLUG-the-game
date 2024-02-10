#include "Artefatti.hpp"
#include <cstring>

Artefatto::Artefatto(artefatto_id id, char display, const char desc[STR_LENGTH], int livello) {
    this->id = id;
    this->display = display;
    strcpy(this->descrizione, desc);
    this->livello = livello;
    this->artefatto_stats = {0, 0, 1, 1, 0};
}

int Artefatto::get_livello() {
    return this->livello;
}

int Artefatto::get_id() {
    return this->id;
}

char Artefatto::get_display() {
    return this->display;
}

char *Artefatto::get_descrizione() {
    char *desc = new char[STR_LENGTH];
    strcpy(desc, this->descrizione);
    return desc;
}

void Artefatto::get_descrizione(char d[STR_LENGTH]) {
    strcpy(d, this->descrizione);
}

stats Artefatto::get_stats(bool negate) {
    stats s = artefatto_stats;
    if (negate) {
        s.danno *= -1;
        s.salute *= -1;
        s.attacco_vel = 1 / s.attacco_vel;
        s.movimento_vel = 1 / s.movimento_vel;
        s.range *= -1;
    }
    return s;
}

Prendibile::Prendibile(artefatto_id id, char display, const char desc[STR_LENGTH], int livello, int n) : Artefatto(id, display, desc, livello) {
    n_utilizzi = n;
}

void Prendibile::set_livello(int lvl) {
    this->livello = lvl;
}

int Prendibile::get_n_utilizzi() {
    return this->n_utilizzi;
}

void Prendibile::set_n_utilizzi(int n) {
    this->n_utilizzi = n;
}

void Prendibile::add_utilizzi(int n) {
    this->n_utilizzi += n;
}

bool Prendibile::use() {
    if (n_utilizzi <= 0)
        return false;
    n_utilizzi -= 1;
    return true;
}

Pozione::Pozione(int livello, int n_util) : Prendibile(pozioni, pozione_display, pozione_d, livello, n_util) {}

int Pozione::use() {
    bool is_used = Prendibile::use();

    if (is_used)
        return livello * 1.5;
    return 0;
}

Chiave::Chiave(int n_util) : Prendibile(chiavi, chiave_display, chiave_d, lvl1, n_util) {}