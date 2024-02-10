#pragma once

#include "Creature.hpp"
#include "Slug.hpp"
#include "EventiStanze.hpp"
#include "geometria.h"
#include "Raccogli.hpp"

// evento: una creatura si è mossa
class EvCreaturaMossa : public EventoStanze {
    public:
        EvCreaturaMossa(coordinate old_pos, coordinate new_pos, char creatura_display);
        coordinate data[2];
        char ed;
};

// evento: una creatura è stata eliminata
class EvCreaturaEliminata : public EventoStanze {
    public:
        EvCreaturaEliminata(Creatura *e);
        void distruggi();
        Creatura *data;
};

// evento: una stanza è stata modificata
class EvStanzaModificata : public EventoStanze {
    public:
        EvStanzaModificata();
};

// evento: la vita di Slug è stata modificata
class EvVitaModificataS : public EventoStanze {
    public:
        EvVitaModificataS(Slug *p);
        Slug *data;
};

// evento: una creatura ha perso vita
class EvVitaDiminuitaC : public EventoStanze {
    public: 
        EvVitaDiminuitaC(Creatura *e);
        Creatura *data;
};

// evento: è stato modificato l'inventario
class EvInventarioModificato : public EventoStanze {
    public: 
        EvInventarioModificato();
};

// evento: è stato raccolto un artefatto
class EvCreaturaRaccolta : public EventoStanze {
    public:
        EvCreaturaRaccolta(Raccogli *i);
        void distruggi();
        Raccogli *data;
};

// evento: è stato modificato il punteggio
class EvPunteggioModificato : public EventoStanze {
    public:
        EvPunteggioModificato(Slug *p);
        Slug *data;
};
