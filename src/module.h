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

/* Ei tällä hetkellä käytössä. Olisi kyllä tehokkaampi vaihtoehto. */
/* typedef struct lista
{
    TIEDOT *pAlku;
    TIEDOT *pLoppu;
} LISTA; */

int valikko();
TIEDOT* lue(char *pNimi, TIEDOT *pAlku);
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara);
TIEDOT *vapautaMuisti(TIEDOT *pAlku);
void kysyKirjoitettavaTiedosto(char *pKirjoitusTiedostoNimi);
void kysyLuettavaTiedosto(char *pLueTiedostoNimi);
TIEDOT kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
void kirjoitaTiedostoLopustaAlkuun();

#endif