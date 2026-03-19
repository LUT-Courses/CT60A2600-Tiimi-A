#include "binaaripuu.h"
#include "linkitettylista.h"
#include "yleiset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * 13.3.: Main ei enää tee null checkkejä. Johtaa siihen, että kirjoitettavien
 * tiedostojen nimet kysytään turhaan. Onko tämä kuitenkin selkeämpi?
 *
 * Syvyyshaku siistittiin binaaripuu.c sijaitsevalla helper-aliohjelmalla.
 */

int main(void) {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    char aHaettavaNimi[LEN] = "";
    TIEDOT *pAlku = NULL;
    PUU *pJuuriSolmu = NULL;
    int iValinta = 0;
    int iValinta2 = 0;
    int iArvo = 0;

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            // Lista:
            do {
                iValinta2 = listaValikko();
                if (iValinta2 == 1) {
                    kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
                    pAlku = lue(aNimiLuettava, pAlku);
                } else if (iValinta2 == 2) {
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    kirjoitaTiedostoAlustaLoppuun(aNimiKirjoitettava, pAlku);
                } else if (iValinta2 == 3) {
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    kirjoitaTiedostoLopustaAlkuun(aNimiKirjoitettava, pAlku);
                } else if (iValinta2 == 4) {
                    pAlku = vapautaMuisti(pAlku);
                    printf("Muisti vapautettu.\n");
                } else if (iValinta2 == 0) {
                    printf("Palataan takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);

            /* Vapautetaan listan varaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos
             * käyttäjä ei muista sitä tehdä. */
            pAlku = vapautaMuisti(pAlku);
        } else if (iValinta == 2) {
            // Binääripuu
            do {
                iValinta2 = binaaripuuValikko();
                if (iValinta2 == 1) {
                    kysyNimi("Tiedoston nimi: ", aNimiLuettava);
                    pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);
                } else if (iValinta2 == 2) {
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    kirjoitaBinaaripuu(aNimiKirjoitettava, pJuuriSolmu);
                } else if (iValinta2 == 3) {
                    iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    tarkistaLoytyykoSyvyyshaulla(aNimiKirjoitettava, pJuuriSolmu, iArvo);
                } else if (iValinta2 == 4) {
                    kysyNimi("Anna haettava nimi: ", aHaettavaNimi);
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    leveyshaku(aNimiKirjoitettava, pJuuriSolmu, aHaettavaNimi);
                } else if (iValinta2 == 5) {
                    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
                    printf("Muisti vapautettu.\n");
                } else if (iValinta2 == 6) {
                    kysyNimi("Anna poistettava nimi: ", aHaettavaNimi);
                    kysyArvo("Anna poistettavan nimen arvo: ", iArvo);
                    pJuuriSolmu = poistaSolmu(aHaettavaNimi, iArvo, pJuuriSolmu);
                } else if (iValinta2 == 7) {
                    kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                    iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                    binaariHaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);
                } else if (iValinta2 == 0) {
                    printf("Palataan takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);

            /* Vapautetaan puun varaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos
             * käyttäjä ei muista sitä tehdä. */
            pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);

    printf("Kiitos ohjelman käytöstä.\n");
    return (0);
}