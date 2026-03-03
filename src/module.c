#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

int valikko()
{
    int iValinta = 0;
    printf("1) Lue Tiedosto\n");
    printf("2) Kirjoita tiedosto alusta loppuun\n");
    printf("3) Kirjoita tiedosto lopusta alkuun\n");
    printf("4) Tyhjennä taulukko\n");
    printf("0) Lopeta\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return (iValinta);
}

TIEDOT *lue(char *pNimi, TIEDOT *pAlku)
{
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    char *p1 = NULL, *p2 = NULL;
    int iOtsikko = 0;
    int iMaara = 0;

    /* Pitääkö tämän olla oma aliohjelmansa (avaaminen)? */

    if ((Tiedosto = fopen(pNimi, "r")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    /* Tiedoston lukeminen */

    while ((fgets(aRivi, LEN, Tiedosto)) != NULL)
    {

        aRivi[strlen(aRivi) - 1] = '\0';

        if (iOtsikko == 0)
        {
            iOtsikko = 1;
            continue;
        }

        if ((p1 = strtok(aRivi, ";")) == NULL)
        {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        if ((p2 = strtok(NULL, ";")) == NULL)
        {
            perror("Tiedoston pilkkominen epäonnistui, lopetetaan");
            exit(0);
        }

        iMaara = atoi(p2);

        /* Muistin varaaminen ja linkitetyn listan luominen. */

        pAlku = varaaMuistia(pAlku, p1, iMaara);
    }
    /* Pitääkö tämän olla oma aliohjelmansa (sulkeminen)? */
    fclose(Tiedosto);
    return (pAlku);
}

TIEDOT *varaaMuistia(TIEDOT *pAlku, char *pSukunimi, int iMaara)
{
    TIEDOT *pUusi = NULL;
    TIEDOT *ptr = NULL;

    /* Muistin varaaminen. */

    if ((pUusi = (TIEDOT *)malloc(sizeof(TIEDOT))) == NULL)
    {
        perror("Muistin varaus epäonnistui, lopetetaan");
        exit(0);
    }

    /* Kaksisuuntaisen linkitetyn listan luominen. */

    strcpy(pUusi->aSukunimi, pSukunimi);
    pUusi->iYhteensa = iMaara;
    pUusi->pSeuraava = NULL;

    if (pAlku == NULL)
    {
        pUusi->pEdellinen = NULL;
        pAlku = pUusi;
    }
    else
    {
        ptr = pAlku;
        while (ptr->pSeuraava != NULL)
        {
            ptr = ptr->pSeuraava;
        }
        ptr->pSeuraava = pUusi;
        pUusi->pEdellinen = ptr;
    }
    return (pAlku);
}

TIEDOT *vapautaMuisti(TIEDOT *pAlku)
{
    /* Muistin vapauttaminen. */
    TIEDOT *ptr = pAlku;
    while (ptr != NULL)
    {
        pAlku = ptr->pSeuraava;
        free(ptr);
        ptr = pAlku;
    }
    pAlku = NULL;
    return (pAlku);
}

void kysyKirjoitettavaTiedosto(char *pKirjoitusTiedostoNimi) {
    printf("Anna kirjoitettavan tiedoston nimi: ");
    scanf("%s", pKirjoitusTiedostoNimi);
    getchar();
}

void kysyLuettavaTiedosto(char *pLueTiedostoNimi) {
    printf("Anna luettavan tiedoston nimi: ");
    scanf("%s", pLueTiedostoNimi);
    getchar();
}

void kirjoitaTiedostoAlustaLoppuun(char *pKirjoitaTiedostoNimi, TIEDOT *pAlku) {
    FILE *Tiedosto = NULL;
    char aRivi[LEN] = "";
    TIEDOT *ptr = NULL;

    //Kirjoitus tiedoston avaaminen
    Tiedosto = fopen(pKirjoitaTiedostoNimi, "a");
    if(Tiedosto == NULL) {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    //Tiedostoon kirjoittaminen
    ptr = pAlku;
    while (ptr != NULL)
    {
        fprintf(Tiedosto, "%s,%d\n", ptr->aSukunimi, ptr->iYhteensa);
        ptr = ptr->pSeuraava;
    }

    //Tiedoston sulkeminen
    fclose(Tiedosto);
    printf("Tiedosto %s kirjoitettu.\n", pKirjoitaTiedostoNimi);
    
}

void kirjoitaTiedostoLopustaAlkuun(char *pNimi, TIEDOT *pAlku)
{
    FILE *Tiedosto = NULL;

    /* Haluaakohan CodeGrade että tämä tarkistetaan _ja_ ohjelman suoritus loppuu?
        vai laitetaanko return :D */

    if (pAlku == NULL){
        printf("Lista on tyhjä, lopetetaan.\n");
        exit(0);
    }
    TIEDOT *ptr = pAlku;

     if ((Tiedosto = fopen(pNimi, "a")) == NULL)
    {
        perror("Tiedoston avaaminen epäonnistui, lopetetaan");
        exit(0);
    }

    // Mennään listan loppuun.
    while (ptr->pSeuraava != NULL){
        ptr=ptr->pSeuraava;
    }

    // Lopusta alkuun, kirjoitetaan tiedostoon.
    while (ptr != NULL){
        fprintf(Tiedosto,"%s,%d\n",ptr->aSukunimi,ptr->iYhteensa);
        ptr=ptr->pEdellinen;
    }

    fclose(Tiedosto);
}