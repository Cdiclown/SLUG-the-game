#pragma once

#include "Lista.hpp"
class Coda {
    public:
        Coda();
        void distruggi();
        void enqueue(void *);
        void *dequeue();
        // mostra la testa ma non rimuove l'elemento
        void *cerca();
    private:
        node *first;
        node *last;
};
