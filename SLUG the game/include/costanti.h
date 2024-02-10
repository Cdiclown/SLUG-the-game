#pragma once

// definizione delle costanti di gioco

#define STR_LENGTH 20
#define ALTEZZA_STANZA 25
#define AMPIEZZA_STANZA 50

// strutture dati per la gestione delle stanze

enum livello
{
    lvl1 = 1, 
    lvl2,     
    lvl3,     
    lvl4,     
    lvl5,     
    lvl6,     
    lvl7      
};

struct stats
{
    int danno;
    int salute;
    double attacco_vel;
    double movimento_vel;
    int range;
};

// definizione delle componenti grafiche

#define display_porta_aperta ' '
#define display_porta_chiusa 'x'
#define display_muro_h '-'
#define display_muro_v '|'
#define cuore_intero 'H'
#define mezzo_cuore 'h'
#define cuore_vuoto '-'

// definizione dei tasti di gioco

#define attacco_su 'w'
#define attacco_giu 's'
#define attacco_sinistra 'a'
#define attacco_destra 'd'
#define tasto_esci 'q'
#define tasto_guarisci 'h'
#define tasto_nuova_partita 'n'

// definizione delle caratteristiche del giocatore

#define slug_s "giocatore"
#define slug_inventory_slots 5
#define slug_display '@'
#define slug_danno 3
#define slug_salute 14
#define slug_as 1000
#define slug_ms 50
#define slug_range 9

// definizione delle caratteristiche dei nemici

#define MAX_SMARTNESS 10

#define Oca_s "oca"
#define Oca_display 'o'
#define Oca_danno 1
#define Oca_salute 4
#define Oca_as 1500
#define Oca_ms 280
#define Oca_range 6
#define Oca_tr 5
#define Oca_intelligenza 6
#define Oca_ds 1
#define Oca_hs 2

#define Pollo_s "pollo"
#define Pollo_display 'p'
#define Pollo_danno 2
#define Pollo_salute 2
#define Pollo_as 1000
#define Pollo_ms 280
#define Pollo_range 15
#define Pollo_tr 13
#define Pollo_intelligenza 3
#define Pollo_ds 1
#define Pollo_hs 2

#define Riccio_s "riccio"
#define Riccio_display 'r'
#define Riccio_danno 1
#define Riccio_salute 2
#define Riccio_as 800
#define Riccio_ms 250
#define Riccio_range 4
#define Riccio_tr 3
#define Riccio_intelligenza 1
#define Riccio_ds 2
#define Riccio_hs 1

#define Lucertola_s "lucertola"
#define Lucertola_display 'l'
#define Lucertola_danno 3
#define Lucertola_salute 2
#define Lucertola_as 1000
#define Lucertola_ms 5000
#define Lucertola_range 500
#define Lucertola_tr 499
#define Lucertola_intelligenza MAX_SMARTNESS
#define Lucertola_ds 2
#define Lucertola_hs 2

// super nemico
#define Serpente_s "Serpente"
#define Serpente_display 'S'
#define Serpente_danno 5
#define Serpente_salute 14
#define Serpente_as 1500
#define Serpente_ms 200
#define Serpente_range 30
#define Serpente_tr 29
#define Serpente_intelligenza 5
#define Serpente_ds 0
#define Serpente_hs 0

// definizione delle caratteristiche degli artefatti

#define pozione_d "pozione"
#define pozione_display '+'
#define chiave_d "chiave"
#define chiave_display 'k'

#define chiave_prob 20
#define pot_prob 20

// definizione del proiettile

#define bullet_d "bullet_desc"
#define bullet_display '.'