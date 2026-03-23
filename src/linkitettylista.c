#include "linkitettylista.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linkitettylista

/**
 * @brief Lukee tiedoston.
 * 
 * Avaa ja lukee kayttajan syotteen mukaisen tiedoston.
 * Kutsuu muistinvaraus aliohjelmaa muistin varaamiseksi.
 * 
 * @param pNimi Luettavan tiedoston nimi.
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return pAlku Uusi osoitin linkitetyn listan alkuun.
 */
TIEDOT *lue(char *pNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    char *p1 = NULL, *p2 = NULL;
    int iOtsikko = 0;
    int iMaara = 0;

    /* Tiedoston avaaminen. */

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    /* Tiedoston lukeminen */

    while ((fgets(aRivi, LEN, Tiedosto)) != NULL) {

        aRivi[strlen(aRivi) - 1] = '\0';

        if (iOtsikko == 0) {
            iOtsikko = 1;
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

        iMaara = atoi(p2);

        /* Muistin varaaminen ja linkitetyn listan luominen. */

        pAlku = varaaMuistia(pAlku, p1, iMaara);
    }
    /* Tiedoston sulkeminen. */
    fclose(Tiedosto);
    printf("Tiedosto '%s' luettu.\n", pNimi);
    return (pAlku);
}

/**
 * @brief Varaa muistin ja lisää uuden solmun kaksisuuntaisen linkitetyn listan.
 * 
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param pNimi Merkkijono solmun nimeksi.
 * @param iMaara Luku, joka asetetaan solmuun maaraksi.
 * @return pAlku Uusi osoitin linkitetyn listan alkuun.
 */
TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pNimi, int iMaara) {
    TIEDOT *pUusi = NULL;
    TIEDOT *ptr = NULL;

    /* Muistin varaaminen. */

    if ((pUusi = (TIEDOT *)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    /* Kaksisuuntaisen linkitetyn listan luominen. */

    strcpy(pUusi->aSukunimi, pNimi);
    pUusi->iYhteensa = iMaara;
    pUusi->pSeuraava = NULL;

    if (pAlku == NULL) {
        pUusi->pEdellinen = NULL;
        pAlku = pUusi;
    } else {
        ptr = pAlku;
        while (ptr->pSeuraava != NULL) {
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
        pUusi->pEdellinen = ptr;
    }
    return (pAlku);
}

/**
 * @brief Vapauttaa linkitetyn listan varaaman muistin.
 * 
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return pAlku Osoitin, joka on NULL, koska lista on tyhja.
 */
TIEDOT *vapautaMuisti(TIEDOT *pAlku) {
    /* Muistin vapauttaminen. */
    TIEDOT *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return (pAlku);
}

/**
 * @brief Kirjoittaa linkitetyn listan tiedostoon alusta loppuun.
 * 
 * @param pNimi Kirjoitettavan tiedoston nimi.
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return void
 */
void kirjoitaTiedostoAlustaLoppuun(char *pNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    TIEDOT *ptr = NULL;

    if (pAlku == NULL) {
        printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
        return;
    }

    // Kirjoitus tiedoston avaaminen
    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Tiedostoon kirjoittaminen
    ptr = pAlku;
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aSukunimi, ptr->iYhteensa);
        ptr = ptr->pSeuraava;
    }

    // Tiedoston sulkeminen
    fclose(Tiedosto);
    printf("Tiedosto %s kirjoitettu.\n", pNimi);
    return;
}

/**
 * @brief Kirjoittaa linkitetyn listan tiedostoon lopusta alkuun.
 * 
 * @param pNimi Kirjoitettavan tiedoston nimi.
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return void
 */
void kirjoitaTiedostoLopustaAlkuun(char *pNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    TIEDOT *ptr = pAlku;

    if (pAlku == NULL) {
        printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
        return;
    }

    if ((Tiedosto = fopen(pNimi, "a")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Mennään listan loppuun.
    while (ptr->pSeuraava != NULL) {
        ptr = ptr->pSeuraava;
    }

    // Lopusta alkuun, kirjoitetaan tiedostoon.
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aSukunimi, ptr->iYhteensa);
        ptr = ptr->pEdellinen;
    }

    fclose(Tiedosto);
    printf("Tiedosto %s kirjoitettu.\n", pNimi);
    return;
}

