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
#include "headers\debugmalloc.h"
#define FONT "Candara.ttf"

typedef enum Allapot{
    felso,
    kozep,
    also
}Allapot;

void menurajz(SDL_Renderer *renderer, TTF_Font *font, SDL_Color si, SDL_Color mu, SDL_Color di){
        boxRGBA(renderer, 0, 0, 1500, 1000, 0, 0, 0, 255);




        int x = 100;
        felirat_fuggveny("Egyjatekos", renderer, x, font, si);

        x += 150;
        felirat_fuggveny("Tobbjatekos", renderer, x, font, mu);

        x += 150;
        felirat_fuggveny("Dicsoseglista", renderer, x, font, di);


        return;
}

void menu(SDL_Renderer* renderer, SDL_Window *window){

    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Candara.ttf", 48);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    SDL_Color feher = {255, 255, 255};
    SDL_Color zold = {60, 200, 200};

    bool quit = false;

    Allapot al = felso;

    //menurajz(renderer, font, zold, feher, );


    while(!quit){
        SDL_Event menu;
        SDL_WaitEvent(&menu);

        switch(al){
            case(felso):
                menurajz(renderer, font, zold, feher, feher);
                switch(menu.type){
                    case(SDL_KEYDOWN):
                        switch(menu.key.keysym.sym){
                            case SDLK_UP:
                                al = also;
                                break;
                            case SDLK_DOWN:
                                al = kozep;
                                break;
                            case SDLK_SPACE:
                                single(window, renderer, font);
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                        }

                }
            break;

            case(kozep):
                menurajz(renderer, font, feher, zold, feher);
                switch(menu.type){
                    case(SDL_KEYDOWN):
                        switch(menu.key.keysym.sym){
                            case SDLK_UP:
                                al = felso;
                                break;
                            case SDLK_DOWN:
                                al = also;
                                break;
                            case SDLK_SPACE:
                                multiplayer(window, renderer);
                                al = felso;
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;
                        }

                }
            break;

            case(also):
                menurajz(renderer, font, feher, feher, zold);
                switch(menu.type){
                    case(SDL_KEYDOWN):
                        switch(menu.key.keysym.sym){
                            case SDLK_UP:
                                al = kozep;
                                break;
                            case SDLK_DOWN:
                                al = felso;
                                break;
                            case SDLK_SPACE:
                                kiir(renderer, "no", "no", true);
                                al = felso;
                                break;
                            case SDLK_ESCAPE:
                                quit = true;
                                break;

                        }
                }
            break;


        }

        /*switch(menu.type){

        case SDL_KEYDOWN:
            switch (menu.key.keysym.sym){

                case SDLK_1:
                    single(window, renderer, font);
                    menurajz(renderer, font);
                    break;

                case SDLK_2:
                    multiplayer(window, renderer);
                    menurajz(renderer, font);
                    break;

                case SDLK_3:
                    kiir(renderer, "no", "no", true);
                    menurajz(renderer, font);
                    break;
                case SDLK_ESCAPE:
                    quit = true;
                    break;
            }
            break;

            case SDL_QUIT:
                quit = true;
                break;
        }*/

    }


    TTF_CloseFont(font);
    return;
}


int main(int argc, char *argv[]) {
    SDL_Renderer *renderer;
    SDL_Window *window;
    TTF_Font *font;

    sdl_init("snake", 1500, 1000, &window, &renderer, &font, FONT);

    menu(renderer, window);

    SDL_Quit();

    return 0;
}
