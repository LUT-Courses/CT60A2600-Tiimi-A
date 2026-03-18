#include "binaaripuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/** L10 / Punamustapuu
 * Vaatii oman structin takia omat aliohjelmat, jotka ovat
 * binaaripuu.c tiedoston aliohjelmia muokattuina.
 */

RBSOLMU *varaaMuistiaRB(char *pNimi, int iArvo) {
    RBSOLMU *pUusi = NULL;

    if ((pUusi = (RBSOLMU *)malloc(sizeof(RBSOLMU))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    pUusi->iVariBitti = 0; // uudet aina punaisia
    strcpy(pUusi->aNimi, pNimi);
    pUusi->iArvo = iArvo;
    pUusi->pVasen = NULL;
    pUusi->pOikea = NULL;
    pUusi->pVanhempi = NULL;
    return (pUusi);
}

RBSOLMU *lisaaRBSolmu(RBSOLMU *pAlku, RBSOLMU *pUusi) {
    int iVertailu = 0;

    // Jos puu on tyhjä, palautetaan uusi RBsolmu.
    if (pAlku == NULL) {
        return pUusi;
    }

    iVertailu = strcmp(pUusi->aNimi, pAlku->aNimi);

    // Solmujen lisääminen rekursiivisesti
    if (pUusi->iArvo < pAlku->iArvo) {
        pAlku->pVasen = lisaaRBSolmu(pAlku->pVasen, pUusi);
        pAlku->pVasen->pVanhempi = pAlku;
    } else if (pUusi->iArvo > pAlku->iArvo) {
        pAlku->pOikea = lisaaRBSolmu(pAlku->pOikea, pUusi);
        pAlku->pOikea->pVanhempi = pAlku;
        /** Katsotaan, ovatko arvot samat.
         * Laitetaan aakkosten perusteella vasemmalle tai oikealle. */
    } else if (pUusi->iArvo == pAlku->iArvo) {
        if (iVertailu < 0) {
            pAlku->pVasen = lisaaRBSolmu(pAlku->pVasen, pUusi);
            pAlku->pVasen->pVanhempi = pAlku;
        } else if (iVertailu > 0) {
            pAlku->pOikea = lisaaRBSolmu(pAlku->pOikea, pUusi);
            pAlku->pOikea->pVanhempi = pAlku;
        }
    }
    return (pAlku);
}

RBSOLMU *luoRBPuu(RBSOLMU *pJuuriSolmu, char *pNimi) {
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    int iOtsikko = 0;
    char *p1 = NULL, *p2 = NULL;
    int iArvo = 0;

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    while ((fgets(aRivi, LEN, Tiedosto)) != NULL) {
        aRivi[strlen(aRivi) - 1] = '\0';
        if (iOtsikko == 0) {
            iOtsikko++;
            continue;
        }

        if ((p1 = strtok(aRivi, ";")) == NULL) {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        if ((p2 = strtok(NULL, ";")) == NULL) {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        iArvo = atoi(p2);

        RBSOLMU *pUusi = varaaMuistiaRB(p1, iArvo);
        pJuuriSolmu = lisaaRBSolmu(pJuuriSolmu, pUusi);
        // korjaaLisays(&pJuuriSolmu, pUusi);
        pJuuriSolmu->iVariBitti = 1; // juuri aina musta
    }

    fclose(Tiedosto);
    return (pJuuriSolmu);
}

void kierraVasemmalle(RBSOLMU **pJuurisolmu, RBSOLMU *pSolmu) {
    RBSOLMU *pOikeaLapsi = pSolmu->pOikea;
    pSolmu->pOikea = pOikeaLapsi->pVasen;

    if (pSolmu->pOikea != NULL)
        pSolmu->pOikea->pVanhempi = pSolmu;

    // Solmun oikea lapsi nousee ylös puussa
    pOikeaLapsi->pVanhempi = pSolmu->pVanhempi;

    if (pSolmu->pVanhempi == NULL)
        *pJuurisolmu = pOikeaLapsi;
    else if (pSolmu == pSolmu->pVanhempi->pVasen)
        pSolmu->pVanhempi->pVasen = pOikeaLapsi;
    else
        pSolmu->pVanhempi->pOikea = pOikeaLapsi;

    pOikeaLapsi->pVasen = pSolmu;
    pSolmu->pVanhempi = pOikeaLapsi;
}

void kierraOikealle(RBSOLMU **pJuurisolmu, RBSOLMU *pSolmu) {
    RBSOLMU *pVasenLapsi = pSolmu->pVasen;
    pSolmu->pVasen = pVasenLapsi->pOikea;

    if (pSolmu->pVasen != NULL)
        pSolmu->pVasen->pVanhempi = pSolmu;

    pVasenLapsi->pVanhempi = pSolmu->pVanhempi;

    if (pSolmu->pVanhempi == NULL)
        *pJuurisolmu = pVasenLapsi;
    else if (pSolmu == pSolmu->pVanhempi->pVasen)
        pSolmu->pVanhempi->pVasen = pVasenLapsi;
    else
        pSolmu->pVanhempi->pOikea = pVasenLapsi;

    pVasenLapsi->pOikea = pSolmu;
    pSolmu->pVanhempi = pVasenLapsi;
}

void korjaaLisays(RBSOLMU **pJuurisolmu, RBSOLMU *pUusi) {}
