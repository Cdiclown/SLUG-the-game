#pragma once

#include "Nucleo.hpp"
#include "geometria.h"
class Muro : public Nucleo {
    public:
        Muro(line);
        bool controlla_muro(coordinate);
        int get_lunghezza_linea();

        // true se è verticale, false se è orizzontale
        bool get_orientamento();

    private:
        int lunghezza_linea;
        bool verticale;

        char char_migliorato(line);
};
