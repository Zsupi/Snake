#ifndef SDLFGV_H
#define SDLFGV_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>


//
void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont, const char* tipus);
//
void sdl_felirat_ablak(int szeles, int magas, const char* tipus, SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont);
//
Uint32 idozit(Uint32 ms, void *param);

void felszabadit(lanc* eleje);
//
void sdl_close(SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont);
//
bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer);
//
void beker (char* s, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);
//
void felirat_fuggveny(char* str, SDL_Renderer *renderer, int x, TTF_Font *font, SDL_Color szin);
//
void kiir(SDL_Renderer *renderer, char* str1, char* str2, bool dics);
//
void pontok(int eredmeny, char* str);

///////////////////////////////////////////////////
typedef struct eredmeny{
    char nev [100+1];
    int score;
}eredmeny;

//
void beolvas(eredmeny tomb[]);
//
void shift(int index, eredmeny tomb[]);
//
void filebaki (char* nev, int score);


#endif
