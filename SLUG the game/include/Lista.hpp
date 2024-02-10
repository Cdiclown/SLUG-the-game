#pragma once

// questa classe contiene l'implementazione di una lista generica che può contenere qualsiasi tipo di dato, purché sia passato per riferimento

struct node {
    void *elemento;
    node *next;
};

class Lista {
    public:
        Lista();
        // inizializza la lista con una sequenza di nodi già esistente
        Lista(node *head);
        node *head;
        void push(void *);
        void *pop();

        //concatena in coda un'altra lista
        void concatena(node *);
        void concatena(Lista&);

        // elimina un elemento dalla lista (ma non lo dealloca)
        bool elimina_elemento(void *);

        // dealloca la lista (ma non i suoi elementi)
        void distruggi();
};
