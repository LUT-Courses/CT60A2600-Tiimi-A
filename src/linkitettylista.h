// 8.3.2026, Sofia Toropainen, Aino Pöyhönen, Noora Vepsäläinen, linkitettylista.h, muokattu tiedostoa myöhemmin.
#ifndef LINKITETTYLISTA_H
#define LINKITETTYLISTA_H
#include "yleiset.h"

typedef struct tiedot {
    char aNimi[LEN];
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
int laskeListanPituus(TIEDOT *pAlku);
TIEDOT *halkaise(TIEDOT *pAlku);
TIEDOT *lomitus(TIEDOT *p1, TIEDOT *p2);
TIEDOT *lomitusLajittelu(TIEDOT *pAlku);
TIEDOT *lisaysLajittelu(TIEDOT *pAlku);
int onkoLukuVaiNimi(char *Tieto);
TIEDOT *poistaListastaAlkio(TIEDOT *pAlku, int iLuvuVaiNimi, char *pTieto);

#endif
