#include "Interfaccia.hpp"

#include "Eventi.hpp"
#include "Muri.hpp"
#include "costanti.h"
#include <cstring>

Interfaccia::Interfaccia(WINDOW *wstanza, WINDOW *pstat, WINDOW *legenda, WINDOW *listanemici, WINDOW *inv, coordinate_interfaccia c)
{
    this->wstanza = wstanza;
    this->slugstats = pstat;            // statistiche del giocatore (la prima a destra)
    this->legenda = legenda;            // legenda (la seconda a destra)
    this->listanemici = listanemici;    // lista dei nemici (in basso)
    this->inventario = inv;             // inventario (l'ultima a destra)
    this->i_coords = c;
}

void Interfaccia::set_stanza(Stanza *r) { this->r = r; }

void Interfaccia::gestisci_eventi()
{
    EventoStanze *e;
    while ((e = r->get_evento()) != NULL)
    {
        switch (e->id)
        {
        case CREATURA_MOSSA:
        {
            EvCreaturaMossa *t = (EvCreaturaMossa *)e;
            coordinate oldC = t->data[0], newC = t->data[1];
            chtype oldCh = ' ', newCh = t->ed;

            Nucleo *oldE = r->get_elemento_in_questa_posizione(oldC);
            if (oldE != NULL)
                oldCh = oldE->get_display();

            mvwaddch(wstanza, oldC.y, oldC.x, oldCh); // vecchia posizione
            mvwaddch(wstanza, newC.y, newC.x, newCh); // nuova posizione
            wrefresh(wstanza);

            delete t;
            break;
        }
        case STANZA_MODIFICATA:
        {
            EvStanzaModificata *t = (EvStanzaModificata *)e;

            this->visualizza_stanza(); // stampo la stanza per la prima volta
            this->visualizza_legenda();
            this->visualizza_listanemici();

            delete t;
            break;
        }
        case CREATURA_ELIMINATA:
        {
            EvCreaturaEliminata *t = (EvCreaturaEliminata *)e;

            chtype ch = ' ';
            Nucleo *el = r->get_elemento_in_questa_posizione({t->data->get_x(), t->data->get_y()});

            if (el != NULL)
                ch = el->get_display(); 

            mvwaddch(wstanza, t->data->get_y(), t->data->get_x(), ch);
            wnoutrefresh(wstanza);
            this->visualizza_listanemici();

            t->distruggi();
            delete t;
            break;
        }
        case VITA_DIMINUITA_C:
        {
            EvVitaDiminuitaC *t = (EvVitaDiminuitaC *)e;

            this->visualizza_listanemici();

            delete t;
            break;
        }
        case VITA_MODIFICATA_S:
        {
            EvVitaModificataS *t = (EvVitaModificataS *)e;

            this->visualizza_slugstats();

            delete t;
            break;
        }
        case PUNTEGGIO_MODIFICATO:
        {
            EvPunteggioModificato *t = (EvPunteggioModificato *)e;

            mvwprintw(slugstats, 3, 1, "%s: %d", "punti", t->data->get_punteggio());
            wrefresh(slugstats);
            delete t;
            break;
        }
        case INVENTARIO_MODIFICATO:
        {
            EvInventarioModificato *t = (EvInventarioModificato *)e;

            this->visualizza_inventario();

            delete t;
            break;
        }
        case CREATURA_RACCOLTA:
        {
            EvCreaturaRaccolta *t = (EvCreaturaRaccolta *)e;

            char ch = ' ';
            Nucleo *el = r->get_elemento_in_questa_posizione({t->data->get_x(), t->data->get_y()});

            if (el != NULL)
                ch = el->get_display();

            mvwaddch(wstanza, t->data->get_y(), t->data->get_x(), ch);
            wnoutrefresh(wstanza);
            this->visualizza_inventario();
            this->visualizza_slugstats();

            t->distruggi();
            delete t;
            break;
        }
        default:
            break;
        }
    }
}

void Interfaccia::visualizza_stanza()
{
    // pulisco lo schermo da rappresentazioni precedenti
    werase(wstanza);

    // render muri esterni e delle porte
    box(wstanza, 0, 0);
    print_porte(r->porta);

    // render degli elementi (dei muri solo la "testa")
    Lista everything = r->get_elemento_stanza(false);
    node *list = everything.head;

    while (list != NULL)
    {
        Nucleo *c = (Nucleo *)list->elemento;
        if (c->get_x() < AMPIEZZA_STANZA - 1 && c->get_y() < ALTEZZA_STANZA - 1)
            mvwaddch(wstanza, c->get_y(), c->get_x(), c->get_display());
        list = list->next;
    }

    // stampo i muri per intero, procedimento diverso dagli altri elementi perchè sono più caratteri
    Lista muri = r->get_muri();
    list = muri.head;

    while (list != NULL)
    {
        Muro *c = (Muro *)list->elemento;
        if (c->get_x() < AMPIEZZA_STANZA - 1 && c->get_y() < ALTEZZA_STANZA - 1)
        {
            wmove(wstanza, c->get_y(), c->get_x());

            if (c->get_orientamento())                                                      // linea verticale
                wvline(wstanza, c->get_display(), c->get_lunghezza_linea() + 1);            
            else                                                                            // linea orizzontale
                whline(wstanza, c->get_display(), c->get_lunghezza_linea() + 1); 
        }
        list = list->next;
    }
    wrefresh(wstanza);
}

void Interfaccia::visualizza_slugstats()
{
    werase(slugstats);
    box(slugstats, 0, 0);
    // estraggo il slug
    Slug *slug = (Slug *)r->p;
    if (slug == NULL)
        return;

    int start_x = 1;

    int nFullHeart = slug->get_salute() / 2,
        nHalfHeart = slug->get_salute() - nFullHeart * 2,                           
        nEmptyHeart = ((slug->get_max_salute() + 1) / 2) - nFullHeart - nHalfHeart;

    // stampo la vita
    wmove(slugstats, 1, start_x);

    for (int i = 0; i < nFullHeart; i++)
        waddch(slugstats, cuore_intero);

    for (int i = 0; i < nHalfHeart; i++)
        waddch(slugstats, mezzo_cuore);

    for (int i = 0; i < nEmptyHeart; i++)
        waddch(slugstats, cuore_vuoto);

    // stampo i punti
    mvwprintw(slugstats, 3, start_x, "%s: %d", "punti", slug->get_punteggio());

    // stampo le statistiche
    int curr_y = 4, temp;
    mvwprintw(slugstats, curr_y, start_x, "%s: %d", "danno", slug->get_danno());
    mvwprintw(slugstats, 0, 1, "Statistiche");
    wrefresh(slugstats);
}

void Interfaccia::visualizza_legenda()
{
    werase(legenda);
    box(legenda, 0, 0);

    int start_x = 2;
    wmove(legenda, 1, start_x);

    Lista room_member = r->get_elemento_stanza(true);
    node *list = room_member.head;

    char seenDisplay[20];
    int p = 0;

    while (list != NULL)
    {
        Nucleo *c = (Nucleo *)list->elemento;
        bool nw = true;
        char display = c->get_display();

        // eccezioni per i caratteri considerati uguali
        if (display == display_muro_h)
            display = display_muro_v;

        for (int i = 0; i < p; i++)     // controllo se questo carattere è già stato inserito nella legenda
        {
            if (display == seenDisplay[i])
            {
                nw = false;
                break;                  // appena ne trovo uno uguale non lo devo stampare e posso smettere di cercare
            }
        }

        if (nw)                         // se non è stato inserito lo faccio qui
        {
            seenDisplay[p++] = display;
            int x, y;
            getyx(legenda, y, x);
            wmove(legenda, y + 1, start_x);

            char desc[STR_LENGTH];
            c->get_descrizione(desc);
            wprintw(legenda, "%c : %s", display, desc);
        }

        list = list->next;
    }

    mvwprintw(legenda, 0, 1, "Legenda");
    wrefresh(legenda);
}

void Interfaccia::visualizza_listanemici()
{
    werase(listanemici);
    box(listanemici, 0, 0);

    int line = 2, col = 2, gap = 4;

    wmove(listanemici, line, col);
    Lista oggetti = r->get_oggetti(false);
    node *list = oggetti.head;

    while (list != NULL)
    {
        Creatura *c = (Creatura *)list->elemento;

        int start_x, start_y,
            end_x, end_y,
            end_h_x, end_h_y;

        int nFullHeart = c->get_salute() / 2,
            nHalfHeart = c->get_salute() - nFullHeart * 2;

        getyx(listanemici, start_y, start_x); // salvo la posizione del cursore prima di scrivere la prima riga

        char desc[STR_LENGTH];
        c->get_descrizione(desc);
        if (start_x + strlen(desc) + 4 >= (AMPIEZZA_STANZA /2) || start_x + nFullHeart + nHalfHeart >= (AMPIEZZA_STANZA /2))    // +4 alla lunghezza del nome perchè stampo anche altri ch
        {                                                                                                                       // se il nome o la barra della vita non ci sta

            line += 3; // mi sposto sotto
            wmove(listanemici, line, col);
        }
        else
        {
            wprintw(listanemici, "%c : %s", c->get_display(), desc); // stampo la prima riga
            getyx(listanemici, end_y, end_x);                        // salvo la posizione del cursore dopo aver scritto la prima riga
            wmove(listanemici, start_y + 1, start_x);                // mi muovo nella riga sotto

            for (int i = 0; i < nFullHeart; i++) // stampo la barra della vita
                waddch(listanemici, cuore_intero);
            for (int i = 0; i < nHalfHeart; i++)
                waddch(listanemici, mezzo_cuore);

            getyx(listanemici, end_h_y, end_h_x);

            if (end_h_x + gap >= (AMPIEZZA_STANZA /2) || end_x + gap >= (AMPIEZZA_STANZA /2)) // se una delle due coordinate sfora si cambia riga
            {
                line += 3;
                wmove(listanemici, line, col);
            }
            else // altrimenti la nuova posizione sarà la più grande delle due
            {
                if (end_x > end_h_x)
                    wmove(listanemici, end_y, end_x + gap);
                else
                    wmove(listanemici, end_y, end_h_x + gap);
            }

            list = list->next;
        }
    }
    mvwprintw(listanemici, 0, 1, "Nemici");
    wrefresh(listanemici);
}

void Interfaccia::visualizza_inventario()
{
    werase(inventario);
    box(inventario, 0, 0);
    int start_x = 2, curr_x = start_x, start_y = 2, curr_y = start_y, spacing = 2;
    struct inventario p_inv = r->p->get_inventory();
    Pozione p = r->p->get_inventory().pozis;
    Chiave k = r->p->get_inventory().chiavi;

    // stampo il simbolo delle pozioni
    int curr_lvl = p.get_livello();
    if (curr_lvl > 7)
        curr_lvl = 7;
    if (curr_lvl < 1)
        curr_lvl = 1;
    mvwaddch(inventario, start_y, start_x, p.get_display());

    // stampo il resto della riga
    wprintw(inventario, ":%d    %c:%d", p.get_n_utilizzi(), k.get_display(), k.get_n_utilizzi());

    start_y += 2;
    // stampa l'inventario
    for (int i = 0; i < slug_inventory_slots; i++)
    {
        Artefatto *curr = r->p->get_inventory().artefatti[i];
        if (curr != NULL)
        {
            curr_lvl = curr->get_livello();
            if (curr_lvl > 7)
                curr_lvl = 7;
            if (curr_lvl < 1)
                curr_lvl = 1;
            mvwaddch(inventario, start_y, curr_x, curr->get_display());
        }
        else
            mvwaddch(inventario, start_y, curr_x, '_');
        if (curr_x + spacing + 2 >= i_coords.ampiezza_laterale)
        {
            start_y += spacing - 1;
            curr_x = start_x - spacing;
        }

        curr_x += spacing;
    }
    mvwprintw(inventario, 0, 1, "Inventario");
    wrefresh(inventario);
}

void Interfaccia::print_porte(porta *porte[])
{
    for (int i = 0; i < 4; i++)
    {
        if (porte[i] != NULL)
        {
            char porta = display_porta_aperta;
            if (porte[i]->bloccata)
                porta = display_porta_chiusa;
            int yLoc1,
                xLoc1, yLoc2, xLoc2;

            switch ((*porte[i]).posizione)
            {
            case PORTA_SUPERIORE:
                yLoc1 = yLoc2 = 0;
                xLoc1 = (AMPIEZZA_STANZA / 2) - 1;
                xLoc2 = (AMPIEZZA_STANZA / 2);
                break;
            case PORTA_INFERIORE:
                yLoc1 = yLoc2 = ALTEZZA_STANZA - 1;
                xLoc1 = (AMPIEZZA_STANZA / 2) - 1;
                xLoc2 = (AMPIEZZA_STANZA / 2);
                break;
            case PORTA_DESTRA:
                yLoc1 = (ALTEZZA_STANZA / 2) - 1;
                yLoc2 = (ALTEZZA_STANZA / 2);
                xLoc1 = xLoc2 = AMPIEZZA_STANZA - 1;
                break;
            case PORTA_SINISTRA:
                yLoc1 = (ALTEZZA_STANZA / 2) - 1;
                yLoc2 = (ALTEZZA_STANZA / 2);
                xLoc1 = xLoc2 = 0;
                break;

            default:
                break;
            }
            mvwaddch(wstanza, yLoc1, xLoc1, porta);
            mvwaddch(wstanza, yLoc2, xLoc2, porta);
        }
    }
}
