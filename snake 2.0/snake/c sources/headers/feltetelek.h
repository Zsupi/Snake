#ifndef FELTETELEK_H
#define FELTETELEK_H

typedef struct Pont{
    int x;
    int y;
}Pont;

typedef struct lanc{
    Pont p;
    struct lanc* kov;
    struct lanc* el;
}lanc;

typedef struct Adat{
    lanc* eleje;
    lanc* vege;
}Adat;

bool benne_teljes(lanc* eleje, Pont n);

bool benne(lanc* eleje, Pont n);

bool palyarolki (lanc* eleje);

Pont etelfelt(Adat adat, Pont etel, int* score, lanc* masik);

bool feltetel_single (bool quit, lanc* s);

bool feltetel_multi(lanc* s_r, lanc* s_b, char* str);

Pont general(lanc* eleje, lanc* masik);

#endif
