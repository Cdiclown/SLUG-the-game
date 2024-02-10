#include "Creature.hpp"
#include "Eventi.hpp"
#include "geometria.h"
#include "fisica.h"
#include <cstring>

Creatura::Creatura(coordinate pos, char display, const char descrizione[STR_LENGTH], stats s) : Nucleo(pos, display, descrizione)
{
    this->salute = s.salute;
    this->danno = s.danno;

    this->attacco_vel = s.attacco_vel; // 1 sec
    time_now(this->ultimo_sparo);

    this->movimento_vel = s.movimento_vel;
    time_now(this->ultima_mossa);
    this->ultima_mossa.tv_sec -= (movimento_vel / 1000) + 1; // come sopra

    this->range = s.range;
}

effetto_mossa Creatura::mossa_su(Stanza *room) { return mossa(room, 0, -1); }
effetto_mossa Creatura::mossa_giu(Stanza *room) { return mossa(room, 0, 1); }
effetto_mossa Creatura::mossa_sinistra(Stanza *room) { return mossa(room, -1, 0); }
effetto_mossa Creatura::mossa_destra(Stanza *Stanza) { return mossa(Stanza, 1, 0); }

effetto_mossa Creatura::mossa(Stanza *r, int x, int y)
{
    coordinate n_pos = {this->pos.x + x, this->pos.y + y};
    timeval now;
    time_now(now);
    // se la creatura non può muoversi, termina e ritorna che non c'è stata collisione
    if (tempo_trascorso(ultima_mossa, now) < movimento_vel)
        return TIMEOUT;
    // se la creatura può muoversi, controlla che non ci sia collisione
    if (!collisione(this->pos.x + x, this->pos.y + y, *r))
    {
        r->add_evento(new EvCreaturaMossa(pos, n_pos, this->get_display()));
        this->pos.x += x;
        this->pos.y += y;
        this->ultima_mossa = now;
        return MOVEMENT;
    }
    else
        return COLLISION;
}

void Creatura::riposiziona(coordinate p) { this->pos = p; }

void Creatura::azione(){};

int Creatura::get_danno() { return danno; }

int Creatura::get_salute() { return this->salute; }

void Creatura::set_salute(int salute) { this->salute = salute; }

void Creatura::modifica_salute(int h) { this->salute += h; }

timeval Creatura::get_ultimo_sparo() { return this->ultimo_sparo; }
void Creatura::set_ultimo_sparo(timeval ls) { this->ultimo_sparo = ls; }

int Creatura::get_attacco_vel() { return this->attacco_vel; }
void Creatura::set_attacco_vel(int as) { this->attacco_vel = as; }

timeval Creatura::get_ultima_mossa() { return this->ultima_mossa; }
void Creatura::set_ultima_mossa(timeval lm) { this->ultima_mossa = lm; }

int Creatura::get_movimento_vel() { return this->movimento_vel; }
void Creatura::set_movimento_vel(int ms) { this->movimento_vel = ms; }

int Creatura::get_range() { return this->range; }