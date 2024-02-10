#pragma once
#include "Nemici.hpp"

#define antagonista(name)                                           \
    class name : public Nemico                                      \
    {                                                               \
    public:                                                         \
        name(coordinate, int livello = 0, Artefatto *i = NULL);     \
    }

antagonista(Oca);
antagonista(Pollo);
antagonista(Riccio);
antagonista(Lucertola);

// Nemico speciale
antagonista(Serpente);

#undef antagonista