#include "ListaNemici.hpp"
#include "costanti.h"

// concatena i due elementi in input mettendo il simbolo _ in mezzo
#define mc(n, c) n##_##c

// Nemico che implementano i livelli
#define antagonista(name) \
    name::name(coordinate pos, int livello, Artefatto *i) : Nemico(pos, mc(name, display), mc(name, s),                                         \
                                                            {mc(name, danno), mc(name, salute), mc(name, as), mc(name, ms), mc(name, range)},   \
                                                            mc(name, tr), mc(name, intelligenza), livello, mc(name, hs), mc(name, ds), i) {};   \

antagonista(Oca);
antagonista(Pollo);
antagonista(Riccio);
antagonista(Lucertola);

// Nemico speciale
antagonista(Serpente);

#undef antagonista