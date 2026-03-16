#ifndef BINAARIPUU_H
#define BINAARIPUU_H
#include "yleiset.h"

typedef struct puu {
    char aNimi[LEN];
    int iArvo;
    struct puu *pOikea;
    struct puu *pVasen;
} PUU;

typedef struct jono {
    PUU *pSolmu;
    struct jono *pSeuraava;
} JONO;

PUU *varaaMuistiaPuulle(char *pSolmu, int iValiMatka);
PUU *vapautaMuistiPuu(PUU *pJuuriSolmu);
PUU *lisaaSolmu(PUU *pAlku, char *pSolmu, int iValiMatka);
PUU *luoPuu(char *pNimi, PUU *pJuuriSolmu);
void kirjoitaBinaaripuu(char *pNimi, PUU *pAlku);
int kysyArvo(char *pPrompti, int iArvo);
int syvyyshaku(char *pKirjoitaTiedostoNimi, PUU *pJuuriSolmu, int iArvo);
void leveyshaku(char *pKirjoitaTiedostoNimi, PUU *pAlku, char *pHaku);
JONO *varaaMuistiaJonolle(PUU *pSolmu);
JONO *vapautaMuistiJono(JONO *pAlku);
void kirjoitaTiedostoon(char *pKirjoitaTiedostoNimi, PUU *pAlku);
void tarkistaLoytyykoSyvyyshaulla(char *aNimiKirjoitettava, PUU *pJuuriSolmu, int iArvo);

#endif
