#include "GestioneTempo.h"

time_t tempo_trascorso(timeval inizio, timeval fine)
{
    long seconds = fine.tv_sec - inizio.tv_sec;
    long microseconds = fine.tv_usec - inizio.tv_usec;
    return seconds * 1e3 + microseconds * 1e-3;
}