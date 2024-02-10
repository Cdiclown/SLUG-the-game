#include "Comandi.hpp"
#include "costanti.h"

Comandi::Comandi(WINDOW *w)
{
    this->comandi = w;
    box(comandi, 0, 0);

    int start_y = 5, start_x = 10, spazio = 10;
    int curr_y = start_y, curr_x = start_x;

    // tasti di movimento
    mvwaddch(comandi, curr_y, curr_x, '^');
    curr_x += spazio;
    mvwprintw(comandi, curr_y, curr_x, "%s", "Premi le frecce per muoverti in una direzione");
    curr_x -= spazio;
    curr_x -= 2;
    curr_y += 1;
    mvwprintw(comandi, curr_y, curr_x, "%c %c %c", '<', 'v', '>');

    // tasti per sparare
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(comandi, curr_y, curr_x, attacco_su);
    curr_x += spazio;
    mvwprintw(comandi, curr_y, curr_x, "%s", "Premi w, a, s, d per sparare in una direzione");
    curr_x -= spazio;
    curr_x -= 2;
    curr_y += 1;
    mvwprintw(comandi, curr_y, curr_x, "%c %c %c", attacco_sinistra, attacco_giu, attacco_destra);

    // cura
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(comandi, curr_y, curr_x, tasto_guarisci);
    curr_x += spazio;
    mvwprintw(comandi, curr_y, curr_x, "%s", "Premi h per usare la pozione curativa");
    curr_x -= spazio;

    // uscita dal gioco
    curr_x = start_x;
    curr_y += 4;
    mvwaddch(comandi, curr_y, curr_x, tasto_esci);
    curr_x += spazio;
    mvwprintw(comandi, curr_y, curr_x, "%s", "Premi q per tornare al terminale");
    curr_x -= spazio;

    // testo finale
    int max_y, max_x;
    getmaxyx(comandi, max_y, max_x);
    mvwprintw(comandi, max_y - 2, 1, "%s", "Premi q per tornare al menu` principale");

    wrefresh(this->comandi);
}

void Comandi::pulisci()
{
    wclear(comandi);
    wrefresh(comandi);
    clear();
    refresh();
    delwin(comandi);
}