
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>

#include "headers\feltetelek.h"
#include "headers\mozgas.h"
#include "headers\debugmalloc.h"

bool benne(lanc* eleje, Pont n){

    if(eleje->kov != NULL && eleje->kov->kov != NULL){
        lanc* mozgato;
        mozgato = eleje->kov->kov;

        while(mozgato != NULL){
            if(mozgato->p.x == n.x && mozgato->p.y == n.y){
                return true;
            }
            mozgato = mozgato->kov;
        }
    }

    return false;
}


bool palyarolki (lanc* eleje){
        if(eleje->p.x >= 1220 || eleje->p.x < 280){
            return true;
        }
        if(eleje->p.y >= 980 || eleje->p.y < 20){
            return true;
        }

        return false;
}

bool benne_teljes(lanc* eleje, Pont n){
        lanc* mozgato;
        mozgato = eleje;

        while(mozgato != NULL){
            if(mozgato->p.x == n.x && mozgato->p.y == n.y){
                return true;
            }
            mozgato = mozgato->kov;
        }

    return false;
}

Pont etelfelt(Adat adat, Pont etel, int* score, lanc* masik){
    if((adat.eleje->p.x == etel.x && adat.eleje->p.y == etel.y) || benne_teljes(adat.eleje, etel)){
        etel = general(adat.eleje, masik);
        if(adat.eleje->kov == NULL){
            adat.eleje = hozza(adat.eleje, adat.vege, adat.eleje->p);
        }
        else{
            adat.eleje = hozza(adat.eleje, adat.vege, adat.eleje->kov->p);
        }
        if(score != NULL){
           *score += 1;
        }

   }
   return etel;
}

Pont general (lanc* eleje, lanc* masik){
    Pont p;
    p.x = rand()%1220;
    p.y = rand()%980;


    while(p.x<=280 || p.x%20 != 0){
        p.x = rand()%1220;
    }
    while(p.y <=20 || p.y%20 != 0){
        p.y = rand()%980;
    }

    if(masik !=NULL){
        while((benne_teljes(eleje, p))){
            while(p.x<=280 || p.x%20 != 0){
                p.x = rand()%1220;
            }
            while(p.y <=20 || p.y%20 != 0){
                p.y = rand()%980;
            }
        }
    }

    while((benne_teljes(masik, p))){
        while(p.x<=280 || p.x%20 != 0){
        p.x = rand()%1220;
        }
        while(p.y <=20 || p.y%20 != 0){
            p.y = rand()%980;
        }
    }



    return p;
}

bool feltetel_single (bool quit, lanc* s){
    quit = palyarolki(s);
    if(!quit){
        quit = benne(s, s->p);
    }

    return quit;
}

bool feltetel_multi(lanc* s_r, lanc* s_b, char* str){

    if(s_b->p.x == s_r->p.x && s_b->p.y == s_r->p.y){
        sprintf(str, "dontetlen");
        return true;
    }


    if(palyarolki(s_r) || benne(s_r, s_r->p) || benne_teljes(s_b, s_r->p)){
            sprintf(str, "kek nyert");
            return true;
       }

    if(palyarolki(s_b) || benne(s_b, s_b->p) || benne_teljes(s_r, s_b->p)){
            sprintf(str, "piros nyert");
            return true;
       }

    return false;

}
