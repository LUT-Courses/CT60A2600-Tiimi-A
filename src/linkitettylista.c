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

/**
 * @brief Lisää linkitettyyn listaan kayttajan syottamat tiedot.
 * 
 * Lisaa kayttajan haluamaan kohtaan (indeksi) tiedot lisattavasta nimesta ja niiden lukumaarasta.
 * 
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param iIndeksi Kayttajan antama indeksi, eli kohta, johon tietue lisataan linkitetyssa listassa.
 * Jos lista on tyhja, lisataan automaattisesti ensimmaiseksi elementiksi.
 * Jos indeksi on suurempi kuin listan elementtien maara, lisataan automaattisesti viimeiseksi.
 * @param pNimi Lisattava nimi.
 * @param iArvo Lisattavan nimen lukumaara.
 * @return pAlku Osoitin listan nykyiseen alkuun.
 */
TIEDOT *lisaaListaan(TIEDOT *pAlku, int iIndeksi, char *pNimi, int iArvo) {
    TIEDOT *pUusi = NULL;
    TIEDOT *ptr = pAlku;
    int i = 0;

    // Varataan muistia uudelle linkitetyn listan solmulle.
    if ((pUusi = (TIEDOT *)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit (0);
    }

    // Lisataan tiedot tietueeseen.
    strcpy(pUusi->aSukunimi, pNimi);
    pUusi->iYhteensa = iArvo;

    // Jos lista on tyhja, lisataan uusi solmu ensimmaiseksi.
    if (pAlku == NULL) {
        pUusi->pEdellinen = NULL;
        pUusi->pSeuraava = NULL;
        pAlku = pUusi;
        return (pAlku);
    } else {
        // Jos lisataan listan alkuun, eli indeksi = 0.
        if (iIndeksi == 0) {
            pUusi->pEdellinen = NULL;
            pUusi->pSeuraava = pAlku;
            pAlku->pEdellinen = pUusi;
            pAlku = pUusi;
            return (pAlku);
        }

        // Etsitaan listalta oikea kohta, johon tiedot lisataan.
        while (ptr->pSeuraava != NULL && i < (iIndeksi - 1)) {
            ptr = ptr->pSeuraava;
            i++;
        }
        // Lisataan tiedot oikeaan kohtaan linkitettya listaa.
        // Paivitetaan osoittimet osoittamaan oikeisiin kohtiin.
        pUusi->pSeuraava = ptr->pSeuraava;
        pUusi->pEdellinen = ptr;

        if (ptr->pSeuraava != NULL) {
            ptr->pSeuraava->pEdellinen = pUusi;
        }

        ptr->pSeuraava = pUusi;
    }
    return (pAlku);
}

/**
 * @brief Poistetaan linkitetystä listasta alkio lukumäärän perusteella.
 * Käyttäjä on antanut lukumäärän. Alkio, jossa on tämä lukumääärä poistetaan.
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param iLKM Käyttäjän antama lukumäärä. Alkio, jossa on tämä lukumäärä poistetaan. 
 * @return TIEDOT* Palautetaan linkitettylista, josta on poistettu alkio. 
 */
TIEDOT *poistaListastaLkmPeruusteella(TIEDOT *pAlku, int iLKM) {
    TIEDOT *ptr = pAlku;
    TIEDOT *pEdellinen = NULL;

    // Tarkistetaan, onko poistettava alkio ensimmäinen.
    if ((ptr != NULL) && (ptr->iYhteensa == iLKM)) {
        // Sijoitetaan osoitin osoittamaan seuraavaan alkioon.
        pAlku = ptr->pSeuraava;
        free(ptr);
        printf("Alkio poistettu.\n");

    // Jos poistettava alkio ei ole ensimmäinen. 
    } else {
        // Etsitään kohtaa, jossa poistettava alkio on. 
        while(ptr != NULL) {
            if (ptr->iYhteensa == iLKM) {
                pEdellinen->pSeuraava = ptr->pSeuraava;
                free(ptr);
                printf("Alkio poistettu.\n");
                break;
            }
            pEdellinen = ptr;
            ptr = ptr->pSeuraava;
        }
    }

    return (pAlku);
}

/**
 * @brief Poistetaan linkitetystä listasta alkio nimen perusteella.
 * Käyttäjä on antanut nimen. Alkio, jossa on tämä nimi poistetaan.
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param pNimi Käyttäjän antama nimi. Alkio, jossa on tämä nimi poistetaan.
 * @return TIEDOT* TIEDOT* Palautetaan linkitettylista, josta on poistettu alkio.
 */
TIEDOT *poistaListastaNimenPerusteella(TIEDOT *pAlku, char *pNimi) {
    TIEDOT *ptr = pAlku;
    TIEDOT *pEdellinen = NULL;

    // Tarkistetaan, onko poistettava alkio ensimmäinen.
    if ((ptr != NULL) && (strcmp(ptr->aSukunimi, pNimi) == 0)) {
        // Sijoitetaan osoitin osoittamaan seuraavaan alkioon.
        pAlku = ptr->pSeuraava;
        free(ptr);
        printf("Alkio poistettu.\n");

    // Jos poistettava alkio ei ole ensimmäinen. 
    } else {
        // Etsitään kohtaa, jossa poistettava alkio on.
        while(ptr != NULL) {
            if (strcmp(ptr->aSukunimi, pNimi) == 0) {
                pEdellinen->pSeuraava = ptr->pSeuraava;
                free(ptr);
                printf("Alkio poistettu.\n");
                break;
            }
            pEdellinen = ptr;
            ptr = ptr->pSeuraava;
        }
    }
    return (pAlku);
}

/**
 * @brief Etsii kaikki alkiot, joiden nimien lukumäärä on käyttäjän antama luku. 
 * 
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param iLKM Käytäjän antama lukumäärä, joiden määrä selvitetään. 
 * @return int Palauttaa luvun, jossa on kaikki alkiot, joissa on käyttäjän antama luku.
 */
int useammallaAlkiollaSamaLKM(TIEDOT *pAlku, int iLKM) {
    int iSamoja = 0;
    TIEDOT *ptr = NULL;
    ptr = pAlku;

    // Käydään linkitettylista läpi
    while(ptr != NULL) {
        // Lisätään summaan yksi, jos linkitetyn listan alkion lukumäärä on sama kuin käyttäjän antama luku. 
        if(ptr->iYhteensa == iLKM) {
            iSamoja++;
        }
        ptr = ptr->pSeuraava;
    }

    return (iSamoja);
}