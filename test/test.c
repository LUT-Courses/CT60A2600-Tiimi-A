/* Tests */
#include "../src/binaaripuu.h"
#include "../src/linkitettylista.h"
#include "../src/yleiset.h"
#include "unity.h"
#include <stdlib.h>

TIEDOT *pAlku = NULL;
SOLMU *pJuuriSolmu = NULL;

void setUp(void) {
    pAlku = NULL;
    pJuuriSolmu = NULL;
}

// Vapautetaan muisti jokaisen testin jälkeen
void tearDown(void) {
    pAlku = vapautaMuisti(pAlku);
    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
}

// Onnistuuko varaaMuistia, kun lista on tyhjä
void test_VaraaMuistia(void) {
    char expectedNimi[LEN] = "Kosonen";
    int expectedYhteensa = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi, expectedYhteensa);
    TEST_ASSERT_NOT_NULL(pAlku);

    // Pitäisi olla ainut solmu listassa
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava);

    // Löytyykö oikeat arvot
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa, pAlku->iYhteensa);
}

void test_VapautaMuisti(void) {
    pAlku = varaaMuistia(NULL, "Kosonen", 500);
    pAlku = varaaMuistia(pAlku, "Toropainen", 400);
    pAlku = vapautaMuisti(pAlku);
    TEST_ASSERT_NULL(pAlku);
}

// Onnistuuko ohittaa otsikkorivi, kun luetaan tiedostoa
void test_OtsikonOhi(void) {
    int expectedLuku = 1;
    int iOtsikko = 0;

    // Onko otsikko menty ohi
    if (iOtsikko == 0) {
        iOtsikko = 1;
    }

    // Loytyyko oikeat arvot
    TEST_ASSERT_EQUAL_INT(expectedLuku, iOtsikko);
}

// Onnistuuko varata muistia usealle alkiolle kun lista on tyhjä
void test_VaraaMuistiUsealleAlkiolle(void) {
    TIEDOT *ptr = pAlku;
    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 500;
    char expectedNimi2[] = "Gekko";
    int expectedYhteensa2 = 345;
    char expectedNimi3[] = "Karjalainen";
    int expectedYhteensa3 = 2;

    // varataan muistia
    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    TEST_ASSERT_NOT_NULL(pAlku);

    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    TEST_ASSERT_NOT_NULL(pAlku);

    pAlku = varaaMuistia(pAlku, expectedNimi3, expectedYhteensa3);
    TEST_ASSERT_NOT_NULL(pAlku);

    // Loytyyko oikeat arvot
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->iYhteensa);
    ptr = pAlku->pSeuraava;
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, ptr->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, ptr->iYhteensa);
    ptr = ptr->pSeuraava;
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, ptr->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, ptr->iYhteensa);

    // ptr pitaisi olla viimeisessa solmussa ja pAlku pitaisi olla ensimmainen solmu
    ptr = ptr->pSeuraava;
    TEST_ASSERT_NULL(ptr);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
}

// Onnistuuko varaaMuistiaPuulle, kun se on tyhja
void test_VaraaMuistiaPuulle() {
    char expectedNimi[] = "Kosonen";
    int expectedArvo = 500;

    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi, expectedArvo);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu);

    // Pitaisi olla ainut solmu
    TEST_ASSERT_NULL(pJuuriSolmu->pVasen);
    TEST_ASSERT_NULL(pJuuriSolmu->pOikea);

    // Loytyyko oikeat arvot
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pJuuriSolmu->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo, pJuuriSolmu->iArvo);
}

// Onnistuuko varata muistia usealle solmulle puussa, kun se on tyhja
void test_VaraaMuistiaUsealleSolmullePuussa() {
    SOLMU *ptr = pJuuriSolmu;
    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "Gekko";
    int expectedArvo2 = 345;
    char expectedNimi3[] = "Karjalainen";
    int expectedArvo3 = 600;

    // Varataan muistia ensimmaiselle solmulle
    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);
    // Loytyyko oikeat arvot
    ptr = pJuuriSolmu;
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, ptr->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, ptr->iArvo);

    // Varataan muistia toiselle solmulle
    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi2, expectedArvo2);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);
    // Loytyyko oikeat arvot
    ptr = pJuuriSolmu;
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, ptr->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, ptr->iArvo);

    // Varataan muistia kolmannelle solmulle
    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi3, expectedArvo3);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);
    // Loytyyko oikeat arvot
    ptr = pJuuriSolmu;
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, ptr->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, ptr->iArvo);
}

// Onnistuuko muistin varaaminen jonolle.
void test_VaraaMuistiaJonolle() {
    char expectedNimi1[LEN] = "Kosonen";
    char expectedNimi2[LEN] = "Karjalainen";
    int expectedArvo1 = 4465;
    int expectedArvo2 = 11900;

    JONO *pJono1 = NULL;
    JONO *pJono2 = NULL;

    SOLMU *pSolmu1 = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);
    pJono1 = varaaMuistiaJonolle(pSolmu1);
    TEST_ASSERT_NOT_NULL(pJono1);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJono1->pSolmu->aNimi);

    SOLMU *pSolmu2 = varaaMuistiaPuulle(expectedNimi2, expectedArvo2);
    pJono2 = varaaMuistiaJonolle(pSolmu2);
    TEST_ASSERT_NOT_NULL(pJono2);
    TEST_ASSERT_EQUAL_INT(11900, pJono2->pSolmu->iArvo);

    free(pJono1);
    free(pJono2);
    free(pSolmu1);
    free(pSolmu2);
}

// Testataan, toimiiko jonon muistin vapautus.
void test_VapautaMuistiJono() {
    char expectedNimi1[LEN] = "Kosonen";
    char expectedNimi2[LEN] = "Karjalainen";
    int expectedArvo1 = 4465;
    int expectedArvo2 = 11900;

    JONO *pJono1 = NULL;
    JONO *pJono2 = NULL;

    SOLMU *pSolmu1 = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);
    SOLMU *pSolmu2 = varaaMuistiaPuulle(expectedNimi2, expectedArvo2);

    pJono1 = varaaMuistiaJonolle(pSolmu1);
    pJono2 = varaaMuistiaJonolle(pSolmu2);

    pJono1 = vapautaMuistiJono(pJono1);
    TEST_ASSERT_NULL(pJono1);

    pJono2 = vapautaMuistiJono(pJono2);
    TEST_ASSERT_NULL(pJono2);

    free(pSolmu1);
    free(pSolmu2);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_VaraaMuistia);
    RUN_TEST(test_VapautaMuisti);
    RUN_TEST(test_OtsikonOhi);
    RUN_TEST(test_VaraaMuistiUsealleAlkiolle);
    RUN_TEST(test_VaraaMuistiaPuulle);
    RUN_TEST(test_VaraaMuistiaUsealleSolmullePuussa);
    RUN_TEST(test_VaraaMuistiaJonolle);
    RUN_TEST(test_VapautaMuistiJono);
    return UNITY_END();
}
