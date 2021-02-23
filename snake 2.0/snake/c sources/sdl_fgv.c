#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>

#include "headers\mozgas.h"

#include "headers\sdl_fgv.h"
#include "headers\debugmalloc.h"


void sdl_init(char const *felirat, int szeles, int magas, SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont, const char* tipus) {
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        SDL_Log("Nem indithato az SDL: %s", SDL_GetError());
        exit(1);
    }
    SDL_Window *window = SDL_CreateWindow(felirat, SDL_WINDOWPOS_CENTERED_MASK, SDL_WINDOWPOS_CENTERED_MASK, szeles, magas, SDL_WINDOW_FULLSCREEN_DESKTOP);
    if (window == NULL) {
        SDL_Log("Nem hozhato letre az ablak: %s", SDL_GetError());
        exit(1);
    }
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    if (renderer == NULL) {
        SDL_Log("Nem hozhato letre a megjelenito: %s", SDL_GetError());
        exit(1);
    }
    SDL_Surface* icon = IMG_Load("snake.png");
    SDL_SetWindowIcon(window, icon);


    TTF_Init();
    TTF_Font *font = TTF_OpenFont(tipus, 32);
    if (font == NULL) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    SDL_RenderClear(renderer);

    *pwindow = window;
    *prenderer = renderer;
    *pfont = font;
}

Uint32 idozit(Uint32 ms, void *param) {
    SDL_Event ev;
    ev.type = SDL_USEREVENT;
    SDL_PushEvent(&ev);
    return ms;
}


void felszabadit(lanc* eleje){
    lanc* iter = eleje;
    while (iter != NULL) {
        lanc *temp = iter->kov;
        free(iter);
        iter = temp;
    }
}


void sdl_close(SDL_Window **pwindow, SDL_Renderer **prenderer, TTF_Font **pfont) {
    SDL_DestroyRenderer(*prenderer);
    *prenderer = NULL;

    SDL_DestroyWindow(*pwindow);
    *pwindow = NULL;

    TTF_CloseFont(*pfont);
    *pfont = NULL;

}



bool input_text(char *dest, size_t hossz, SDL_Rect teglalap, SDL_Color hatter, SDL_Color szoveg, TTF_Font *font, SDL_Renderer *renderer) {

    char composition[SDL_TEXTEDITINGEVENT_TEXT_SIZE];
    composition[0] = '\0';

    char textandcomposition[hossz + SDL_TEXTEDITINGEVENT_TEXT_SIZE + 1];

    int maxw = teglalap.w - 2;
    int maxh = teglalap.h - 2;

    dest[0] = '\0';

    bool enter = false;
    bool kilep = false;

    SDL_StartTextInput();
    while (!kilep && !enter) {

        boxRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, hatter.r, hatter.g, hatter.b, 255);
        rectangleRGBA(renderer, teglalap.x, teglalap.y, teglalap.x + teglalap.w - 1, teglalap.y + teglalap.h - 1, szoveg.r, szoveg.g, szoveg.b, 255);

        int w;
        strcpy(textandcomposition, dest);
        strcat(textandcomposition, composition);
        if (textandcomposition[0] != '\0') {
            SDL_Surface *felirat = TTF_RenderUTF8_Blended(font, textandcomposition, szoveg);
            SDL_Texture *felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
            SDL_Rect cel = { teglalap.x, teglalap.y, felirat->w < maxw ? felirat->w : maxw, felirat->h < maxh ? felirat->h : maxh };
            SDL_RenderCopy(renderer, felirat_t, NULL, &cel);
            SDL_FreeSurface(felirat);
            SDL_DestroyTexture(felirat_t);
            w = cel.w;
        } else {
            w = 0;
        }

        if (w < maxw) {
            vlineRGBA(renderer, teglalap.x + w + 2, teglalap.y + 2, teglalap.y + teglalap.h - 3, szoveg.r, szoveg.g, szoveg.b, 192);
        }

        SDL_RenderPresent(renderer);

        SDL_Event event;
        SDL_WaitEvent(&event);
        switch (event.type) {

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_BACKSPACE) {
                    int textlen = strlen(dest);
                    do {
                        if (textlen == 0) {
                            break;
                        }
                        if ((dest[textlen-1] & 0x80) == 0x00)   {

                            dest[textlen-1] = 0x00;
                            break;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0x80) {

                            dest[textlen-1] = 0x00;
                            textlen--;
                        }
                        if ((dest[textlen-1] & 0xC0) == 0xC0) {

                            dest[textlen-1] = 0x00;
                            break;
                        }
                    } while(true);
                }
                if (event.key.keysym.sym == SDLK_RETURN) {
                    enter = true;
                }
                break;

            case SDL_TEXTINPUT:
                if (strlen(dest) + strlen(event.text.text) < hossz) {
                    strcat(dest, event.text.text);
                }

                composition[0] = '\0';
                break;

            case SDL_TEXTEDITING:
                strcpy(composition, event.edit.text);
                break;

            case SDL_QUIT:
                SDL_PushEvent(&event);
                kilep = true;
                break;
        }
    }

    SDL_StopTextInput();
    return enter;
}
void beker (char* s, SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font){



    //sdl_felirat_ablak(440, 440, FONT, &window, &renderer, &font);

    SDL_Color feher = {255, 255, 255}, fekete = { 0, 0, 0 };

    char szoveg[100];

    SDL_Surface *screen = SDL_GetWindowSurface(window);
    SDL_Surface *background = SDL_CreateRGBSurface(0, 1500, 1000, 32, 0, 0, 0, 255);

    boxRGBA(renderer, 0, 0, 1500, 1000, 0, 0, 0, 255);
    SDL_BlitSurface(screen, NULL, background, NULL);
    SDL_RenderPresent(renderer);


    SDL_Rect r = { 550, 500, 400, 40 };
    input_text(szoveg, 100, r, fekete, feher, font, renderer);

    strcpy(s, szoveg);

    SDL_FreeSurface(background);

}

void felirat_fuggveny(char* str, SDL_Renderer *renderer, int x, TTF_Font *font, SDL_Color szin){

    SDL_Surface *felirat;
    SDL_Texture *felirat_t;
    SDL_Rect hova = { 0, 0, 0, 0 };



    felirat = TTF_RenderUTF8_Blended(font, str, szin);
    felirat_t = SDL_CreateTextureFromSurface(renderer, felirat);
    hova.x = (1500 - felirat->w) / 2;
    hova.y = (1000 - felirat->h) / 4+x;
    hova.w = felirat->w;
    hova.h = felirat->h;
    SDL_RenderCopy(renderer, felirat_t, NULL, &hova);
    SDL_FreeSurface(felirat);
    SDL_DestroyTexture(felirat_t);

    SDL_RenderPresent(renderer);
}

void kiir(SDL_Renderer *renderer, char* str1, char* str2, bool dics){
    TTF_Init();
    TTF_Font *font = TTF_OpenFont("Candara.ttf", 48);
    if (!font) {
        SDL_Log("Nem sikerult megnyitni a fontot! %s\n", TTF_GetError());
        exit(1);
    }

    boxRGBA(renderer, 0, 0, 1500, 1000, 0, 0, 0, 255);

    SDL_Color feher = {255, 255, 255};

    if(!dics){
        int x = 200;
        felirat_fuggveny(str1, renderer, x, font, feher);

        x += 100;
        felirat_fuggveny(str2, renderer, x, font, feher);
    }

    else{
        eredmeny tomb[10];
        beolvas(tomb);
        int x =0;
        for(int i =0; i<10; i++){
            pontok(tomb[i].score, tomb[i].nev);
            printf("%s", tomb[i].nev);
            x+=60;
            felirat_fuggveny(tomb[i].nev, renderer, x, font, feher);
        }

    }

    SDL_Event event;
    while (SDL_WaitEvent(&event) && event.type != SDL_QUIT && event.key.keysym.sym != SDLK_BACKSPACE) {
    }

    TTF_CloseFont(font);

}

void pontok(int eredmeny, char* str){
    char tmp[10+1];


    sprintf(tmp, " %d", eredmeny);
    printf("%s", tmp);
    strcat(str, tmp);

    printf("%s", str);

}

///////////////////////////////////////////////////

void beolvas(eredmeny tomb[]){
    eredmeny tmp;

    FILE *fp;
    fp = fopen("dicsoseg.txt", "rt");

    if(fp == NULL){
        perror("a dicsoseg.txt-t nem sikerult megnyitni");
        return;

    }

    for(int i = 0; i<10; i++){
        fscanf(fp, "%d %[^\n]", &tmp.score, tmp.nev);
        strcpy(tomb[i].nev, tmp.nev);
        tomb[i].score = tmp.score;
    }

    fclose(fp);


}

void shift(int index, eredmeny tomb[]){
    for(int i = index; i<9; i++){
        tomb[index+1] = tomb[index];
    }

}

void filebaki (char* nev, int score){
    eredmeny tomb[10];
    beolvas(tomb);

    for(int i = 0; i<10; i++){
        if(tomb[i].score < score){
            shift(i, tomb);
            sprintf(tomb[i].nev, "%s", nev);
            tomb[i].score = score;
            break;
        }
    }

    FILE *fp;
    fp = fopen("dicsoseg.txt", "wt");

    if(fp == NULL){
        perror("a dicsoseg.txt-t nem sikerult megnyitni");
        return;

    }
    for(int i =0; i<10; i++){
        fprintf(fp, "%d %s\n", tomb[i].score, tomb[i].nev);
        printf("\n %s \t%d", tomb[i].nev, tomb[i].score);
    }

    fclose(fp);
}
