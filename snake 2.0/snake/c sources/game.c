#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <math.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <stdio.h>
#include <string.h>

#include "headers\feltetelek.h"
#include "headers\mozgas.h"
#include "headers\sdl_fgv.h"
#include "headers\game.h"
#include "headers\debugmalloc.h"

/*Fal* letrehoz(void){
    Pont board;
    board.x = 1500;
    board.y = 1000;

    int diff = (board.x-board.y)/2;

    Fal fal[4];
    int index = 0;

    for(int i = 0; i<2; i++{
        for(int j = 0; j<2; j++){
            fal[index].kezd.x=
        }
    }
}*/


void single(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font){


        lanc* s = (lanc*)malloc(sizeof(lanc));
        lanc* s_v = (lanc*)malloc(sizeof(lanc));

        Pont in;
        in.x = 500;
        in.y = 500;


        Pont board;
        board.x = 1500;
        board.y = 1000;

        int diff = (board.x-board.y)/2;


        Bomba bomb;
        bomb.db = -1;

        IRANY irany = 7;

        Adat adat;
        adat.eleje = s;
        adat.vege = s_v;

        inic(adat, in);

        char nev[20+1];

        beker(nev, window, renderer, font);
        int score = 0;

        srand(time(0));

        //idozit
        SDL_TimerID id = SDL_AddTimer(75, idozit, NULL);

        //irányítás

        bool quit = false;
        bool leptet = true;
        bool kigyo = true;

        //kaja
        bool food = true;
        Pont etel;
        etel = general(s, NULL);

        //vezérlés
        while(!quit){

            if(kigyo){
                boxRGBA(renderer, diff, 0, 1000+diff, 1000, 199, 133, 48, 255);
                boxRGBA(renderer, diff+30, 20, 1000+diff-30, 1000-20, 50, 199, 48, 255);
                festes(s, food, etel, renderer, 255, 0, 0, bomb, false);


            //feltételek

                /*for(int i=0; i<3000; i++){
                    lineRGBA(renderer, 0+20*i, 0, 0+20*i, 3000, 255, 255, 255, 255);
                    lineRGBA(renderer, 0, 0+20*i, 3000, 0+20*i, 255, 255, 255, 255);
                }*/
               etel = etelfelt(adat, etel, &score, NULL);
               quit = feltetel_single(quit, s);


               SDL_RenderPresent(renderer);
               kigyo = false;
            }

            SDL_Event event;
            SDL_WaitEvent(&event);


        //mozgatás
            switch(event.type){

                case SDL_USEREVENT:

                mozog(s, s_v, irany);
                kigyo = true;
                leptet = true;
                break;


            case SDL_KEYDOWN:
                vezerles(event, &irany, &leptet, &quit, bomb, adat);
                break;

            case SDL_QUIT:
                            quit = true;
                            break;

            }

        }

        char str[50+1] = "pontod: ";
        pontok(score, str);

        kiir(renderer,nev, str, false);
        filebaki(nev, score);

        SDL_RemoveTimer(id);

        felszabadit(s);
        free(s_v);

        return;
}



void multiplayer (SDL_Window *window, SDL_Renderer *renderer){

    Pont board;
    board.x = 1500;
    board.y = 1000;

    int diff = (board.x-board.y)/2;

    lanc* s_r = (lanc*)malloc(sizeof(lanc));
    lanc* s_v_r = (lanc*)malloc(sizeof(lanc));
    Pont in_r;
    in_r.x = 500;
    in_r.y = 500;

    Adat adat_r;
    adat_r.eleje = s_r;
    adat_r.vege = s_v_r;

    inic(adat_r, in_r);


    Bomba bomb_r;
    bomb_r.db = 3;

    Bomba bomb_b;
    bomb_b.db = 3;


    srand(time(0));

    char str[50+1];
    //idozit
    SDL_TimerID id = SDL_AddTimer(75, idozit, NULL);
    //irányítás
    bool quit = false;
    bool leptet_r = true;
    bool leptet_b = true;
    bool kigyo = true;

    IRANY irany_r;
    IRANY irany_b;
    irany_r = 7;
    irany_b = 7;
    //snake
    lanc* s_b = (lanc*)malloc(sizeof(lanc));
    lanc* s_v_b = (lanc*)malloc(sizeof(lanc));
    Pont in_b;
    in_b.x = 900;
    in_b.y = 700;

    Adat adat_b;
    adat_b.eleje = s_b;
    adat_b.vege = s_v_b;

    inic(adat_b, in_b);
    //kaja
    bool food = true;
    Pont etel;
    etel = general(s_r, s_b);
    //vezérlés
    while(!quit){
        if(kigyo){
            boxRGBA(renderer, diff, 0, 1000+diff, 1000, 199, 133, 48, 255);
            boxRGBA(renderer, diff+30, 20, 1000+diff-30, 1000-20, 50, 199, 48, 255);

            festes(s_r, food, etel, renderer, 255, 0, 0, bomb_r, true);
            festes(s_b, food, etel, renderer, 0, 0, 255, bomb_b, true);
        //feltételek
            etel = etelfelt(adat_r, etel, NULL, s_b);
            etel = etelfelt(adat_b, etel, NULL, s_r);

            quit = feltetel_multi(s_r, s_b, str);

            SDL_RenderPresent(renderer);
            kigyo = false;
        }

        SDL_Event event;
        SDL_WaitEvent(&event);
    //mozgatás
        switch(event.type){

            case SDL_USEREVENT:

                mozog(s_r, s_v_r, irany_r);
                leptet_r = true;

                mozog(s_b, s_v_b, irany_b);
                leptet_b = true;
                kigyo = true;

            case SDL_KEYDOWN:
                vezerles(event, &irany_r, &leptet_r, &quit, bomb_r, adat_r);

                vezerles_multi(event, &irany_b, &leptet_b, &quit, bomb_b, adat_b);
                break;

            case SDL_QUIT:
                    quit = true;
                    break;



        }
    }

    SDL_RemoveTimer(id);
    felszabadit(s_r);
    free(s_v_r);
    felszabadit(s_b);
    free(s_v_b);

    kiir(renderer, str, "        ", false);
    return;
}

