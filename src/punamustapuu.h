#ifndef PUNAMUSTAPUU_H
#define PUNAMUSTAPUU_H
#include "yleiset.h"

typedef struct RBSolmu {
    char aNimi[LEN];
    int iArvo;
    int iVariBitti;
    struct RBSolmu *pOikea;
    struct RBSolmu *pVasen;
    struct RBSolmu *pVanhempi;
} RBSOLMU;


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