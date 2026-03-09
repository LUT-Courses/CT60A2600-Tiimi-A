#ifndef MODULE_H
#define MODULE_H

#define LEN 50

typedef struct tiedot
{
    char aSukunimi[LEN];
    int iYhteensa;
    struct tiedot *pSeuraava;
    struct tiedot *pEdellinen;
} TIEDOT;

typedef struct puu
{
    char aNimi[LEN];
    int iArvo;
    struct tiedot *pSeuraava;
    struct tiedot *pEdellinen;
} PUU;

int valikko();
int listaValikko();
int binaaripuuValikko();
char *kysyNimi(char *pPrompti, char *pNimi);

TIEDOT* lue(char *pNimi, TIEDOT *pAlku);
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara);
TIEDOT *vapautaMuisti(TIEDOT *pAlku);
void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
void kirjoitaTiedostoLopustaAlkuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);

void luoPuu();
void tulostaPuu();
void syvyyshaku(char *pKirjoitaTiedostoNimi);
void leveyshaku(char *pKirjoitaTiedostoNimi);

#endif