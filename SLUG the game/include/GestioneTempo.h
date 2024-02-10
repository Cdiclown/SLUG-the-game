#include <sys/time.h>

// typedef unsigned long long time64_t;
#define time_now(var) (gettimeofday(&var, 0))

// restituisce il tempo passato tra inizio e fine in millisecondi
time_t tempo_trascorso(timeval inizio, timeval fine);