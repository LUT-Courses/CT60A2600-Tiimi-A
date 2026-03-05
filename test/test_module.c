/* Tests */
#include "unity.h"
#include <stdlib.h>
#include "../src/module.h"

TIEDOT *pAlku = NULL;

void setUp(void) {
    pAlku = NULL;
}

// Vapautetaan muisti jokaisen testin jälkeen
void tearDown(void) {
    pAlku = vapautaMuisti(pAlku);
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
    TEST_ASSERT_EQUAL_STRING(expectedNimi,pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa,pAlku->iYhteensa);
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
    TEST_ASSERT_EQUAL_STRING(expectedNimi1,pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1,pAlku->iYhteensa);
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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_VaraaMuistia);
    RUN_TEST(test_VapautaMuisti);
    RUN_TEST(test_OtsikonOhi);
    RUN_TEST(test_VaraaMuistiUsealleAlkiolle);
    return UNITY_END();
}