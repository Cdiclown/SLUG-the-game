#include "Lista.hpp"
#include <cstddef>

Lista::Lista(){
    this->head=NULL;
}

Lista::Lista(node *head)
{
    if (head == NULL)
        this->head = NULL;
    else
    {
        this->head = new node;
        this->head->elemento = head->elemento;
        this->head->next = NULL;
        node *tlcn = this->head;

        for (node *cn = head->next; cn != NULL; cn = cn->next)
        {
            tlcn->next = new node;
            tlcn = tlcn->next;
            tlcn->elemento = cn->elemento;
            tlcn->next = NULL;
        }
    }
}

void Lista::push(void *e) {
    node *nw_head = new node;
    nw_head->elemento=e;
    nw_head->next=this->head;
    this->head=nw_head;
}

void *Lista::pop() {
    if (this->head==NULL)
        return NULL;
    node *npopped=this->head;
    void *epopped=npopped->elemento;

    this->head=npopped->next;
    delete npopped;

    return epopped;
}

void Lista::distruggi() {
    while (pop()!=NULL);
}

bool Lista::elimina_elemento(void *e) {
    node *cn; //current node
    node *tmp;

    if (head==NULL)
        return false;
    if(head->elemento==e) {
        tmp=head;
        this->head=head->next;
        delete tmp;
        return true;
    }
    for(cn=head; cn->next!=NULL; cn=cn->next) {
        if(cn->next->elemento == e) {
            tmp=cn->next;
            cn->next=tmp->next;
            delete tmp;
            return true;
        }
    }
    return false;
}

void Lista::concatena(node *n) {
    node *last;

    if (n!=NULL) {
        for (last=head; last->next!=NULL; last=last->next);
        node *nuovo = new node;
        nuovo->elemento = n->elemento;
        nuovo->next = n->next;

        n = n->next;
        last->next=nuovo;
    }
}

void Lista::concatena(Lista& l) {
    concatena(l.head);
}