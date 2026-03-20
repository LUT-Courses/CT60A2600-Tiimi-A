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

typedef struct RBSolmu {
    char aNimi[LEN];
    int iArvo;
    int iVariBitti;
    struct RBSolmu *pOikea;
    struct RBSolmu *pVasen;
    struct RBSolmu *pVanhempi;
} RBSOLMU;

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
PUU *paivitaPuu(PUU *pJuurisolmu);

void kirjoitaBinaaripuu(char *pNimi, PUU *pAlku);
void kirjoitaTiedostoon(char *pKirjoitaTiedostoNimi, PUU *pAlku);

/**
 * Punamustapuu, ehkä oma header olisi kätevämpi,
 * kun omat aliohjelmat oman structin takia. */
RBSOLMU *varaaMuistiaRB(char *pNimi, int iArvo);
RBSOLMU *vapautaMuistiRB(RBSOLMU *pJuuriSolmu);
RBSOLMU *lisaaRBSolmu(RBSOLMU *pJuurisolmu, RBSOLMU *pUusi);
RBSOLMU *luoRBPuu(RBSOLMU *pJuurisolmu, char *pNimi);
void kierraVasemmalle(RBSOLMU **pJuurisolmu, RBSOLMU *pSolmu);
void kierraOikealle(RBSOLMU **pJuurisolmu, RBSOLMU *pSolmu);
void korjaaLisays(RBSOLMU **pJuurisolmu, RBSOLMU *pUusi);
void kirjoitaRBTiedostoon(char *pNimi, RBSOLMU *pJuurisolmu);
void kirjoitaRB(char *pNimi, RBSOLMU *pJuurisolmu);

#endif
