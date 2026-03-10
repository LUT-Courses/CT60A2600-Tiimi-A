#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int valikko() {
    int iValinta = 0;
    printf("Valitse haluamasi toiminto:\n");
    printf("1) Lista\n");
    printf("2) Binääripuu\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

int listaValikko() {
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedosto alusta loppuun\n");
    printf("3) Kirjoita tiedosto lopusta alkuun\n");
    printf("4) Tyhjennä taulukko\n");
    printf("0) Takaisin\n"); // Viikko 2: takaisin ??
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

int binaaripuuValikko() {
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto:\n");
    printf("1) Luo puu\n");
    printf("2) Tulosta puu\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Tyhjennä puu\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

char *kysyNimi(char *pPrompti, char *pNimi) {
    printf("%s", pPrompti);
    scanf("%s", pNimi);
    getchar();
    return (pNimi);
}

// Viikko 1 / Lista:

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
    return (pAlku);
}

void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    TIEDOT *ptr = NULL;

    // Kirjoitus tiedoston avaaminen
    Tiedosto = fopen(pKirjoitaTiedostoNimi, "a");
    if (Tiedosto == NULL) {
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
    printf("Tiedosto %s kirjoitettu.\n", pKirjoitaTiedostoNimi);
    return;
}

void kirjoitaTiedostoLopustaAlkuun(char *pNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    TIEDOT *ptr = pAlku;

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
    return;
}

// Viikko 2 / Binääripuu:

PUU *varaaMuistiaPuulle(char *pSolmu, int iValiMatka) {
    PUU *pUusi = NULL;

    // Muistin varaaminen
    if ((pUusi = (PUU *)malloc(sizeof(PUU))) == NULL) {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    strcpy(pUusi->aNimi, pSolmu);
    pUusi->iArvo = iValiMatka;
    pUusi->pVasen = NULL;
    pUusi->pOikea = NULL;
    return (pUusi);
}

/*PUU *vapautaMuistiPuu(PUU *pJuuriSolmu) {
    //Muistin vapauttaminen
    vapautaMuistiPuu(pJuuriSolmu->pVasen);
    vapautaMuistiPuu(pJuuriSolmu->pOikea);
    free(pJuuriSolmu);

    return(pJuuriSolmu);
}*/

PUU *lisaaSolmu(PUU *pAlku, char *pSolmu, int iValiMatka) {
    int iVertailu = 0;

    // Varataan muistia, jos muisti tyhja
    if (pAlku == NULL) {
        return varaaMuistiaPuulle(pSolmu, iValiMatka);
    }

    iVertailu = strcmp(pSolmu, pAlku->aNimi);

    // Solmujen lisaaminen
    if (iValiMatka < pAlku->iArvo) {
        pAlku->pVasen = lisaaSolmu(pAlku->pVasen, pSolmu, iValiMatka);
    } else if (iValiMatka > pAlku->iArvo) {
        pAlku->pOikea = lisaaSolmu(pAlku->pOikea, pSolmu, iValiMatka);

        // Testataan, onko arvot samat
    } else if (iValiMatka == pAlku->iArvo) {
        if (iVertailu < 0) {
            pAlku->pVasen = lisaaSolmu(pAlku->pVasen, pSolmu, iValiMatka);
        } else if (iVertailu > 0) {
            pAlku->pOikea = lisaaSolmu(pAlku->pOikea, pSolmu, iValiMatka);
        }
    }

    return (pAlku);
}

PUU *luoPuu(char *pNimi, PUU *pJuuriSolmu) {
    // Voi viedä enemmän kuin yhden aliohjelman varmaan, + erillinen muistinkäsittely?
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    int iOtsikko = 0;
    char *p1 = NULL, *p2 = NULL;
    int iValiMatka = 0;

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

        iValiMatka = atoi(p2);

        // Maaritetaan juuri solmu jos sita ei ole maaritetty
        if (pJuuriSolmu == NULL) {
            pJuuriSolmu = lisaaSolmu(pJuuriSolmu, p1, iValiMatka);
            iOtsikko++;
            continue;
        }

        lisaaSolmu(pJuuriSolmu, p1, iValiMatka);
    }

    fclose(Tiedosto);
    return (pJuuriSolmu);
}

PUU *tulostaPuu(PUU *pAlku) {
    // tulosta puu järkevässä muodossa, CodeGrade *ei* testaa
    if (pAlku != NULL) {
        printf("%s-%d + ", pAlku->aNimi, pAlku->iArvo);
        tulostaPuu(pAlku->pVasen);
        tulostaPuu(pAlku->pOikea);
    }
    return (0);
}

void syvyyshaku(char *pNimi) {
    // syvyyshaku arvon mukaan, kirjoitetaan käydyt nodet /polku tiedostoon
}

void leveyshaku(char *pNimi) {
    // leveyshaku nimen mukaan, kirjoitetaan käydyt nodet /polku tiedostoon
}
