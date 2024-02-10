#include <cstddef>
#include <iostream>
#include <string.h>
#include "fisica.h"
#include "Eventi.hpp"
#include "Nemici.hpp"
#include "Mappa.h"
#include "GestioneTempo.h"
#include "Raccogli.hpp"
#include "costanti.h"

using namespace std;
Lista bullets = Lista();

bool collisione(int x, int y, Stanza& r){
    coordinate pos_to_check = {x, y};
    bool muro_collision_flag = collisione_muro(pos_to_check, r), creatura_collision_flag = collisione_creatura(pos_to_check, r);

    if(slugsullaporta(pos_to_check, r)) 
        collisione_porta(pos_to_check, r);

    if(muro_collision_flag || creatura_collision_flag) 
        return true;
    else 
        return false;
}

bool slugsullaporta(coordinate pos, Stanza& r){
    bool flag = (r.p->get_x() == pos.x - 1 && r.p->get_y() == pos.y) 
                || (r.p->get_x() == pos.x + 1 && r.p->get_y() == pos.y)
                || (r.p->get_x() == pos.x && r.p->get_y() == pos.y - 1) 
                || (r.p->get_x() == pos.x && r.p->get_y() == pos.y + 1) ;
    
    return flag;
}

bool collisione_muro(coordinate pos, Stanza& r){
    if(pos.y < 1) return true;
    else if(pos.x < 1) return true;
    else if(pos.y > ALTEZZA_STANZA - 2) return true;
    else if( pos.x > AMPIEZZA_STANZA - 2) return true;
    else return false;
}

bool collisione_creatura(coordinate pos, Stanza& r){
    if(r.get_elemento_in_questa_posizione(pos) == NULL || r.get_elemento_in_questa_posizione(pos)->controlla_attraversabile())
        return false;
    else
        return true;
    
}

void collisione_porta(coordinate p, Stanza& r){
    if(p.x == 0 && p.y == (ALTEZZA_STANZA/2) || p.x == 0 && p.y == (ALTEZZA_STANZA/2) - 1){  

        if(posizione_stanza_successiva(r, PORTA_SINISTRA))  riposiziona_slug_nuova_stanza(p, r, PORTA_SINISTRA, PORTA_DESTRA);
           
    }else if(p.x == AMPIEZZA_STANZA-1 && p.y == (ALTEZZA_STANZA/2) || p.x ==  AMPIEZZA_STANZA-1 && p.y == (ALTEZZA_STANZA/2) - 1){
           
        if(posizione_stanza_successiva(r, PORTA_DESTRA))  riposiziona_slug_nuova_stanza(p, r, PORTA_DESTRA, PORTA_SINISTRA);

    }else if(p.x == AMPIEZZA_STANZA/2 && p.y == 0 || p.x ==  (AMPIEZZA_STANZA/2) - 1 && p.y == 0){

        if(posizione_stanza_successiva(r, PORTA_SUPERIORE))  riposiziona_slug_nuova_stanza(p, r, PORTA_SUPERIORE, PORTA_INFERIORE);

    }else if(p.x == AMPIEZZA_STANZA/2 && p.y == (ALTEZZA_STANZA-1) || p.x ==  (AMPIEZZA_STANZA/2) - 1 && p.y == (ALTEZZA_STANZA-1)){
            
        if(posizione_stanza_successiva(r, PORTA_INFERIORE))  riposiziona_slug_nuova_stanza(p, r, PORTA_INFERIORE, PORTA_SUPERIORE);

    }
}

void riposiziona_slug_nuova_stanza(coordinate pos, Stanza& r, enum porta_pos p, enum porta_pos p1){
    int nx,ny,w,h;
    w=AMPIEZZA_STANZA-2;
    h=ALTEZZA_STANZA-2;
    nx=1+((pos.x-1+w)%w);
    ny=1+((pos.y-1+h)%h);
    r.stanza_successiva(p)->p->riposiziona({nx,ny});    
}

bool posizione_stanza_successiva(Stanza& r, enum porta_pos p){
    if (r.porta[p] == NULL)
        return false;
    if (r.porta[p]->bloccata){
        if (r.p->use_chiave(&r)){ // se la porta è sbloccata non devo usare la chiave
            r.porta[p]->bloccata = false;
            r.add_evento(new EvStanzaModificata());
        }
        return false;
    }
    if (r.porta[p]->stanza_successiva != NULL)
        cambia_stanza(r.stanza_successiva(p));
    else
        cambia_stanza(aggiungi_stanza(&r, p));

    bullets.distruggi();
    return true;
}

void crea_proiettile(Creatura *e, enum direzione direzione){
    timeval now;
    time_now(now);
    if(tempo_trascorso(e->get_ultimo_sparo(), now) >= e->get_attacco_vel()){
        Proiettile *b = new Proiettile({e->get_x(), e->get_y()}, e->get_danno(), direzione, e->get_range());
        bullets.push(b);
        time_now(now);
        e->set_ultimo_sparo(now);
    }
}

void danno_slug(Stanza& r, Proiettile *b){
    r.p->set_salute(r.p->get_salute() - b->get_danno());
    r.add_evento(new EvVitaModificataS(r.p));
}

void danno_creatura(Stanza& r, Proiettile *b, Creatura *e){
    e->set_salute(e->get_salute() - r.p->get_danno());   
    if(e->get_salute() <= 0){
        r.p->set_punteggio(e->get_danno() + r.p->get_max_salute());
        r.add_evento(new EvPunteggioModificato(r.p));
        r.delete_elemento_stanza(e);
        r.add_evento(new EvCreaturaEliminata(e));
    }else r.add_evento(new EvVitaDiminuitaC(e));
}

void distruggi_proiettile(Stanza& r, Proiettile *b){
    r.add_evento(new EvCreaturaEliminata(b));
    bullets.elimina_elemento(b); 
}

enum direzione direzione_sparo_nemico(Stanza& r, Nemico *e){
    bool enemy_range_down = (r.p->get_x() == e->get_x() && (r.p->get_y() <= e->get_y() + e->get_range_attacco()) && (r.p->get_y() >= e->get_y()));
    bool enemy_range_up = (r.p->get_x() == e->get_x() && (r.p->get_y() >= e->get_y() - e->get_range_attacco()) && (r.p->get_y() <= e->get_y()));
    bool enemy_range_right = (r.p->get_y() == e->get_y() && (r.p->get_x() <= e->get_x() + e->get_range_attacco()+ 2) && (r.p->get_x() >= e->get_x()));
    bool enemy_range_left = (r.p->get_y() == e->get_y() && (r.p->get_x() >= e->get_x() - e->get_range_attacco() - 2) && (r.p->get_x() <= e->get_x()));
    
    if(enemy_range_down) return DOWN;
    else if(enemy_range_up) return UP;
    else if(enemy_range_right) return RIGHT;
    else if(enemy_range_left) return LEFT;
    return NULLA;
}

bool nemico_nel_range(Stanza& r, Nemico *e){
    bool nemico_nel_range = (r.p->get_x() == e->get_x() && (r.p->get_y() <= e->get_y() + e->get_range_attacco()) && (r.p->get_y() >= e->get_y()))
    || (r.p->get_x() == e->get_x() && (r.p->get_y() >= e->get_y() - e->get_range_attacco()) && (r.p->get_y() <= e->get_y()))
    || (r.p->get_y() == e->get_y() && (r.p->get_x() <= e->get_x() + e->get_range_attacco()+ 2) && (r.p->get_x() >= e->get_x()))
    || (r.p->get_y() == e->get_y() && (r.p->get_x() >= e->get_x() - e->get_range_attacco() - 2) && (r.p->get_x() <= e->get_x()));
    
    return nemico_nel_range;
}

void spara_in_direzione(Stanza& r, Proiettile *b){
    if(b->get_direzione() >= DOWN && b->get_direzione() <= LEFT){
        switch(b->get_direzione()){
            case DOWN:
            {
                if(b->mossa_giu(&r) == COLLISION){
                    if((b->get_y() + 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        danno_slug(r, b);
                    }else{
                        coordinate bpos = {b->get_x(), b->get_y() + 1};
                        if(r.get_elemento_in_questa_posizione(bpos) != NULL && !r.get_elemento_in_questa_posizione(bpos)->controlla_attraversabile() && controlla_creatura(r, (Creatura*)r.get_elemento_in_questa_posizione(bpos))){
                            danno_creatura(r, b, (Nemico*)r.get_elemento_in_questa_posizione(bpos));
                        }
                    }
                    distruggi_proiettile(r, b);                                                     
                }
                break;
            }
            case UP:
                if(b->mossa_su(&r) == COLLISION){
                    if((b->get_y() - 1 == r.p->get_y() && b->get_x() == r.p->get_x())){
                        danno_slug(r, b);
                    }else{
                        coordinate bpos = {b->get_x(), b->get_y() - 1};
                        if(r.get_elemento_in_questa_posizione(bpos) != NULL && !r.get_elemento_in_questa_posizione(bpos)->controlla_attraversabile() && controlla_creatura(r, (Creatura*)r.get_elemento_in_questa_posizione(bpos))){
                            danno_creatura(r, b, (Nemico*)r.get_elemento_in_questa_posizione(bpos));
                        }
                    }      
                    distruggi_proiettile(r, b);                                                      
                }
                break;
            case RIGHT:
                if(b->mossa_destra(&r) == COLLISION){
                    if((b->get_x() + 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        danno_slug(r, b);
                    }else{
                        coordinate bpos = {b->get_x() + 1, b->get_y()};
                        if(r.get_elemento_in_questa_posizione(bpos) != NULL && !r.get_elemento_in_questa_posizione(bpos)->controlla_attraversabile() && controlla_creatura(r, (Creatura*)r.get_elemento_in_questa_posizione(bpos))){
                            danno_creatura(r, b, (Nemico*)r.get_elemento_in_questa_posizione(bpos));
                        }
                    }       
                    distruggi_proiettile(r, b);                                                  
                }
                break;
            case LEFT:
                if(b->mossa_sinistra(&r) == COLLISION){
                    if((b->get_x() - 1 == r.p->get_x() && b->get_y() == r.p->get_y())){
                        danno_slug(r, b);
                    }else{
                        coordinate bpos = {b->get_x() - 1, b->get_y()};
                            if(r.get_elemento_in_questa_posizione(bpos) != NULL && !r.get_elemento_in_questa_posizione(bpos)->controlla_attraversabile() && controlla_creatura(r, (Creatura*)r.get_elemento_in_questa_posizione(bpos))){
                            danno_creatura(r, b, (Nemico*)r.get_elemento_in_questa_posizione(bpos));
                        }
                    }         
                    distruggi_proiettile(r, b);                                                         
                }
                break;
        } 
    }
}

bool controlla_creatura(Stanza& r, Creatura *creatura){
    Lista oggetti = r.get_oggetti(false);
    node *tmp = oggetti.head;
    bool flag = false;
    while(tmp != NULL){
        Nemico *e = (Nemico*) tmp->elemento;
        if(e == creatura) flag = true;
        tmp = tmp->next;  
    }
    return flag;
}

void proiettili_push(Stanza& r){
    Lista oggetti = r.get_oggetti(false);
    node *tmp = oggetti.head;
    while(tmp != NULL){
        Nemico *e = (Nemico*) tmp->elemento;
        if(nemico_nel_range(r, e)){
            direzione temp = direzione_sparo_nemico(r, e);
            if(temp != NULLA)
                crea_proiettile(e, temp);
        }
        tmp = tmp->next;  
    }
}

void proiettile_movimento(Stanza& r){
    node *tmp_bullets = bullets.head;        
    while(tmp_bullets != NULL){
        Proiettile *b = (Proiettile*) tmp_bullets->elemento;
        node *successivo = tmp_bullets->next;
        spara_in_direzione(r, b);
        tmp_bullets = successivo;      
    } 
}

void oggetti_movimento(Stanza &r){
    Lista oggetti = r.get_oggetti(false);
    node *tmp = oggetti.head;
    int low_intelligenza = 0;

    while(tmp != NULL){
        Nemico *e = (Nemico*) tmp->elemento;
        timeval now;
        time_now(now);
        if(tempo_trascorso(e->get_ultima_mossa(), now) >= e->get_movimento_vel()){ 

            if(rand()%(MAX_SMARTNESS/5) + e->get_intelligenza() <= MAX_SMARTNESS/2)
                muovi_in_direzione_random(r,e);
            else
                muovi_in_direzione_slug(r,e);



            time_now(now);
            e->set_ultima_mossa(now);
        }
        tmp = tmp->next;
    }
}

void muovi_in_direzione_random(Stanza &r, Nemico *e){
    int mossa = rand() % 4;
    switch (mossa){
    case 0:
        e->mossa_destra(&r);
        break;
    case 1:
        e->mossa_sinistra(&r);
        break;
    case 2:
        e->mossa_su(&r);
        break;
    case 3:
        e->mossa_giu(&r);
        break;
    default:
        break;
    }
}

void muovi_in_direzione_slug(Stanza &r, Nemico *e){
    bool flag = nemico_nel_range(r, e);
    if(e->get_x() < r.p->get_x() && !flag){
        if(e->mossa_destra(&r) == COLLISION && !flag){
            if(e->mossa_giu(&r) == COLLISION && !flag) e->mossa_su(&r);
        }
    }else if(e->get_x() > r.p->get_x() && !flag){
        if(e->mossa_sinistra(&r) == COLLISION && !flag){
            if(e->mossa_su(&r) == COLLISION && !flag) e->mossa_giu(&r);
        }
    }else if(e->get_y() > r.p->get_y() && !flag){
        if(e->mossa_su(&r) == COLLISION && !flag){
            if(e->mossa_destra(&r) == COLLISION && !flag) e->mossa_sinistra(&r);     
        }
    }else if(e->get_y() < r.p->get_y() && !flag){
        if(e->mossa_giu(&r) == COLLISION && !flag){
            if(e->mossa_destra(&r) == COLLISION && !flag) e->mossa_sinistra(&r);
        }
    }
}

void raccogli_artefatto_da_terra(Stanza &r){
    Lista artefatti_a_terra = r.get_artefatti_a_terra();
    node *artefatti_tmp = artefatti_a_terra.head;
    while(artefatti_tmp != NULL){
        Raccogli *i = (Raccogli*)artefatti_tmp->elemento;
        bool flag = r.p->get_x() == i->get_x() && r.p->get_y() == i->get_y();
        bool full_inventory = r.p->get_inventory().artefatto_n == slug_inventory_slots;
        if(flag && i->get_artefatto()->get_id() == artefatto && !full_inventory){
            r.p->add_artefatto(i->get_artefatto());
        }else if(flag && i->get_artefatto()->get_id() == pozioni){
            r.p->add_pozione(&r,(Pozione*) i->get_artefatto());
        }else if(flag && i->get_artefatto()->get_id() == chiavi){
            r.p->add_chiave(&r, (Chiave*) i->get_artefatto());
        }
        if(flag && !full_inventory){
            r.delete_elemento_stanza(i);
            r.add_evento(new EvCreaturaRaccolta(i));
        }
        artefatti_tmp = artefatti_tmp->next;
    }
}

void fai_stanza(Stanza *r){ // fa cose sulla stanza
    proiettili_push(*r);
    proiettile_movimento(*r);
    oggetti_movimento(*r);
    raccogli_artefatto_da_terra(*r);
}; 

bool game_over(Slug p)
{
    if(p.get_salute()<=0) return true;     //il gioco termina quando finisce la vita 
    else return false;
}