#include "haut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Tekee syvyyshaun numeroarvon pohjalta.
 *
 * Tekee syvyyshaun kayttajan antaman numeroarvon pohjalta.
 * Kirjoittaa syvyyshaun polun kayttajan maarittelemaan tiedostoon.
 *
 * @param pNimi Kayttajan antama kirjoitettavan tiedoston nimi.
 * @param pAlku Osoitin puu tietueen alkuun, eli ensimmaiseen solmuun.
 * @param iArvo Arvo, jota etsitaan syvyyshaussa.
 * @return int Palauttaa arvon 0 tai 1, riippuen siita, loytyyko etsitty arvo.
 */
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

/**
 * @brief Tarkistaa, loytyyko etsitty arvo syvyyshaussa.
 *
 * Tarkistaa, loytyyko syvyyshaussa etsitty arvo.
 * Jos arvoa ei loydy, tulostaa tiedon siita.
 *
 * @param aNimiKirjoitettava Kayttajan antama kirjoitettavan tiedoston nimi.
 * @param pJuuriSolmu Osoitin puu tietueen alkuun, eli ensimmaiseen solmuun.
 * @param iArvo Syvyyhaussa haettava numeroarvo.
 * @return void
 */
void tarkistaLoytyykoSyvyyshaulla(char *aNimiKirjoitettava, PUU *pJuuriSolmu, int iArvo) {
    int iLoytyi = 0;
    iLoytyi = syvyyshaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);
    if (iLoytyi == 0) {
        printf("Arvoa %d ei löytynyt puusta.\n", iArvo);
    }
    return;
}

/**
 * @brief Tekee leveyshaun nimen pohjalta.
 *
 * Tekee leveyshaun kayttajan antaman nimen pohjalta.
 * Kirjoittaa leveyshaun polun kayttajan maarittelemaan tiedostoon.
 *
 * @param pNimi Kayttajan antama kirjoitettavan tiedoston nimi.
 * @param pAlku Osoitin puu tietueen alkuun, eli ensimmaiseen solmuun.
 * @param pHaku Osoitin haettavan nimen merkkijonoon.
 * @return void
 */
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

/**
 * @brief Varaa muistia jonolle.
 *
 * Varaa muistia jonon uudelle alkiolle leveyshakua varten.
 *
 * @param pSolmu Osoitin kasiteltavaan puun solmuun.
 * @return pUusi Osoitin uuteen jonon alkioon.
 */
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

/**
 * @brief Vapauttaa jonon varaaman muistin.
 *
 * Vapauttaa jonon alkioita varten varatun muistin.
 *
 * @param pAlku Osoitin jonon ensimmaiseen alkioon.
 * @return pAlku Palauttaa NULL, koska jono on tyhja.
 */
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

/**
 * @brief Binaarihaku perustuen numeroarvoon.
 *
 * Binaarihaku, joka tehdaan kayttajan antaman numeroarvon perusteella.
 *
 * @param pNimi Kirjoitettavan tiedoston nimi.
 * @param pJuuriSolmu Osoitin kasiteltavaan puun solmuun.
 * @param iArvo Haettava numeroarvo.
 * @return int Palauttaa joko 0 tai 1, riippuen siitä, loytyyko numeroarvo binaaripuusta.
 */
int binaarihaku(char *pNimi, PUU *pJuuriSolmu, int iArvo) {

    if (pJuuriSolmu == NULL) {
        return (0);
    }

    kirjoitaTiedostoon(pNimi, pJuuriSolmu);

    if (iArvo == pJuuriSolmu->iArvo) {
        printf("Hakemasi arvo '%d' löytyi!\n", iArvo);
        return (1);
    } else if (iArvo < pJuuriSolmu->iArvo) {
        return binaarihaku(pNimi, pJuuriSolmu->pVasen, iArvo);
    } else {
        return binaarihaku(pNimi, pJuuriSolmu->pOikea, iArvo);
    }
}
