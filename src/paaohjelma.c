#include "binaaripuu.h"
#include "linkitettylista.h"
#include "yleiset.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * @brief Paaohjelma, pyorittaa koko ohjelmaa.
 *
 * @return int Palauttaa aina 0, kun ohjelma tulee päätökseen.
 */
int main(void) {
    int iValinta = 0;

    do {
        iValinta = valikko();
        if (iValinta == 1) {
            mainLista();
        } else if (iValinta == 2) {
            mainBinaaripuu();
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
