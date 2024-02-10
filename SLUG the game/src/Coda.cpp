#include "Coda.hpp"
#include "Lista.hpp"
#include <cstddef>

Coda::Coda() {
    this->first=NULL;
    this->last=NULL;
}

void Coda::distruggi() {
    while (dequeue()!=NULL);
}

void Coda::enqueue(void *e) {
    if(e==NULL) return;

    node *n = new node;
    n->elemento=e;
    n->next=NULL;

    if (last==NULL) {
        last=n;
        first=n;
    }
    else {
        this->last->next=n;
        this->last=n;
    }

    if(this->first==NULL) this->first=n;
}

void* Coda::dequeue() {
    void *ret_e;
    node *f_n;

    if(first==NULL) return NULL;
    f_n=this->first;
    ret_e=f_n->elemento;

    this->first=this->first->next;

    delete f_n;

    if(first==NULL) last=NULL;

    return ret_e;
}

void* Coda::cerca() { 
    return this->first->elemento;
}
