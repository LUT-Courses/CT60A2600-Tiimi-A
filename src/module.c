#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

int valikko() {
    int iValinta = 0;
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return (iValinta);
}

TIEDOT *lue(char *pNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    char *p1 = NULL, *p2 = NULL;
    int iOtsikko = 0;
    int iMaara = 0;

    /* Pitääkö tämän olla oma aliohjelmansa (avaaminen)? */

    if ((Tiedosto = fopen(pNimi, "r")) == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    /* Tiedoston lukeminen */

    while ((fgets(aRivi, LEN, Tiedosto)) != NULL) {

        aRivi[strlen(aRivi)-1] = '\0';

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
    /* Pitääkö tämän olla oma aliohjelmansa (sulkeminen)? */
    fclose(Tiedosto);
    return(pAlku);
}

TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara) {
    TIEDOT *pUusi = NULL;
    TIEDOT *ptr = NULL;

    /* Muistin varaaminen. */

    if ((pUusi = (TIEDOT *)malloc(sizeof(TIEDOT))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    /* Kaksisuuntaisen linkitetyn listan luominen. */

    strcpy(pUusi->aSukunimi, pSukunimi);
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

TIEDOT *vapautaMuisti(TIEDOT *pAlku) {
    /* Muistin vapauttaminen. */
    TIEDOT *ptr = pAlku;
    while (ptr != NULL) {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return(pAlku);
}

void kirjoita()
{
}

void tulosta()
{
}