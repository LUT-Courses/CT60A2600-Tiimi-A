#include "yleiset.h"
#include "linkitettylista.h"
#include "binaaripuu.h"
#include "haut.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Yleisiä aliohjelmia

void mainLista() {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    int iValinta = 0;
    TIEDOT *pAlku = NULL;

    do {
        iValinta = listaValikko();
        if (iValinta == 1) {
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            pAlku = lue(aNimiLuettava, pAlku);

        } else if (iValinta == 2) {
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoAlustaLoppuun(aNimiKirjoitettava, pAlku);
            }

        } else if (iValinta == 3) {
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoLopustaAlkuun(aNimiKirjoitettava, pAlku);
            }
            
        } else if (iValinta == 4) {
            pAlku = vapautaMuisti(pAlku);
            printf("Muisti vapautettu.\n");

        } else if (iValinta == 0) {
            printf("Palataan takaisin päävalikkoon.\n");

        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    } while (iValinta != 0);

    /* Vapautetaan listan varaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos
        * käyttäjä ei muista sitä tehdä. */
    pAlku = vapautaMuisti(pAlku);
    return;
}

void mainBinaaripuu() {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    char aHaettavaNimi[LEN] = "";
    PUU *pJuuriSolmu = NULL;
    RBSOLMU *pRBJuuri = NULL;
    int iValinta = 0;
    int iArvo = 0;

    do {
        iValinta = binaaripuuValikko();
        if (iValinta == 1) {
            kysyNimi("Tiedoston nimi: ", aNimiLuettava);
            pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);

        } else if (iValinta == 2) {
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen sen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaBinaaripuu(aNimiKirjoitettava, pJuuriSolmu);
            }

        } else if (iValinta == 3) {
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen syvyyshakua.\n");
            } else {
                iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                tarkistaLoytyykoSyvyyshaulla(aNimiKirjoitettava, pJuuriSolmu, iArvo);
            }

        } else if (iValinta == 4) {
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen leveyshakua.\n");
            } else {
                kysyNimi("Anna haettava nimi: ", aHaettavaNimi);
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                leveyshaku(aNimiKirjoitettava, pJuuriSolmu, aHaettavaNimi);
            }

        } else if (iValinta == 5) {
            pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
            printf("Muisti vapautettu.\n");

        } else if (iValinta == 6) {
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen poistoa.\n");
            } else {
                kysyNimi("Anna poistettava nimi tai arvo: ", aHaettavaNimi);
                pJuuriSolmu = poistaSolmu(aHaettavaNimi, pJuuriSolmu);
            }

        } else if (iValinta == 7) {
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen binäärihakua.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                binaariHaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);
            }

        } else if (iValinta == 8) {
            // Aino säätää ja testaa
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
            pRBJuuri = luoRBPuu(pRBJuuri, aNimiLuettava);
            kirjoitaRB(aNimiKirjoitettava, pRBJuuri);
            pRBJuuri = vapautaMuistiRB(pRBJuuri);

        } else if (iValinta == 0) {
            printf("Palataan takaisin päävalikkoon.\n");

        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    } while (iValinta != 0);

    /* Vapautetaan puun varaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos
        * käyttäjä ei muista sitä tehdä. */
    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}


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
    printf("2) Kirjoita AVL puu tiedostoon\n");
    printf("3) Syvyyshaku\n");
    printf("4) Leveyshaku\n");
    printf("5) Tyhjennä puu\n");
    printf("6) Poista solmu\n");
    printf("7) Binäärihaku AVL puusta\n");
    printf("8) Punamustapuu\n");
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

/**
 * @brief Kysyy arvon, joka halutaan etsia/poistaa puusta
 * 
 * @param pPrompti Kysymys esim. "Anna haettava numeroarvo: "
 * @param iArvo Arvo, joka halutaan poistaa/etsiä
 * @return int Palauttaa kayttajan antaman arvon
 */

int kysyArvo(char *pPrompti, int iArvo) {
    printf("%s", pPrompti);
    scanf("%d", &iArvo);
    getchar();
    return (iArvo);
}
