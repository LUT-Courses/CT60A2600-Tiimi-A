#include "binaaripuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Tasapainoitettu binääripuu AVL:

/**
 * @brief Muistin varaaminen puu structin alkioille
 * 
 * @param pSolmu Solmu, jolle muistia varataan
 * @param iArvo Arvo, jolle muistia varataan
 * @return PUU* 
 */
PUU *varaaMuistiaPuulle(char *pSolmu, int iArvo) {
    PUU *pUusi = NULL;

    // Muistin varaaminen
    if ((pUusi = (PUU *)malloc(sizeof(PUU))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    strcpy(pUusi->aNimi, pSolmu);
    pUusi->iArvo = iArvo;
    pUusi->iPituus = 1;
    pUusi->pVasen = NULL;
    pUusi->pOikea = NULL;
    return (pUusi);
}

/**
 * @brief Muistin vapauttaminen puu structin alkiosta
 * Juurisolmun ja kaikkien sen lapsie solmujen muisti vapautetaan.
 * @param pJuuriSolmu Puun juurisolmu
 * @return PUU* 
 */
PUU *vapautaMuistiPuu(PUU *pJuuriSolmu) {
    // Muistin vapauttaminen
    if (pJuuriSolmu != NULL) {
        vapautaMuistiPuu(pJuuriSolmu->pVasen);
        vapautaMuistiPuu(pJuuriSolmu->pOikea);
        free(pJuuriSolmu);
    }
    pJuuriSolmu = NULL;
    return (pJuuriSolmu);
}

/**
 * @brief Lisaa solmun puuhun.
 * Tasapainottaa puun.
 * @param pAlku
 * @param pSolmu Lisattava solmu.
 * @param iArvo Solmun arvo.
 * @return PUU*
 */
PUU *lisaaSolmu(PUU *pAlku, char *pSolmu, int iArvo) {
    int iVertailu = 0;

    // Varataan muistia, jos muisti tyhjä.
    if (pAlku == NULL) {
        return varaaMuistiaPuulle(pSolmu, iArvo);
    }

    iVertailu = strcmp(pSolmu, pAlku->aNimi);

    // Solmujen lisääminen.
    if (iArvo < pAlku->iArvo) {
        pAlku->pVasen = lisaaSolmu(pAlku->pVasen, pSolmu, iArvo);
    } else if (iArvo > pAlku->iArvo) {
        pAlku->pOikea = lisaaSolmu(pAlku->pOikea, pSolmu, iArvo);

    // Testataan, ovatko arvot samat.
    } else if (iArvo == pAlku->iArvo) {
        if (iVertailu < 0) {
            pAlku->pVasen = lisaaSolmu(pAlku->pVasen, pSolmu, iArvo);
        } else if (iVertailu > 0) {
            pAlku->pOikea = lisaaSolmu(pAlku->pOikea, pSolmu, iArvo);
        }
    }

    // Selvitetaan paikka, johon solmu lisataan. Tasapainotetaan puu.
    pAlku->iPituus = 1 + suurempiLukuVertailu(puunPituus(pAlku->pVasen), puunPituus(pAlku->pOikea));
    int tasapaino = tasapainoitaPuu(pAlku);

    // vasen vasen tasapainotus
    if ((tasapaino > 1) && (iArvo < pAlku->pVasen->iArvo)) {
        return (oikeaPuoli(pAlku));
    }

    // vasen oikea tasapainotus
    if ((tasapaino > 1) && (iArvo > pAlku->pVasen->iArvo)) {
        pAlku->pVasen = vasenPuoli(pAlku->pVasen);
        return (oikeaPuoli(pAlku));
    }

    // oikea vasen tasapainotus
    if ((tasapaino < -1) && (iArvo < pAlku->pOikea->iArvo)) {
        pAlku->pOikea = oikeaPuoli(pAlku->pOikea);
        return (vasenPuoli(pAlku));
    }

    // oikea oikea tasapainotus
    if ((tasapaino < -1) && (iArvo > pAlku->pOikea->iArvo)) {
        return (vasenPuoli(pAlku));
    }

    return (pAlku);
}

/**
 * @brief Luetaan tiedosto ja luodaan puu rakenne.
 * Pilkotaan luetut rivit.
 * @param pNimi Luettavan tiedoston nimi.
 * @param pJuuriSolmu Puun juurisolmu.
 * @return PUU* Palauttaa juuriSolmun.
 */
PUU *luoPuu(char *pNimi, PUU *pJuuriSolmu) {
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    int iOtsikko = 0;
    char *p1 = NULL, *p2 = NULL;
    int iArvo = 0;

    // Tiedoston avaus
    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Tiedoston lukeminen
    while ((fgets(aRivi, LEN, Tiedosto)) != NULL) {
        aRivi[strlen(aRivi) - 1] = '\0';

        // Ohitetaan otsikko
        if (iOtsikko == 0) {
            iOtsikko++;
            continue;
        }

        // Pilkotaan rivit
        if ((p1 = strtok(aRivi, ";")) == NULL) {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        if ((p2 = strtok(NULL, ";")) == NULL) {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        iArvo = atoi(p2);

        // Maaritetaan juuri solmu jos sitä ei ole määritelty.
        if (pJuuriSolmu == NULL) {
            pJuuriSolmu = lisaaSolmu(pJuuriSolmu, p1, iArvo);
            iOtsikko++;
            continue;
        }

        pJuuriSolmu = lisaaSolmu(pJuuriSolmu, p1, iArvo);
    }

    // Suljetaan tiedosto
    fclose(Tiedosto);
    return (pJuuriSolmu);
}

/**
 * @brief Tasapainoitetun binaaripuun kirjoittaminen tiedostoon
 * 
 * @param pNimi Kirjoitettavan tiedoston nimi.
 * @param pAlku 
 */
void kirjoitaBinaaripuu(char *pNimi, PUU *pAlku) {
    /*if (pAlku == NULL) { //Noora kommentoi pois 19.3.2026 klo. 13.08
        printf("Puu on tyhjä, luo puurakenne ennen kirjoittamista.\n");
        return;
    }*/
    if (pAlku != NULL) {
        kirjoitaTiedostoon(pNimi, pAlku);
        kirjoitaBinaaripuu(pNimi, pAlku->pVasen);
        kirjoitaBinaaripuu(pNimi, pAlku->pOikea);
    }
    return;
}

/**
 * @brief Kirjoittaa binaaripuun tiedostoon
 * 
 * @param pNimi Kirjoitettavan tiedoston nimi
 * @param pAlku Solmu, joka kirjoitetaan tiedostoon
 */
void kirjoitaTiedostoon(char *pNimi, PUU *pAlku) {
    FILE *Tiedosto = NULL;

    if (pAlku == NULL) {
        return;
    }

    /* Tiedoston avaaminen. */
    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }
    /* Tiedostoon kirjoittaminen. */
    fprintf(Tiedosto, "%s,%d\n", pAlku->aNimi, pAlku->iArvo);

    /* Tiedoston sulkeminen. */
    fclose(Tiedosto);
    return;
}

/**
 * @brief Palauttaa solmun tasapainokertoimen.
 *
 * @param pAlku Solmu, josta tasapainokerroin halutaan
 * @return int
 */
int tasapainoitaPuu(PUU *pAlku) {
    // Tarkistetaan, onko Null
    if (pAlku == NULL) {
        return (0);
    }

    // Palautetaan tasapainokerroin
    return (puunPituus(pAlku->pVasen) - puunPituus(pAlku->pOikea));
}

/**
 * @brief Oikean puolen kierto.
 * Puu jarjestetaan, jotta se on tasapainossa.
 * @param pAlku
 * @return PUU* Palauttaa solmun.
 */
PUU *oikeaPuoli(PUU *pAlku) {
    // Tarkistetaan, onko pAlku tai pAlku oikea puoli NULL
    if ((pAlku->pVasen == NULL) || (pAlku == NULL)) {
        return (pAlku);
    }

    // Muuttujien ja vakioden alustaminen
    PUU *pMuuttuja1 = pAlku->pVasen;
    PUU *pMuuttuja2 = pMuuttuja1->pOikea;

    // Sijoitetetaan arvoja
    pMuuttuja1->pOikea = pAlku;
    pAlku->pVasen = pMuuttuja2;

    //  Verrataan ja sijoitetaan suuremmat korkeudet
    pAlku->iPituus = suurempiLukuVertailu(puunPituus(pAlku->pVasen), puunPituus(pAlku->pOikea)) + 1;
    pMuuttuja1->iPituus =
        suurempiLukuVertailu(puunPituus(pMuuttuja1->pVasen), puunPituus(pMuuttuja1->pOikea)) + 1;

    return pMuuttuja1;
}

/**
 * @brief Vasemman puolen kierto.
 * Puu jarjestetaan, jotta se on tasapainossa.
 * @param pAlku
 * @return PUU* Palauttaa solmun.
 */
PUU *vasenPuoli(PUU *pAlku) {
    // Tarkistetaan, onko pAlku tai pAlku oikea puoli NULL
    if ((pAlku->pOikea == NULL) || (pAlku == NULL)) {
        return (pAlku);
    }

    // Muuttujien ja vakioden alustaminen
    PUU *pMuuttuja1 = pAlku->pOikea;
    PUU *pMuuttuja2 = pMuuttuja1->pVasen;

    // Sijoitetetaan arvoja
    pMuuttuja1->pVasen = pAlku;
    pAlku->pOikea = pMuuttuja2;

    // Verrataam ja sijoitetaan suuremmat korkeudet
    pAlku->iPituus = suurempiLukuVertailu(puunPituus(pAlku->pVasen), puunPituus(pAlku->pOikea)) + 1;
    pMuuttuja1->iPituus =
        suurempiLukuVertailu(puunPituus(pMuuttuja1->pVasen), puunPituus(pMuuttuja1->pOikea)) + 1;

    return pMuuttuja1;
}

/**
 * @brief Hakee solmun korkeuden.
 *
 * @param pAlku Kohta, josta korkeus haetaan
 * @return int Palauttaa solmun korkeuden
 */
int puunPituus(PUU *pAlku) {
    // Tarkistetaan, onko Solmu Null
    if (pAlku == NULL) {
        return (0);
    }

    // Palauttaa solmun korkeuden
    return (pAlku->iPituus);
}

/**
 * @brief Vertaa kahta lukua ja palauttaa suuremman.
 *
 * @param iLuku1 Ensimmainen verrattava kokonaisluku.
 * @param iLuku2 Toinen verrattava kokonaisluku.
 * @return int Palauttaa suuremman luvun.
 */
int suurempiLukuVertailu(int iLuku1, int iLuku2) {
    int iPalautus = 0;

    // Verrataan kumpi luvuista on suurempi.
    if (iLuku1 > iLuku2) {
        iPalautus = iLuku1;
    } else {
        iPalautus = iLuku2;
    }

    // Palauttaa suuremman luvun.
    return (iPalautus);
}

PUU *poistaSolmu(char *pNimi, PUU *pJuuriSolmu) {
    int iArvo = 0;

    if (pJuuriSolmu == NULL) {
        printf("Solmua ei löytynyt.\n");
        return (pJuuriSolmu);
    }

    // Testataan, onko syöte nimi vai lukuarvo, ja määritetään lukuarvo puun läpikäymiseksi.
    if (onkoLuku(pNimi)) {
        iArvo = atoi(pNimi);
    } else {
        iArvo = nimenArvo(pNimi, pJuuriSolmu);
    }

    // Lehtisolmun poistaminen.
    if (iArvo < pJuuriSolmu->iArvo) {
        pJuuriSolmu->pVasen = poistaSolmu(pNimi, pJuuriSolmu->pVasen);
    } else if (iArvo > pJuuriSolmu->iArvo) {
        pJuuriSolmu->pOikea = poistaSolmu(pNimi, pJuuriSolmu->pOikea);
    } else {
        if (pJuuriSolmu->pVasen == NULL && pJuuriSolmu->pOikea == NULL) {
            free(pJuuriSolmu);
            pJuuriSolmu = NULL;
            printf("Solmu poistettu.\n");
            return (pJuuriSolmu);
        } else {
            printf("Voit poistaa vain lehtisolmun.\n");
            return (pJuuriSolmu);
        }
    }

    // Puun korkeuden päivittäminen.
    if (pJuuriSolmu == NULL) {
        return (pJuuriSolmu);
    }

    int iLuku1 = puunPituus(pJuuriSolmu->pVasen);
    int iLuku2 = puunPituus(pJuuriSolmu->pOikea);
    pJuuriSolmu->iPituus = suurempiLukuVertailu(iLuku1, iLuku2) + 1;

    // Puun tasapanottaminen.
    int iTasapaino = tasapainoitaPuu(pJuuriSolmu);
    // Vasen-vasen tapaus.
    if (iTasapaino > 1 && tasapainoitaPuu(pJuuriSolmu->pVasen) >= 0) {
        return oikeaPuoli(pJuuriSolmu);
    }

    // Oikea-oikea tapaus.
    if (iTasapaino < -1 && tasapainoitaPuu(pJuuriSolmu->pOikea) <= 0) {
        return vasenPuoli(pJuuriSolmu);
    }

    // Vasen-oikea tapaus.
    if (iTasapaino > 1 && tasapainoitaPuu(pJuuriSolmu->pVasen) < 0) {
        pJuuriSolmu->pVasen = vasenPuoli(pJuuriSolmu->pVasen);
        return oikeaPuoli(pJuuriSolmu);
    }

    // Oikea-vasen tapaus.
    if (iTasapaino < -1 && tasapainoitaPuu(pJuuriSolmu->pOikea) > 0) {
        pJuuriSolmu->pOikea = oikeaPuoli(pJuuriSolmu->pOikea);
        return vasenPuoli(pJuuriSolmu);
    }

    return (pJuuriSolmu);
}

int onkoLuku(char *pNimi) {
    int tosi = 0;
    char *ptr = pNimi;
    
    while (*ptr) {
        if (!isdigit(*ptr)) {
            return tosi;
        }
        ptr++;
    }
    tosi = 1;
    return (tosi);
}

int nimenArvo(char *pNimi, PUU *pJuuriSolmu) {  
    if (pJuuriSolmu == NULL) {
        return (-1);
    }

    if (strcmp(pJuuriSolmu->aNimi, pNimi) == 0) {
        int iArvo = pJuuriSolmu->iArvo;
        return (iArvo);
    }

    int iArvo = nimenArvo(pNimi, pJuuriSolmu->pVasen);
    if (iArvo != -1) {
        return (iArvo); 
    } else {
        int iArvo = nimenArvo(pNimi, pJuuriSolmu->pOikea);
        return (iArvo);
    }
}