#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "module.h"

int main(void) {
    char aNimiLuettava[LEN] = "";
    char aNimiKirjoitettava[LEN] = "";
    TIEDOT *pAlku = NULL;
    int iValinta = 0;

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            kysyNimi("Anna luettavan tiedoston nimi: ", aNimiLuettava);
            pAlku = lue(aNimiLuettava, pAlku);
        } else if (iValinta == 2) {
            if (pAlku == NULL){
                printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoAlustaLoppuun(aNimiKirjoitettava, pAlku);
            }
        } else if (iValinta == 3) {
            if (pAlku == NULL){
                printf("Lista on tyhjä, lue tiedosto ennen kirjoittamista.\n");
            } else {
                kysyNimi("Anna kirjoitettavan tiedoston nimi: ", aNimiKirjoitettava);
                kirjoitaTiedostoLopustaAlkuun(aNimiKirjoitettava, pAlku);
            }
        } else if (iValinta == 4) {
            pAlku = vapautaMuisti(pAlku);
            printf("Muisti vapautettu.\n");
        } else if (iValinta == 0) {
            printf("Lopetetaan.\n");
        } else {
            printf("Tuntematon valinta, yritä uudestaan.\n");
        }
        printf("\n");
    } while (iValinta != 0);
    /* Vapautetaan muisti varmuuden vuoksi vielä täällä lopussa erikseen, jos käyttäjä ei muista sitä tehdä. */
    pAlku = vapautaMuisti(pAlku);
    printf("Kiitos ohjelman käytöstä.\n");
    return(0);
}
