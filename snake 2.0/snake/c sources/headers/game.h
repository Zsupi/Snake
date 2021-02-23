#ifndef GAME_H
#define GAME_H

typedef struct Bomba{
    int db;
    Pont hely[3];
}Bomba;

/*typedef struct Fal{
    Pont kezd;
    Pont veg;
}Fal;*/

void single(SDL_Window *window, SDL_Renderer *renderer, TTF_Font *font);


void multiplayer (SDL_Window *window, SDL_Renderer *renderer);
#endif
