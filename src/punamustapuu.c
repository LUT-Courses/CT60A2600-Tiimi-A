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

RBSOLMU *vapautaMuistiRB(RBSOLMU *pJuuriSolmu) {
    if (pJuuriSolmu != NULL) {
        vapautaMuistiRB(pJuuriSolmu->pVasen);
        vapautaMuistiRB(pJuuriSolmu->pOikea);
        free(pJuuriSolmu);
    }
    pJuuriSolmu = NULL;
    return (pJuuriSolmu);
}

RBSOLMU *lisaaRBSolmu(RBSOLMU *pJuurisolmu, RBSOLMU *pUusi) {
    int iVertailu = 0;

    // Jos puu on tyhjä, palautetaan uusi RBsolmu.
    if (pJuurisolmu == NULL) {
        return pUusi;
    }

    iVertailu = strcmp(pUusi->aNimi, pJuurisolmu->aNimi);

    // Solmujen lisääminen rekursiivisesti
    if (pUusi->iArvo < pJuurisolmu->iArvo) {
        pJuurisolmu->pVasen = lisaaRBSolmu(pJuurisolmu->pVasen, pUusi);
        pJuurisolmu->pVasen->pVanhempi = pJuurisolmu;
    } else if (pUusi->iArvo > pJuurisolmu->iArvo) {
        pJuurisolmu->pOikea = lisaaRBSolmu(pJuurisolmu->pOikea, pUusi);
        pJuurisolmu->pOikea->pVanhempi = pJuurisolmu;
        /** Katsotaan, ovatko arvot samat.
         * Laitetaan aakkosten perusteella vasemmalle tai oikealle. */
    } else if (pUusi->iArvo == pJuurisolmu->iArvo) {
        if (iVertailu < 0) {
            pJuurisolmu->pVasen = lisaaRBSolmu(pJuurisolmu->pVasen, pUusi);
            pJuurisolmu->pVasen->pVanhempi = pJuurisolmu;
        } else if (iVertailu > 0) {
            pJuurisolmu->pOikea = lisaaRBSolmu(pJuurisolmu->pOikea, pUusi);
            pJuurisolmu->pOikea->pVanhempi = pJuurisolmu;
        }
    }
    return (pJuurisolmu);
}

RBSOLMU *luoRBPuu(RBSOLMU *pJuurisolmu, char *pNimi) {
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
        pJuurisolmu = lisaaRBSolmu(pJuurisolmu, pUusi);
        korjaaLisays(&pJuurisolmu, pUusi);
    }

    fclose(Tiedosto);
    return (pJuurisolmu);
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

void korjaaLisays(RBSOLMU **pJuurisolmu, RBSOLMU *pUusi) {
    // Ilman p-alkua, koska pVanhempi->pVanhempi oli sekava
    RBSOLMU *vanhempi = NULL;
    RBSOLMU *seta = NULL;
    RBSOLMU *isoVanhempi = NULL;

    while ((pUusi != *pJuurisolmu) && (pUusi->pVanhempi->iVariBitti == 0)) {
        vanhempi = pUusi->pVanhempi;
        isoVanhempi = vanhempi->pVanhempi;

        if (vanhempi == isoVanhempi->pVasen) {
            seta = isoVanhempi->pOikea;
            if (seta != NULL && seta->iVariBitti == 0) {
                vanhempi->iVariBitti = 1;
                seta->iVariBitti = 1;
                isoVanhempi->iVariBitti = 0;
                pUusi = isoVanhempi;
            } else {
                if (pUusi == vanhempi->pOikea) {
                    pUusi = vanhempi;
                    kierraVasemmalle(pJuurisolmu, pUusi);
                    vanhempi = pUusi->pVanhempi;
                }
                vanhempi->iVariBitti = 1;
                isoVanhempi->iVariBitti = 0;
                kierraOikealle(pJuurisolmu, isoVanhempi);
            }

        } else {
            seta = isoVanhempi->pVasen;
            if (seta != NULL && seta->iVariBitti == 0) {
                vanhempi->iVariBitti = 1;
                seta->iVariBitti = 1;
                isoVanhempi->iVariBitti = 0;
                pUusi = isoVanhempi;
            } else {
                if (pUusi == vanhempi->pVasen) {
                    pUusi = vanhempi;
                    kierraOikealle(pJuurisolmu, pUusi);
                    vanhempi = pUusi->pVanhempi;
                }
                vanhempi->iVariBitti = 1;
                isoVanhempi->iVariBitti = 0;
                kierraVasemmalle(pJuurisolmu, isoVanhempi);
            }
        }
    }
    (*pJuurisolmu)->iVariBitti = 1;
}

// Koska binaaripuu.c versio ottaa parametrina PUU*, tarvitaan uusi kirjoitusaliohjelma.
void kirjoitaRBTiedostoon(char *pNimi, RBSOLMU *pJuurisolmu) {
    FILE *Tiedosto = NULL;

    if (pJuurisolmu == NULL) {
        return;
    }

    /* Tiedoston avaaminen. */
    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    /* Tiedostoon kirjoittaminen. */
    fprintf(Tiedosto, "%s,%d\n", pJuurisolmu->aNimi, pJuurisolmu->iArvo);

    /* Tiedoston sulkeminen. */
    fclose(Tiedosto);
    printf("Tiedosto '%s' kirjoitettu.\n", pNimi);
    return;
}

void kirjoitaRB(char *pNimi, RBSOLMU *pJuurisolmu) {
    /*if (pJuurisolmu == NULL) {
        printf("Puu on tyhjä, luo puurakenne ennen kirjoittamista.\n");
        return;
    }*/
    if (pJuurisolmu != NULL) {
        kirjoitaRBTiedostoon(pNimi, pJuurisolmu);
        kirjoitaRB(pNimi, pJuurisolmu->pVasen);
        kirjoitaRB(pNimi, pJuurisolmu->pOikea);
    }
    return;
}
