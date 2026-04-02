#include "../src/binaaripuu.h"
#include "../src/haut.h"
#include "../src/linkitettylista.h"
#include "unity.h"

void setUp(void) {
    // Tyhjä, koska alustetaan muuttujat paikallisesti.
}

void tearDown(void) {
    // Tyhjä, koska muisti vapautetaan testeissä.
}

// Testien esittelyt.
void test_VaraaMuistia();
void test_VapautaMuisti();
void test_VaraaMuistiUsealleAlkiolle();

void test_VaraaMuistiaPuulle();
void test_VaraaMuistiaUsealleSolmullePuussa();
void test_VapautaPuunMuisti();
void test_VapautaPuunMuistiUseastaSolmusta();
void test_LLtasapainotus();
void test_RRtasapainotus();
void test_LRtasapainotus();
void test_RLtasapainotus();

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

void test_lomitusLajitteluTyhjaLista();
void test_lomitusLajitteluYhdellaAlkiolla();
void test_lomitusLajitteluKahdellaAlkiolla();
void test_lomitusLajitteluUseallaAlkiolla();
void test_lomitusLajitteluSamaArvo();

void test_lisaysLajitteluTyhjaLista();
void test_lisaysLajitteluYhdellaAlkiolla();
void test_lisaysLajitteluKahdellaAlkiolla();
void test_lisaysLajitteluUseallaAlkiolla();
void test_lisaysLajitteluSamaArvo();

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
    RUN_TEST(test_LLtasapainotus);
    RUN_TEST(test_RRtasapainotus);
    RUN_TEST(test_LRtasapainotus);
    RUN_TEST(test_RLtasapainotus);

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

    // Listaan lisaamiseen liittyvat testit
    RUN_TEST(test_lisaaListaan_tyhja);
    RUN_TEST(test_lisaaListaan_alkuun);
    RUN_TEST(test_lisaaListaan_indeksilla);

    // Listasta poistamiseen liittyvat testit
    RUN_TEST(test_useammalleAlkiolleSamaLKM);
    RUN_TEST(test_poistaListaLkmPerusteella);
    RUN_TEST(test_poistaListaNimenPerusteella);

    // Lomituslajittelun testit
    RUN_TEST(test_lomitusLajitteluTyhjaLista);
    RUN_TEST(test_lomitusLajitteluYhdellaAlkiolla);
    RUN_TEST(test_lomitusLajitteluKahdellaAlkiolla);
    RUN_TEST(test_lomitusLajitteluUseallaAlkiolla);
    RUN_TEST(test_lomitusLajitteluSamaArvo);

    // Lisäyslajittelun testit
    RUN_TEST(test_lisaysLajitteluTyhjaLista);
    RUN_TEST(test_lisaysLajitteluYhdellaAlkiolla);
    RUN_TEST(test_lisaysLajitteluKahdellaAlkiolla);
    RUN_TEST(test_lisaysLajitteluUseallaAlkiolla);
    RUN_TEST(test_lisaysLajitteluSamaArvo);

    return UNITY_END();
}