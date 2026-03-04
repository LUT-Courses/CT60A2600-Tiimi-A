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

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_VaraaMuistia);
    RUN_TEST(test_VapautaMuisti);
    return UNITY_END();
}