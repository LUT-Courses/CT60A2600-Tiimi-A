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

int valikko(void);
char *kysyNimi(char *pPrompti, char *pNimi);
TIEDOT* lue(char *pNimi, TIEDOT *pAlku);
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara);
TIEDOT *vapautaMuisti(TIEDOT *pAlku);
void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
void kirjoitaTiedostoLopustaAlkuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);

#endif
