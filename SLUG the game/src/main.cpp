#include <iostream>
#include "GestioneTempo.h"
#include "Schermo.hpp"
#include "Mappa.h"
#include "Slug.hpp"
#include "fisica.h"
#include "costanti.h"

#ifdef _WIN32 // sleep fn
#include <Windows.h>
#include <ncursesw/ncurses.h>
#else
#include <unistd.h>
#include <ncurses.h>
#endif

using namespace std;

#define FRAMETIME 30        // durata di un frame ~~> velocità del gioco
#define utom(x) (1000 * x)  // from micro to milli

int sleep_time(timeval inizio, timeval fine);

void controller(Slug *);    // gestisce la tastiera

void exit_game();           // permette di uscire

bool menu(Schermo &);       // apre il menu
void game_loop();
void comandi(Schermo &);    // apre l'interfaccia dei controlli

mappa *game_map;
Slug *slug;
Schermo schermo;

int main()
{
    int chiave;
    do
    {
        // init schermo e slug
        schermo = Schermo();
        slug = new Slug({AMPIEZZA_STANZA / 2, ALTEZZA_STANZA / 2});

        // apro il menu
        bool again;
        do
        {
            again = menu(schermo);
        } while (again);

        // init della mappa
        game_map = inizializza_mappa(slug, 1);

        game_loop();
        chiave = schermo.print_game_over();
        distruggi_mappa(*game_map);
        *game_map = {NULL, NULL};
        delete slug;
        schermo.stop_schermo();

    } while (chiave != tasto_esci);
    exit_game();
}

bool menu(Schermo &schermo)
{
    schermo.start_menugioco();
    int opzione_selezionata, chiave;

    // loop di controllo del menù
    do
    {
        schermo.mg.disegna();
        chiave = getch();
        if (chiave == '\n')
        {
            opzione_selezionata = schermo.mg.get_artefatto_selezionato();
            break;
        }
        else if (chiave == KEY_DOWN || chiave == attacco_giu)
            schermo.mg.seleziona_artefatto_successivo();
        else if (chiave == KEY_UP || chiave == attacco_su)
            schermo.mg.seleziona_artefatto_precedente();
    } while (true);
    schermo.mg.pulisci();

    bool again = false;
    switch (opzione_selezionata)
    {
    case NUOVA_PARTITA:
        // game loop
        break;

    case COMANDI:
        comandi(schermo);
        again = true;
        break;

    case ESCI:
        exit_game();
        break;

    default:
        exit_game();
        break;
    }
    return again;
}

void comandi(Schermo &schermo)
{
    schermo.start_gamecomandi();
    while (getch() != tasto_esci)
        ;
    schermo.cg.pulisci();
}

void game_loop()
{
    timeval inizio_frame, fine_frame;

    schermo.start_interfacciagioco(game_map->stanza_attuale);
    while (!game_over(*slug))
    {
        time_now(inizio_frame);

        controller(slug);

        fai_stanza(game_map->stanza_attuale);
        schermo.ig.set_stanza(game_map->stanza_attuale);
        schermo.ig.gestisci_eventi();

        time_now(fine_frame);
#ifdef _WIN32
        Sleep(sleep_time(inizio_frame, fine_frame));
#else
        usleep(utom(sleep_time(inizio_frame, fine_frame))); // usleep specifica quanti micro secondi sospendere l'esecuzione
#endif
    }
}

void controller(Slug *slug)
{
    int chiave;
    do
    {
        chiave = getch();
        if (chiave - '0' >= 1 && chiave - '0' <= slug_inventory_slots)
        {
            int slot = chiave - '0' - 1;
            continue;
        }
        switch (chiave)
        {
        case KEY_UP:    // attacco_su:
            slug->mossa_su(game_map->stanza_attuale);
            break;
        case KEY_LEFT:  // attacco_sinistra:
            slug->mossa_sinistra(game_map->stanza_attuale);
            break;
        case KEY_RIGHT: // attacco_destra:
            slug->mossa_destra(game_map->stanza_attuale);
            break;
        case KEY_DOWN:  // attacco_giu:
            slug->mossa_giu(game_map->stanza_attuale);
            break;

        case attacco_su:        // KEY_UP:
            crea_proiettile(slug, UP);
            break;
        case attacco_giu:       // KEY_DOWN:
            crea_proiettile(slug, DOWN);
            break;
        case attacco_destra:    // KEY_RIGHT:
            crea_proiettile(slug, RIGHT);
            break;
        case attacco_sinistra:  // KEY_LEFT:
            crea_proiettile(slug, LEFT);
            break;

        case tasto_guarisci:
            slug->use_pozione(game_map->stanza_attuale);
            break;
#ifdef DEBUG
        case tasto_esci:
            exit_game();
            break;
        case 'p': // tasto suicidio
            slug->set_salute(0);
            break;
#endif
        default:
            break;
        }
    } while (chiave != ERR);
}

void exit_game()
{
    schermo.stop_schermo();
    exit(EXIT_SUCCESS);
}

int sleep_time(timeval inizio, timeval fine)
{
    time_t tt = tempo_trascorso(inizio, fine);
    if (tt > FRAMETIME)
        return 0;
    return FRAMETIME - tt;
}
