#ifndef HAUT_H
#define HAUT_H
#include "binaaripuu.h"

typedef struct jono {
    PUU *pSolmu;
    struct jono *pSeuraava;
} JONO;

int syvyyshaku(char *pKirjoitaTiedostoNimi, PUU *pJuuriSolmu, int iArvo);
void tarkistaLoytyykoSyvyyshaulla(char *aNimiKirjoitettava, PUU *pJuuriSolmu, int iArvo);
void leveyshaku(char *pKirjoitaTiedostoNimi, PUU *pAlku, char *pHaku);
JONO *varaaMuistiaJonolle(PUU *pSolmu);
JONO *vapautaMuistiJono(JONO *pAlku);
int binaarihaku(char *pNimi, PUU *pJuuriSolmu, int iArvo);

#endif