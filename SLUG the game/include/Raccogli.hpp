#pragma once
#include "Nucleo.hpp"
#include "Artefatti.hpp"

class Raccogli : public Nucleo
{
protected:
    Artefatto *artefatto;

public:
    Raccogli(coordinate pos, Artefatto *);
    Raccogli(coordinate pos, char display, const char descrizione[], Artefatto *);
    Artefatto *get_artefatto();
};
