#pragma once
#include "Nucleo.hpp"
#include "GestioneTempo.h"

class Stanza;
enum effetto_mossa {
    COLLISION,
    MOVEMENT,
    TIMEOUT
};

class Creatura : public Nucleo {
protected:
    int salute;
    int danno;
    int attacco_vel;           // tempo in millisecondi dell'attacco
    timeval ultimo_sparo;
    timeval ultima_mossa;
    int movimento_vel;
    int range;
    
    // restituisce COLLISION se ha provato a muoversi in un pixel occupato, MOVEMENT se si è mosso, TIMEOUT se non può ancora muoversi
    effetto_mossa mossa(Stanza *r, int x, int y);

public:
    Creatura(coordinate pos, char display, const char descrizione[STR_LENGTH], stats);
    effetto_mossa mossa_su(Stanza *room);
    effetto_mossa mossa_giu(Stanza *room);
    effetto_mossa mossa_sinistra(Stanza *room);
    effetto_mossa mossa_destra(Stanza *room);

    void riposiziona(coordinate);
    void azione();

    int get_salute();
    void set_salute(int salute);
    void modifica_salute(int h);
    int get_attacco_vel();
    void set_attacco_vel(int as);
    timeval get_ultimo_sparo();
    void set_ultimo_sparo(timeval ls);
    int get_movimento_vel();
    void set_movimento_vel(int ms);
    timeval get_ultima_mossa();
    void set_ultima_mossa(timeval lm);
    int get_danno();
    int get_range();
};
