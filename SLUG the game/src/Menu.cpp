#include "Menu.hpp"
#include <cstring>

Menu::Menu(WINDOW *w, int ampiezza, int altezza)
{
    // init variables
    this->win = w;
    this->numero_opzioni = ESCI + 1;
    this->opzione_selezionata = 0;
    strcpy(menus[NUOVA_PARTITA], "Nuova partita");
    strcpy(menus[COMANDI], "Comandi");
    strcpy(menus[ESCI], "Esci dal gioco");

    this->ampiezza = ampiezza;
    this->altezza = altezza;
}

void Menu::disegna() {
    int start_y = this->altezza / 2 ;
    for (int i = 0; i < this->numero_opzioni; i++)
    {
        int length = strlen(this->menus[i]), pad;
        if (length >= this->ampiezza)
            pad = 0;
        else
            pad = (ampiezza - length) / 2;

        if (opzione_selezionata == i)
            wattron(win, A_STANDOUT);

        mvwprintw(win, start_y, pad, "%s", this->menus[i]);
        wattroff(win, A_STANDOUT);
        start_y += 2;
    }

    mvwprintw(win, 4, 0, "A GAME BY:");
    mvwprintw(win, 5, 0, "Annamaria Carriello,");
    mvwprintw(win, 6, 0, "Alice Marinelli,");
    mvwprintw(win, 7, 0, "Simona Paparesta,");
    mvwprintw(win, 8, 0, "e Chiara Tosadori");
    mvwprintw(win, 11, 0, "per il corso di Programmazione");
    mvwprintw(win, 12, 0, "della Laurea in Informatica");

    wrefresh(win);

    WINDOW *slug = newwin(20, 50, 3, 80);
    mvwprintw(slug, 1, 12, "       .-=-.  ");
    mvwprintw(slug, 2, 12, "     .' .--.  '. ");
    mvwprintw(slug, 3, 12, "    :  : .-.'. : ");
    mvwprintw(slug, 4, 12, "    :  : : .': :   (o)o) ");
    mvwprintw(slug, 5, 12, "    :  '. '-' .'   //// ");
    mvwprintw(slug, 6, 12, "    _'.__'--=' '-.///' ");
    mvwprintw(slug, 7, 12, ".-'               / ");
    mvwprintw(slug, 8, 12, "'---..____...---''");

    /*
   .-'''-.   .---.      ___    _   .-_'''-.    
  / _     \  | ,_|    .'   |  | | '_( )_   \   
 (`' )/`--',-./  )    |   .'  | ||(_ o _)|  '  
(_ o _).   \  '_ '`)  .'  '_  | |. (_,_)/___|  
 (_,_). '.  > (_)  )  '   ( \.-.||  |  .-----. 
.---.  \  :(  .  .-'  ' (`. _` /|'  \  '-   .' 
\    `-'  | `-'`-'|___| (_ (_) _) \  `-'`   |  
 \       /   |        \\ /  . \ /  \        /  
  `-...-'    `--------` ``-'`-''    `'-...-'   
    */

    mvwprintw(slug, 10, 0, "   .-'''-.   .---.      ___    _   .-_'''-.    ");
    mvwprintw(slug, 11, 0, "  / _     \\  | ,_|    .'   |  | | '_( )_   \\   ");
    mvwprintw(slug, 12, 0, " (`' )/`--',-./  )    |   .'  | ||(_ o _)|  '  ");
    mvwprintw(slug, 13, 0, "(_ o _).   \\  '_ '`)  .'  '_  | |. (_,_)/___|  ");
    mvwprintw(slug, 14, 0, " (_,_). '.  > (_)  )  '   ( \\.-.||  |  .-----. ");
    mvwprintw(slug, 15, 0, ".---.  \\  :(  .  .-'  ' (`. _` /|'  \\  '-   .' ");
    mvwprintw(slug, 16, 0, "\\    `-'  | `-'`-'|___| (_ (_) _) \\  `-'`   |  ");
    mvwprintw(slug, 17, 0, " \\       /   |        \\\\ /  . \\ /  \\        /  ");
    mvwprintw(slug, 18, 0, "  `-...-'    `--------` ``-'`-''    `'-...-'   ");
    mvwprintw(slug, 19, 17, "- THE GAME -");

    wrefresh(slug);
}

void Menu::seleziona_artefatto_successivo()
{
    this->opzione_selezionata += 1;
    if (this->opzione_selezionata >= numero_opzioni)
        this->opzione_selezionata = 0;
}

void Menu::seleziona_artefatto_precedente()
{
    this->opzione_selezionata -= 1;
    if (this->opzione_selezionata < 0)
        this->opzione_selezionata = numero_opzioni - 1;
}

int Menu::get_artefatto_selezionato()
{
    return this->opzione_selezionata;
}

void Menu::pulisci()
{
    wclear(win);
    wrefresh(win);
    clear();
    refresh();
    delwin(win);
}