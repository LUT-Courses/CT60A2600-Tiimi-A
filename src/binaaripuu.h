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

PUU *varaaMuistiaPuulle(char *pSolmu, int iArvo);
PUU *vapautaMuistiPuu(PUU *pJuuriSolmu);
PUU *lisaaSolmu(PUU *pAlku, char *pSolmu, int iArvo);
PUU *luoPuu(char *pNimi, PUU *pJuuriSolmu);

int tasapainoitaPuu(PUU *pAlku);
PUU *oikeaPuoli(PUU *pAlku);
PUU *vasenPuoli(PUU *pAlku);
int puunPituus(PUU *pAlku);
int suurempiLukuVertailu(int iLuku1, int iLuku2);

PUU *poistaSolmu(char *pNimi, PUU *pJuuriSolmu);
int onkoLuku(char *pNimi);
int nimenArvo(char *pNimi, PUU *pJuuriSolmu);
PUU *etsiPienin(PUU *pUusiSolmu);
PUU *paivitaPuu(PUU *pJuurisolmu);

void kirjoitaBinaaripuu(char *pNimi, PUU *pAlku);
void kirjoitaTiedostoon(char *pKirjoitaTiedostoNimi, PUU *pAlku);

#endif
