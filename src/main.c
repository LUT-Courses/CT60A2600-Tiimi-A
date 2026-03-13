#include "module.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    char aHaettavaNimi[LEN] = "";
    TIEDOT *pAlku = NULL;
    PUU *pJuuriSolmu = NULL;
    int iValinta = 0;
    int iValinta2 = 0;
    int iArvo = 0;
    int iLoytyi = 0;

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
                    printf("Palataan takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);

            /* Vapautetaan listan varaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos käyttäjä
             * ei muista sitä tehdä. */
            pAlku = vapautaMuisti(pAlku);

        } else if (iValinta == 2) {
            // Binääripuu
            do {
                iValinta2 = binaaripuuValikko();
                if (iValinta2 == 1) {
                    kysyNimi("Tiedoston nimi: ", aNimiLuettava);
                    pJuuriSolmu = luoPuu(aNimiLuettava, pJuuriSolmu);
                } else if (iValinta2 == 2) {
                    if (pJuuriSolmu == NULL) {
                        printf("Puu on tyhjä, luo puurakenne ennen kirjoittamista.\n");
                    } else {
                        kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                        kirjoitaBinaaripuu(aNimiKirjoitettava, pJuuriSolmu);
                    }
                } else if (iValinta2 == 3) {
                    if (pJuuriSolmu == NULL) {
                        printf("Puu on tyhjä, luo puurakenne ennen syvyyshakua.\n");
                    } else {
                        iArvo = kysyArvo("Anna haettava numeroarvo: ", iArvo);
                        kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                        iLoytyi = syvyyshaku(aNimiKirjoitettava, pJuuriSolmu, iArvo);

                        if (iLoytyi == 0) {
                            printf("Arvoa %d ei löytynyt puusta.\n", iArvo);
                        }
                        printf("Tiedosto '%s' kirjoitettu.\n", aNimiKirjoitettava);
                    }
                } else if (iValinta2 == 4) {
                    if (pJuuriSolmu == NULL) {
                        printf("Puu on tyhjä, luo puurakenne ennen leveyshakua.\n");
                    } else {
                        kysyNimi("Anna haettava nimi: ", aHaettavaNimi);
                        kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                        leveyshaku(aNimiKirjoitettava, pJuuriSolmu, aHaettavaNimi);
                        printf("Tiedosto '%s' kirjoitettu.\n", aNimiKirjoitettava);
                    }
                } else if (iValinta2 == 5) {
                    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
                    printf("Muisti vapautettu.\n");
                } else if (iValinta2 == 0) {
                    printf("Palataan takaisin päävalikkoon.\n");
                } else {
                    printf("Tuntematon valinta, yritä uudestaan.\n");
                }
            } while (iValinta2 != 0);

            /* Vapautetaan puun varaaama muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos käyttäjä
             * ei muista sitä tehdä. */
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
