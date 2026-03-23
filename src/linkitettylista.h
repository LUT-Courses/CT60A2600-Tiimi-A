#ifndef LINKITETTYLISTA_H
#define LINKITETTYLISTA_H
#include "yleiset.h"

typedef struct tiedot {
    char aSukunimi[LEN];
    int iYhteensa;
    struct tiedot *pSeuraava;
    struct tiedot *pEdellinen;
} TIEDOT;

TIEDOT *lue(char *pNimi, TIEDOT *pAlku);
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara);
TIEDOT *vapautaMuisti(TIEDOT *pAlku);
void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
void kirjoitaTiedostoLopustaAlkuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
TIEDOT *lisaaListaan(TIEDOT *pAlku, int iIndeksi, char *pNimi, int iArvo);
TIEDOT *poistaListastaLkmPeruusteella(TIEDOT *pAlku, int iLKM);
int useammallaAlkiollaSamaLKM(TIEDOT *pAlku, int iLKM);
TIEDOT *poistaListastaNimenPerusteella(TIEDOT *pAlku, char *pNimi);

#endif
