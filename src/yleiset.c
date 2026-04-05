#include "yleiset.h"
#include "binaaripuu.h"
#include "haut.h"
#include "linkitettylista.h"
#include "punamustapuu.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Yleisiä ja usein käytettyjä aliohjelmia.

/**
 * @brief Tekee käyttäjän valinnan perusteella listan toiminnot.
 *
 * Funktio näyttää valikon ja suorittaa käyttäjän valinnan mukaiset
 * listaan liittyvät toiminnot.
 */
void mainLista(void) {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    char aTietoPoistettava[LEN] = "";
    int iArvo = 0;
    int iIndeksi = 0;
    int iValinta = 0;
    TIEDOT *pAlku = NULL;

    do {
        iValinta = listaValikko();
        if (iValinta == 1) {
            // Lukee tiedoston.
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            pAlku = lue(aNimiLuettava, pAlku);

        } else if (iValinta == 2) {
            // Kirjoittaa tiedoston alusta loppuun.
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoAlustaLoppuun(aNimiKirjoitettava, pAlku);
            }

        } else if (iValinta == 3) {
            // Kirjoittaa tiedoston lopusta alkuun.
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoLopustaAlkuun(aNimiKirjoitettava, pAlku);
            }

        } else if (iValinta == 4) {
            // Vapauttaa muistin.
            pAlku = vapautaMuisti(pAlku);
            printf("Muisti vapautettu.\n");

        } else if (iValinta == 5) {
            // Lajittelee listan nousevasti lomistuslajittelulla.
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen lajittelua.\n");
            } else {
                pAlku = lomitusLajittelu(pAlku);
                printf("Numerot lajiteltu nousevasti.\n");
            }

        } else if (iValinta == 6) {
            // Lajittelee listan laskevasti lisäyslajittelulla.
            if (pAlku == NULL) {
                printf("Lue tiedosto ennen lajittelua.\n");
            } else {
                pAlku = lisaysLajittelu(pAlku);
                printf("Numerot lajiteltu laskevasti.\n");
            }

        } else if (iValinta == 7) {
            // Lisää tietoja listaan.
            iIndeksi = kysyArvo("Mille riville haluat lisätä tietoja: ", iIndeksi);
            kysyNimi("Anna lisättävä nimi: ", aNimiKirjoitettava);
            iArvo = kysyArvo("Anna tämän nimisten lukumäärä: ", iArvo);
            pAlku = lisaaListaan(pAlku, iIndeksi, aNimiKirjoitettava, iArvo);

        } else if (iValinta == 8) {
            // Poistaminen listalta.
            if (pAlku == NULL) {
                printf("Lista on tyhjä, ei poistettavia alkioita.\n");
            } else {
                kysyNimi("Anna poistettava nimi tai arvo: ", aTietoPoistettava);
                iArvo = onkoLukuVaiNimi(aTietoPoistettava);
                pAlku = poistaListastaAlkio(pAlku, iArvo, aTietoPoistettava);
            }

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

/**
 * @brief Tekee käyttäjän valinnan perusteella binääripuun toiminnot.
 *
 * Funktio näyttää valikon ja suorittaa käyttäjän valinnan mukaiset
 * binääripuuhun liittyvät toiminnot.
 */
void mainBinaaripuu(void) {
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
            // Luo AVL puun.
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);

        } else if (iValinta == 2) {
            // Kirjoittaa AVL puun tiedostoon.
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen sen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaBinaaripuu(aNimiKirjoitettava, pJuuriSolmu);
            }

        } else if (iValinta == 3) {
            // Syvyyshaku binääripuulle.
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen syvyyshakua.\n");
            } else {
                iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                tarkistaLoytyykoSyvyyshaulla(aNimiKirjoitettava, pJuuriSolmu, iArvo);
            }

        } else if (iValinta == 4) {
            // Leveyshaku binääripuulle.
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen leveyshakua.\n");
            } else {
                kysyNimi("Anna haettava nimi: ", aHaettavaNimi);
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                leveyshaku(aNimiKirjoitettava, pJuuriSolmu, aHaettavaNimi);
            }

        } else if (iValinta == 5) {
            // Vapauttaa muistin.
            pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
            printf("Muisti vapautettu.\n");

        } else if (iValinta == 6) {
            // Poistaa solmun binääripuusta.
            if (pJuuriSolmu == NULL) {
                printf("Luo binääripuu ennen poistoa.\n");
            } else {
                kysyNimi("Anna poistettava nimi tai arvo: ", aHaettavaNimi);
                pJuuriSolmu = poistaSolmu(aHaettavaNimi, pJuuriSolmu);
            }

        } else if (iValinta == 7) {
            // Binäärihaku
            if (pJuuriSolmu == NULL) {
                printf("Binääripuu on tyhjä, ei poistettavia alkioita.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                iArvo = binaarihaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);
                if (iArvo == 0) {
                    printf("Hakemaasi arvoa ei löytynyt binääripuusta.\n");
                }
            }

        } else if (iValinta == 8) {
            // Toteuttaa punamustapuun.
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
            pRBJuuri = luoRBPuu(pRBJuuri, aNimiLuettava);
            kirjoitaRB(aNimiKirjoitettava, pRBJuuri);
            printf("Tiedosto '%s' kirjoitettu.\n", aNimiKirjoitettava);
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

/**
 * @brief Ensimmäinen valikko, jossa käyttäjä valitsee listan tai binääripuun.
 *
 * @param iValinta Käyttäjän antama syöte.
 * @return int Palauttaa kayttäjän valinnan.
 */
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

/**
 * @brief Tulostaa lista valikon ja kysyy käyttäjän valinnan.
 *
 * @param iValinta Käyttäjän antama syöte vaihtoehtojen pohjalta.
 * @return int Palauttaa käyttäjän valinnan.
 */
int listaValikko(void) {
    int iValinta = 0;
    printf("\nValitse haluamasi toiminto:\n");
    printf("1) Lue tiedosto\n");
    printf("2) Kirjoita tiedosto alusta loppuun\n");
    printf("3) Kirjoita tiedosto lopusta alkuun\n");
    printf("4) Tyhjennä taulukko\n");
    printf("5) Lajittele nousevasti\n");
    printf("6) Lajittele laskevasti\n");
    printf("7) Lisää tietoja listaan\n");
    printf("8) Poista listalta tietoja\n");
    printf("0) Takaisin\n");
    printf("Anna valintasi: ");
    scanf("%d", &iValinta);
    getchar();
    return iValinta;
}

/**
 * @brief Tulostaa binääriluku valikon ja kysyy käyttäjältä valinnan.
 *
 * @param iValinta Käyttäjän antama syöte vaihtoehtojen pohjalta.
 * @return int Palauttaa käyttäjän valinnan.
 */
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

/**
 * @brief Kysyy tiedoston/haettavan nimen.
 *
 * @param pPrompti Kysymys esim. "Anna kirjoitettavan tiedoston nimi: "
 * @param pNimi Tiedoston nimi/haettava nimi, jota halutaan käyttää.
 * @return char Palauttaa käyttäjän antaman merkkijonon.
 */
char *kysyNimi(char *pPrompti, char *pNimi) {
    printf("%s", pPrompti);
    scanf("%s", pNimi);
    getchar();
    return (pNimi);
}

/**
 * @brief Kysyy arvon, joka halutaan etsia/poistaa puusta.
 *
 * @param pPrompti Kysymys esim. "Anna haettava numeroarvo: "
 * @param iArvo Arvo, joka halutaan poistaa/etsiä.
 * @return int Palauttaa käyttäjän antaman arvon.
 */
int kysyArvo(char *pPrompti, int iArvo) {
    printf("%s", pPrompti);
    scanf("%d", &iArvo);
    getchar();
    return (iArvo);
}
