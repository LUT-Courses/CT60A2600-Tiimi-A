#include "haut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int syvyyshaku(char *pNimi, PUU *pAlku, int iArvo) {
    // Syvyyshaku arvon mukaan, kirjoitetaan käydyt solmut tiedostoon.
    int iLoytyi = 0;

    if (pAlku == NULL) {
        return 0;
    }

    if (pAlku != NULL) {
        kirjoitaTiedostoon(pNimi, pAlku);

        if (pAlku->iArvo == iArvo) {
            iLoytyi = 1;
            printf("Arvo %d löytyi.\n", iArvo);
        } else {
            if (iLoytyi == 0) {
                iLoytyi = syvyyshaku(pNimi, pAlku->pVasen, iArvo);
            }
            if (iLoytyi == 0) {
                iLoytyi = syvyyshaku(pNimi, pAlku->pOikea, iArvo);
            }
        }
    }
    return (iLoytyi);
}

void tarkistaLoytyykoSyvyyshaulla(char *aNimiKirjoitettava, PUU *pJuuriSolmu, int iArvo) {
    int iLoytyi = 0;
    iLoytyi = syvyyshaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);
    if (iLoytyi == 0) {
        printf("Arvoa %d ei löytynyt puusta.\n", iArvo);
    }
}

void leveyshaku(char *pNimi, PUU *pJuuriSolmu, char *pHaku) {
    // Leveyshaku nimen mukaan, kirjoitetaan käydyt solmut tiedostoon.
    JONO *pAlku = varaaMuistiaJonolle(pJuuriSolmu);
    JONO *pLoppu = pAlku;
    JONO *pEdellinen = NULL;
    int iVertailu = 0;
    int iLoytyi = 0;

    if (pJuuriSolmu == NULL) {
        printf("Puu on tyhjä, luo puurakenne ennen leveyshakua.\n");
        return;
    }

    while (pAlku != NULL) {
        PUU *ptr = pAlku->pSolmu;
        kirjoitaTiedostoon(pNimi, ptr);

        iVertailu = strcmp(ptr->aNimi, pHaku);

        if (iVertailu == 0) {
            printf("Nimi '%s' löytyi puusta.\n", ptr->aNimi);
            iLoytyi = 1;
            break;
        }

        if (ptr->pVasen != NULL) {
            pLoppu->pSeuraava = varaaMuistiaJonolle(ptr->pVasen);
            pLoppu = pLoppu->pSeuraava;
        }

        if (ptr->pOikea != NULL) {
            pLoppu->pSeuraava = varaaMuistiaJonolle(ptr->pOikea);
            pLoppu = pLoppu->pSeuraava;
        }

        pEdellinen = pAlku;
        pAlku = pAlku->pSeuraava;
        free(pEdellinen);
    }

    if (iLoytyi == 0) {
        printf("Hakemaasi nimeä ei löytynyt puusta.\n");
    }
    pAlku = vapautaMuistiJono(pAlku);
    return;
}

JONO *varaaMuistiaJonolle(PUU *pSolmu) {
    JONO *pUusi = NULL;

    // Muistin varaaminen jonolle.
    if ((pUusi = (JONO *)malloc(sizeof(JONO))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    pUusi->pSolmu = pSolmu;
    pUusi->pSeuraava = NULL;

    return (pUusi);
}

JONO *vapautaMuistiJono(JONO *pAlku) {
    // Jonon muistin vapauttaminen.
    JONO *ptr = pAlku;
    JONO *pSeuraava = NULL;

    while (ptr != NULL) {
        pSeuraava = ptr->pSeuraava;
        free(ptr);
        ptr = pSeuraava;
    }
    pAlku = NULL;
    return (pAlku);
}

int binaariHaku(char *pNimi, PUU *pJuuriSolmu, int iArvo) {

    if (pJuuriSolmu == NULL) {
        printf("Puu on tyhjä, luo puurakenne ennen binäärihakua.\n");
        return (0);
    }

    kirjoitaTiedostoon(pNimi, pJuuriSolmu);

    if (iArvo == pJuuriSolmu->iArvo) {
        printf("Hakemasi arvo '%d' löytyi!\n", iArvo);
        return (1);
    } else if (iArvo < pJuuriSolmu->iArvo) {
        return binaariHaku(pNimi, pJuuriSolmu->pVasen, iArvo);
    } else {
        return binaariHaku(pNimi, pJuuriSolmu->pOikea, iArvo);
    }
}