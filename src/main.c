#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    TIEDOT *pAlku = NULL;
    PUU *pJuuriSolmu = NULL;
    int iValinta = 0;
    int iValinta2 = 0;

    /*
    kysyNimi("Tiedoston nimi ", aNimiLuettava); //SAA POISTAA KUN VALINNAT TOIMIVAT
    pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);//SAA POISTAA KUN VALINNAT TOIMIVAT
    tulostaPuu(pJuuriSolmu);//SAA POISTAA KUN VALINNAT TOIMIVAT
    //pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu); //SAA POISTAA KUN VALINNAT TOIMIVAT
    //pJuuriSolmu = NULL; //SAA POISTAA KUN VALINNAT TOIMIVAT
    */

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
                    if (pAlku == NULL) {
                        printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
                    } else {
                        kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                        kirjoitaTiedostoAlustaLoppuun(aNimiKirjoitettava, pAlku);
                    }
                } else if (iValinta2 == 3) {
                    if (pAlku == NULL) {
                        printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
                    } else {
                        kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                        kirjoitaTiedostoLopustaAlkuun(aNimiKirjoitettava, pAlku);
                    }
                } else if (iValinta2 == 4) {
                    pAlku = vapautaMuisti(pAlku);
                    printf("Muisti vapautettu.\n");
                } else if (iValinta2 == 0) {
                    printf("Mennään takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);
            /* Vapautetaan muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos käyttäjä
             * ei muista sitä tehdä. */
            pAlku = vapautaMuisti(pAlku);

        } else if (iValinta == 2) {
            // Binääripuu
            do {
                iValinta2 = binaaripuuValikko();
                if (iValinta2 == 1) {
                    kysyNimi("Tiedoston nimi ", aNimiLuettava);
                    pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);
                } else if (iValinta2 == 2) {
                    tulostaPuu(pJuuriSolmu);
                } else if (iValinta2 == 3) {
                    /* code */
                } else if (iValinta2 == 4) {
                    /* code */
                } else if (iValinta2 == 5) {
                    /* code */
                }
                if (iValinta2 == 0) {
                    printf("Mennään takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);
            // pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);

        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);
    printf("\n");
    printf("Kiitos ohjelman käytöstä.\n");
    return (0);
}
