#include "unity.h"
#include "../src/binaaripuu.h"
#include "../src/haut.h"
#include "../src/linkitettylista.h"

void setUp(void) {
    // Tyhja, koska alustetaan muuttujat paikallisesti.
}

void tearDown(void) {
    // Tyhja, koska muisti vapautetaan testeissa.
}

// Testien esittelyt.
void test_VaraaMuistia();
void test_VapautaMuisti();
void test_VaraaMuistiUsealleAlkiolle();

void test_VaraaMuistiaPuulle();
void test_VaraaMuistiaUsealleSolmullePuussa();
void test_VapautaPuunMuisti();
void test_VapautaPuunMuistiUseastaSolmusta();

void test_VaraaMuistiaJonolle();
void test_VapautaMuistiJono();

void test_onkoLuku();
void test_nimenArvo();
void test_poistaSolmuNimi();
void test_poistaSolmuArvo();

void test_VaraaMuistiaRBSolmulle();

void test_lisaaListaan_tyhja();
void test_lisaaListaan_alkuun();
void test_lisaaListaan_indeksilla();

void test_useammalleAlkiolleSamaLKM();
void test_poistaListaLkmPerusteella();
void test_poistaListaNimenPerusteella();

int main(void) {
    UNITY_BEGIN();
    // Tiedot struct testit
    RUN_TEST(test_VaraaMuistia);
    RUN_TEST(test_VapautaMuisti);
    RUN_TEST(test_VaraaMuistiUsealleAlkiolle);

    // Puu structin testit
    RUN_TEST(test_VaraaMuistiaPuulle);
    RUN_TEST(test_VaraaMuistiaUsealleSolmullePuussa);
    RUN_TEST(test_VapautaPuunMuisti);
    RUN_TEST(test_VapautaPuunMuistiUseastaSolmusta);

    // Jono structin testit
    RUN_TEST(test_VaraaMuistiaJonolle);
    RUN_TEST(test_VapautaMuistiJono);

    // Poistoon liittyvät testit
    RUN_TEST(test_onkoLuku);
    RUN_TEST(test_nimenArvo);
    RUN_TEST(test_poistaSolmuNimi);
    RUN_TEST(test_poistaSolmuArvo);

    // RBSolmu structin testit
    RUN_TEST(test_VaraaMuistiaRBSolmulle);

    // Listaan lisaamiseen liittyvat testit.
    RUN_TEST(test_lisaaListaan_tyhja);
    RUN_TEST(test_lisaaListaan_alkuun);
    RUN_TEST(test_lisaaListaan_indeksilla);

    // Listasta poistamiseen liittyvat testit.
    RUN_TEST(test_useammalleAlkiolleSamaLKM);
    RUN_TEST(test_poistaListaLkmPerusteella);
    RUN_TEST(test_poistaListaNimenPerusteella);
    return UNITY_END();
}