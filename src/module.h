#ifndef MODULE_H
#define MODULE_H

#define LEN 50

typedef struct tiedot {
    char aSukunimi[LEN];
    int iYhteensa;
    struct tiedot *pSeuraava;
    struct tiedot *pEdellinen;
} TIEDOT;

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

int valikko();
int listaValikko();
int binaaripuuValikko();
char *kysyNimi(char *pPrompti, char *pNimi);

TIEDOT *lue(char *pNimi, TIEDOT *pAlku);
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara);
TIEDOT *vapautaMuisti(TIEDOT *pAlku);
void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);
void kirjoitaTiedostoLopustaAlkuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku);

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
#endif
