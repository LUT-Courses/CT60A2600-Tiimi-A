#include "yleiset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Module.c – Yleisiä aliohjelmia

int valikko(void) {
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

int listaValikko(void) {
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedosto alusta loppuun\n");
    printf("3) Kirjoita tiedosto lopusta alkuun\n");
    printf("4) Tyhjennä taulukko\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

int binaaripuuValikko(void) {
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto:\n");
    printf("1) Luo puu\n");
    printf("2) Kirjoita puu tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Tyhjennä puu\n");
    printf("6) Poista solmu\n");
    printf("7) Binäärihaku\n");
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
