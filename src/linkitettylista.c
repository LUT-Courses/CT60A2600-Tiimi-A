#include "linkitettylista.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Linkitettylista

/**
 * @brief Lukee tiedoston.
 *
 * Avaa ja lukee kayttajan syötteen mukaisen tiedoston.
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

    strcpy(pUusi->aNimi, pNimi);
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
    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Tiedostoon kirjoittaminen
    ptr = pAlku;
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aNimi, ptr->iYhteensa);
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

    if ((Tiedosto = fopen(pNimi, "w")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Mennään listan loppuun.
    while (ptr->pSeuraava != NULL) {
        ptr = ptr->pSeuraava;
    }

    // Lopusta alkuun, kirjoitetaan tiedostoon.
    while (ptr != NULL) {
        fprintf(Tiedosto, "%s,%d\n", ptr->aNimi, ptr->iYhteensa);
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
    int i = 1;

    // Varataan muistia uudelle linkitetyn listan solmulle.
    if ((pUusi = (TIEDOT *)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    // Lisataan tiedot tietueeseen.
    strcpy(pUusi->aNimi, pNimi);
    pUusi->iYhteensa = iArvo;

    // Jos lista on tyhja, lisataan uusi solmu ensimmaiseksi.
    if (pAlku == NULL) {
        pUusi->pEdellinen = NULL;
        pUusi->pSeuraava = NULL;
        pAlku = pUusi;
        return (pAlku);
    } else {
        // Jos lisataan listan alkuun, eli indeksi = 0.
        if (iIndeksi <= 1) {
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
 * @brief Poistaa linkitetystä listasta alkion.
 * 
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @param iLuvuVaiNimi Tieto siitä, haluaako käyttäjä poistaa alkion nimen vai luvun perusteella.  
 * @param pTieto Poistettavan alkion tieto, nimi tai luku.
 * @return TIEDOT* pAlku Osoitin listan nykyiseen alkuun.
 */
TIEDOT *poistaListastaAlkio(TIEDOT *pAlku, int iLuvuVaiNimi, char *pTieto) {
    int iSamojenAlkiodenLkm = 0;
    char aPoistettavaNimi[LEN] = "";

    if (iLuvuVaiNimi == -2) {
        pAlku = poistaListastaNimenPerusteella(pAlku, pTieto);
    } else {
        iSamojenAlkiodenLkm = useammallaAlkiollaSamaLKM(pAlku, iLuvuVaiNimi);

        if (iSamojenAlkiodenLkm > 1) {
            kysyNimi("Anna nimi, joka poistetaan: ", aPoistettavaNimi);
            pAlku = poistaListastaNimenPerusteella(pAlku, aPoistettavaNimi);
        } else {
            pAlku = poistaListastaLkmPeruusteella(pAlku, iLuvuVaiNimi);
        }
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
    int iAlkioLoytyi = 0;

    // Tarkistetaan, onko poistettava alkio ensimmäinen.
    if ((ptr != NULL) && (ptr->iYhteensa == iLKM)) {
        // Sijoitetaan osoitin osoittamaan seuraavaan alkioon.
        pAlku = ptr->pSeuraava;
        free(ptr);
        printf("Alkio poistettu.\n");

        // Jos poistettava alkio ei ole ensimmäinen.
    } else {
        // Etsitään kohtaa, jossa poistettava alkio on.
        while (ptr != NULL) {
            if (ptr->iYhteensa == iLKM) {
                pEdellinen->pSeuraava = ptr->pSeuraava;
                free(ptr);
                iAlkioLoytyi = 1;
                break;
            }
            pEdellinen = ptr;
            ptr = ptr->pSeuraava;
        }

        // Kerrotaan käyttäjälle, poistettiinko alkio.
        if(iAlkioLoytyi == 1) {
            printf("Alkio poistettu.\n");
        } else {
            printf("Poistettavaa alkiota ei löydetty.\n");
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
    int iAlkioLoytyi = 0;

    // Tarkistetaan, onko poistettava alkio ensimmäinen.
    if ((ptr != NULL) && (strcmp(ptr->aNimi, pNimi) == 0)) {
        // Sijoitetaan osoitin osoittamaan seuraavaan alkioon.
        pAlku = ptr->pSeuraava;
        free(ptr);
        printf("Alkio poistettu.\n");

        // Jos poistettava alkio ei ole ensimmäinen.
    } else {
        // Etsitään kohtaa, jossa poistettava alkio on.
        while (ptr != NULL) {
            if (strcmp(ptr->aNimi, pNimi) == 0) {
                pEdellinen->pSeuraava = ptr->pSeuraava;
                free(ptr);
                iAlkioLoytyi = 1;
                break;
            }
            pEdellinen = ptr;
            ptr = ptr->pSeuraava;
        }

        // Kerrotaan käyttäjälle, poistettiinko alkio.
        if(iAlkioLoytyi == 1) {
            printf("Alkio poistettu.\n");
        } else {
            printf("Poistettavaa alkiota ei löydetty.\n");
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
    while (ptr != NULL) {
        // Lisätään summaan yksi, jos linkitetyn listan alkion lukumäärä on sama kuin käyttäjän
        // antama luku.
        if (ptr->iYhteensa == iLKM) {
            iSamoja++;
        }
        ptr = ptr->pSeuraava;
    }

    return (iSamoja);
}

/**
 * @brief Selvittää onko käyttäjän antama syöte luku vai nimi. 
 * 
 * @param Tieto Käyttäjän antama syöte.
 * @return int Tieto, onko luku vai nimi, jos -2, niin käyttäjä antoi luvun, jos joku muu niin se on luku.
 */
int onkoLukuVaiNimi(char *Tieto) {
    int iVastaus = 0;
    int i = 0;
    int iPituus = 0;

    iPituus = strlen(Tieto);

    for (i = 0; i < iPituus; i++) {
        if (isdigit(Tieto[i])) {
            iVastaus = -1;
        } else {
            iVastaus = -2;
            break;
        }
    }

    if (iVastaus == -1) {
        iVastaus = atoi(Tieto);
    }

    return (iVastaus);
}

// L11 / Lomituslajittelu (merge sort)

/**
 * @brief Laskee linkitetyn listan pituuden.
 *
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return int Linkitetyn listan alkioiden lukumäärä.
 */
int laskeListanPituus(TIEDOT *pAlku) {
    int i = 0;
    while (pAlku != NULL) {
        i++;
        pAlku = pAlku->pSeuraava;
    }
    return i;
}

/**
 * @brief Halkaisee linkitetyn listan kahteen puoliskoon.
 *
 * @param pAlku Osoitin linkitetyn listan alkuun.
 * @return TIEDOT* Osoitin listan jälkimmäisen puoliskon alkuun.
 */
TIEDOT *halkaise(TIEDOT *pAlku) {
    TIEDOT *p1 = NULL, *p2 = NULL;
    int i;
    int iPituus = 0;
    int iKeskikohta = 0;

    iPituus = laskeListanPituus(pAlku);
    iKeskikohta = iPituus / 2 - 1;

    p1 = pAlku;
    for (i = 0; i < iKeskikohta; i++) {
        p1 = p1->pSeuraava;
    }

    // Halkaistaan lista kahtia, p1 päättyy siihen mistä p2 alkaa
    p2 = p1->pSeuraava;
    p1->pSeuraava = NULL;
    if (p2 != NULL) {
        p2->pEdellinen = NULL;
    }

    // palautetaan osoitin toisen listan alkuun
    return p2;
}

/**
 * @brief Lomittaa (merge) kaksi lajiteltua listaa yhdeksi.
 *
 * @param p1 Osoitin ensimmäisen lajitellun listan alkuun.
 * @param p2 Osoitin jälkimmäisen lajitellun listan alkuun.
 * @return TIEDOT* yhdistetty lajiteltu lista.
 */
TIEDOT *lomitus(TIEDOT *p1, TIEDOT *p2) {
    // Jos kumpikaan lista on tyhjä, palautetaan toinen.
    if (p1 == NULL)
        return p2;
    if (p2 == NULL)
        return p1;

    TIEDOT *p3 = NULL;      // Uuden listan alku.
    TIEDOT *p3Loppu = NULL; // Uuden lista loppu, jotta loppuun lisääminen onnistuu helposti.

    // Käydään molempia listoja läpi:
    while (p1 != NULL && p2 != NULL) {
        int iVertailu =
            strcmp(p1->aNimi, p2->aNimi); // Jos sama arvo, lisätään aakkosjärjestyksessä.
        if (p1->iYhteensa > p2->iYhteensa || (p1->iYhteensa == p2->iYhteensa && iVertailu > 0)) {
            TIEDOT *ptr = p2; // p2[0] talteen
            // Poistetaan p2[0] listasta.
            p2 = p2->pSeuraava;
            if (p2 != NULL) {
                p2->pEdellinen = NULL;
            }
            // Lisätään p2[0] uuden listan loppuun.
            ptr->pSeuraava = NULL;
            ptr->pEdellinen = p3Loppu;
            if (p3Loppu != NULL) {
                p3Loppu->pSeuraava = ptr;
            } else {
                p3 = ptr; // ensimmäinen alkio, jos lista tyhjä
            }
            p3Loppu = ptr; // päivitetään loppu.
        } else {
            TIEDOT *ptr = p1; // p1[0] talteen
            p1 = p1->pSeuraava;
            // Poistetaan p1[0] listasta.
            if (p1 != NULL) {
                p1->pEdellinen = NULL;
            }
            // Lisätään p1[0] uuden listan loppuun.
            ptr->pSeuraava = NULL;
            ptr->pEdellinen = p3Loppu;
            if (p3Loppu != NULL) {
                p3Loppu->pSeuraava = ptr;
            } else {
                p3 = ptr; // ensimmäinen alkio, jos lista tyhjä
            }
            p3Loppu = ptr; // päivitetään loppu.
        }
    }

    // Tässä kohtaa joko p1 tai p2 on tyhjä.

    // Lisätään loput p1:stä uuden listan loppuun.
    while (p1 != NULL) {
        TIEDOT *ptr = p1;
        p1 = p1->pSeuraava;
        if (p1 != NULL) {
            p1->pEdellinen = NULL;
        }
        ptr->pSeuraava = NULL;
        ptr->pEdellinen = p3Loppu;
        if (p3Loppu != NULL) {
            p3Loppu->pSeuraava = ptr;
        } else {
            p3 = ptr;
        }
        p3Loppu = ptr;
    }

    // Lisätään loput p2:stä uuden listan loppuun.
    while (p2 != NULL) {
        TIEDOT *ptr = p2;
        p2 = p2->pSeuraava;
        if (p2 != NULL) {
            p2->pEdellinen = NULL;
        }
        ptr->pSeuraava = NULL;
        ptr->pEdellinen = p3Loppu;
        if (p3Loppu != NULL) {
            p3Loppu->pSeuraava = ptr;
        } else {
            p3 = ptr;
        }
        p3Loppu = ptr;
    }
    return p3;
}

/**
 * @brief Lajittelee listan rekursiivisella lomituslajittelulla (Merge sort).
 *
 * @param pAlku Osoitin lajiteltavan linkitetyn listan alkuun.
 * @return TIEDOT* Lajiteltu lista.
 */
TIEDOT *lomitusLajittelu(TIEDOT *pAlku) {
    TIEDOT *p1 = NULL, *p2 = NULL;

    // Jos lista on tyhjä tai sisältää vain yhden alkion
    if (pAlku == NULL || pAlku->pSeuraava == NULL) {
        return pAlku;
    }

    // Jaetaan lista kahtia
    p2 = halkaise(pAlku);
    p1 = pAlku;

    // Lajitellaan molemmat puolikkaat
    p1 = lomitusLajittelu(p1);
    p2 = lomitusLajittelu(p2);

    // Yhdistetään lajitellut puolikkaat
    return lomitus(p1, p2);
}

// Lisäyslajittelu (Insertion sort)

/**
 * @brief Lajittelee listan lisayslajittelulla (Insertion sort).
 *
 * @param pAlku Osoitin lajiteltavan linkitetyn listan alkuun.
 * @return TIEDOT* Lajiteltu lista.
 */
TIEDOT *lisaysLajittelu(TIEDOT *pAlku) {
    // Jos lista on tyhjä
    if (pAlku == NULL) {
        return pAlku;
    }

    TIEDOT *pLajittelematon = pAlku; // Osoitin lajiteltavan listan nykyiseen solmuun
    TIEDOT *pLajiteltu = NULL;       // Tehdään toinen lista, johon lajitellut tiedot laitetaan
    TIEDOT *pSeuraava = NULL;
    TIEDOT *ptr = NULL; // Osoitin, jolla läpikäydään lajiteltua listaa.

    /* Käydään lajittelematonta listaa läpi ja lisätään alkiot
     * lajiteltuun listaan pienenevässä järjestyksessä arvon mukaan.
     */
    while (pLajittelematon != NULL) {
        pSeuraava = pLajittelematon->pSeuraava; // pSeuraava talteen ennen listan läpikäyntiä

        // irrotetaan alkio
        if (pSeuraava != NULL) {
            pSeuraava->pEdellinen = pLajittelematon->pEdellinen;
        }
        if (pLajittelematon->pEdellinen != NULL) {
            pLajittelematon->pEdellinen->pSeuraava = pSeuraava;
        }
        pLajittelematon->pSeuraava = NULL;
        pLajittelematon->pEdellinen = NULL;

        if (pLajiteltu == NULL || pLajiteltu->iYhteensa < pLajittelematon->iYhteensa ||
            (pLajiteltu->iYhteensa == pLajittelematon->iYhteensa &&
             strcmp(pLajiteltu->aNimi, pLajittelematon->aNimi) < 0)) {
            // Lisätään lajitellun listan alkuun
            pLajittelematon->pSeuraava = pLajiteltu;
            if (pLajiteltu != NULL) {
                pLajiteltu->pEdellinen = pLajittelematon;
            }
            pLajiteltu = pLajittelematon;

        } else {
            ptr = pLajiteltu;
            while (ptr->pSeuraava != NULL &&
                   (ptr->pSeuraava->iYhteensa > pLajittelematon->iYhteensa ||
                    (ptr->pSeuraava->iYhteensa == pLajittelematon->iYhteensa &&
                     strcmp(ptr->pSeuraava->aNimi, pLajittelematon->aNimi) > 0))) {
                ptr = ptr->pSeuraava;
            }
            pLajittelematon->pSeuraava = ptr->pSeuraava;
            if (ptr->pSeuraava != NULL) {
                ptr->pSeuraava->pEdellinen = pLajittelematon;
            }
            ptr->pSeuraava = pLajittelematon;
            pLajittelematon->pEdellinen = ptr;
        }
        pLajittelematon = pSeuraava;
    }
    return pLajiteltu;
}
