#ifndef BINAARIPUU_H
#define BINAARIPUU_H
#include "yleiset.h"

typedef struct puu {
    char aNimi[LEN];
    int iArvo;
    int iPituus;
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
int tasapainoitaPuu(PUU *pAlku);
PUU *oikeaPuoli(PUU *pAlku);
PUU *vasenPuoli(PUU *pAlku);
int puunPituus(PUU *pAlku);
int suurempiLukuVertailu(int iLuku1, int iLuku2);
PUU *poistaSolmu(char *pNimi, int iArvo, PUU *pJuuriSolmu);
int binaariHaku(char *pNimi, PUU *pJuuriSolmu, int iArvo);

#endif
