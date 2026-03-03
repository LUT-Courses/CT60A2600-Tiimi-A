#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

int main(void) {
    char aNimi[] = "data/sukunimet_2025.txt";
    TIEDOT *pAlku = NULL;
    int iValinta = 0;

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            pAlku = lue(aNimi, pAlku);
        } else if (iValinta == 2) {
    
        } else if (iValinta == 3) {

        } else if (iValinta == 4) {
            pAlku = vapautaMuisti(pAlku);
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
