#pragma once
#include "costanti.h"

enum artefatto_id {
    artefatto,
    pozioni,
    chiavi
};

class Artefatto {
protected:
    artefatto_id id;
    char display;
    char descrizione[STR_LENGTH];
    int livello;
    stats artefatto_stats;

public:
    Artefatto(artefatto_id id, char display, const char desc[STR_LENGTH], int livello = 1);

    int get_livello();
    int get_id();
    char get_display();
    char *get_descrizione();
    void get_descrizione(char[STR_LENGTH]);
    stats get_stats(bool negate = false);
};

class Prendibile : public Artefatto {
protected:
    int n_utilizzi;

public:
    Prendibile(artefatto_id id, char display, const char desc[STR_LENGTH], int livello = 1, int n_utilizzi = 0);

    void set_livello(int);
    int get_n_utilizzi();
    void set_n_utilizzi(int);
    void add_utilizzi(int);
    bool use();
};

class Pozione : public Prendibile {
public:
    Pozione(int livello = 1, int n_util = 1);
    int use();
};

class Chiave : public Prendibile {
public:
    Chiave(int n_util = 1);
};