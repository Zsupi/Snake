#ifndef MOZGAS_H
#define MOZGAS_H

#include "feltetelek.h"
#include "game.h"

typedef enum IRANY{
    left,
    right,
    up,
    down
}IRANY;

void festes (lanc *eleje, bool food, Pont etel, SDL_Renderer* renderer, int r, int g, int b, Bomba bomb, bool multi);

void mozog(lanc* eleje, lanc* vege, IRANY irany);

lanc *hozza (lanc* eleje, lanc* vege, Pont n);

void inic (Adat adat, Pont p);

void vezerles(SDL_Event event, IRANY *irany, bool *leptet, bool* quit, Bomba bomb, Adat adat);

void vezerles_multi(SDL_Event event, IRANY *irany, bool *leptet, bool* quit, Bomba bomb, Adat adat);

#endif
