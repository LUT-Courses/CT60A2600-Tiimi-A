#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

int main(void) {
    //char aNimi[] = "data/sukunimet_2025.txt";
    char aNimi[40] = "";
    TIEDOT *pAlku = NULL;
    int iValinta = 0;
    char pKirjoitusTiedosto[50] = "";

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            kysyLuettavaTiedosto(aNimi);
            pAlku = lue(aNimi, pAlku);
        } else if (iValinta == 2) {
            kysyKirjoitettavaTiedosto(pKirjoitusTiedosto);
            kirjoitaTiedostoAlustaLoppuun(pKirjoitusTiedosto, pAlku);
        } else if (iValinta == 3) {
            kysyKirjoitettavaTiedosto(pKirjoitusTiedosto);
        } else if (iValinta == 4) {
            pAlku = vapautaMuisti(pAlku);
            printf("Muisti vapautettu.\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
    } while (iValinta != 0);
    /* En tiedä onko turha, mutta varmuuden vuoksi vielä täällä lopussa erikseen. */
    pAlku = vapautaMuisti(pAlku);
    return(0);
}
