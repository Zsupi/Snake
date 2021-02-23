#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdbool.h>

#include "headers\mozgas.h"
#include "headers\debugmalloc.h"



lanc *hozza (lanc* eleje, lanc* vege, Pont n){
    lanc* uj;
    uj = (lanc*)malloc(sizeof(lanc));

    uj->p = n;
    uj->kov = NULL;

    lanc* mozgato;
    mozgato = eleje;

    while(mozgato->kov != NULL){
        mozgato = mozgato->kov;
    }
    mozgato->kov = uj;
    uj->el = mozgato;
    vege->el = uj;


    return eleje;
}

void inic (Adat adat, Pont p){
    adat.eleje->kov = NULL;
    adat.eleje->p.x = p.x;
    adat.eleje->p.y = p.y;
    adat.eleje->el = NULL;

    adat.vege->el = adat.eleje;
    adat.vege->kov = NULL;
    adat.vege->p.x = p.x;
    adat.vege->p.y = p.y;


}

void mozog(lanc* eleje, lanc* vege, IRANY irany){
    if(eleje->kov != NULL){
        lanc* mozgato;
        mozgato = vege->el;

        while(mozgato != eleje){
           mozgato->p = mozgato->el->p;
           mozgato = mozgato->el;
       }
    }

    if(irany == 0){
        eleje->p.x-=20;
    }

    if(irany == 1){
        eleje->p.x+=20;
    }

    if(irany == 2){
        eleje->p.y-=20;
    }

    if(irany == 3){
        eleje->p.y+=20;
    }



}

void festes (lanc *eleje, bool food, Pont etel, SDL_Renderer* renderer, int r, int g, int b, Bomba bomb, bool multi){

       if(food){
            boxRGBA(renderer, etel.x, etel.y, etel.x+19, etel.y+19, 251, 255, 0, 255);
       }


       lanc* mozgato;
       boxRGBA(renderer, eleje->p.x, eleje->p.y, eleje->p.x+19, eleje->p.y+19, r, g, b, 255);
       for(mozgato = eleje->kov; mozgato != NULL; mozgato = mozgato->kov){
            rectangleRGBA(renderer, mozgato->p.x, mozgato->p.y, mozgato->p.x+20, mozgato->p.y+20, r, g, b, 255);
       }
       if(multi){
           for(int i = 0; i < 3-bomb.db; i++){
                boxRGBA(renderer, bomb.hely[i].x, bomb.hely[i].y, bomb.hely[i].x+20, bomb.hely[i].y+20, 0, 0, 0, 255);
           }
       }


}

void vezerles(SDL_Event event, IRANY *irany, bool *leptet, bool* quit, Bomba bomb, Adat adat){
            switch(event.key.keysym.sym){
                case SDLK_LEFT: if(*irany != 1 && *leptet){
                                *irany = left;
                                *leptet = false;

                                }
                                break;

                case SDLK_RIGHT: if(*irany != 0 && *leptet){
                                *irany = right;
                                 *leptet = false;

                                }
                                 break;

                case SDLK_UP:   if(*irany != 3 && *leptet){
                                *irany = up;
                                *leptet = false;

                                }
                              break;

                case SDLK_DOWN: if(*irany != 2 && *leptet){
                                *irany = down;
                                *leptet = false;
                                }
                                break;

                case SDLK_m: if(bomb.db > 0 && adat.eleje->kov != NULL){
                                bomb.hely[bomb.db-3] = adat.vege->el->p;
                                bomb.db -= 1;
                                }
                                break;

                case SDLK_ESCAPE:
                            *quit = true;
                            break;


            }
}


void vezerles_multi(SDL_Event event, IRANY *irany, bool *leptet, bool* quit, Bomba bomb, Adat adat){
            switch(event.key.keysym.sym){
                case SDLK_a: if(*irany != 1 && *leptet){
                                *irany = left;
                                *leptet = false;

                                }
                                break;

                case SDLK_d: if(*irany != 0 && *leptet){
                                *irany = right;
                                 *leptet = false;

                                }
                                 break;

                case SDLK_w:   if(*irany != 3 && *leptet){
                                *irany = up;
                                *leptet = false;

                                }
                              break;

                case SDLK_s: if(*irany != 2 && *leptet){
                                *irany = down;
                                *leptet = false;

                                }
                                break;
                case SDLK_x: if(bomb.db > 0 && adat.eleje->kov != NULL){
                                bomb.hely[bomb.db-3] = adat.vege->el->p;
                                printf("\n----------%d %d\n", bomb.hely[0].x, bomb.hely[0].y);
                                bomb.db -= 1;
                                }
                                break;

                case SDLK_ESCAPE:
                            *quit = true;
                            break;


            }
}
