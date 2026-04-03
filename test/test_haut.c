#include "unity.h"
#include "../src/haut.h"
#include <stdlib.h>

// Onnistuuko muistin varaaminen jonolle?
void test_VaraaMuistiaJonolle(void) {
    PUU *pSolmu1 = NULL;
    PUU *pSolmu2 = NULL;
    JONO *pJono1 = NULL;
    JONO *pJono2 = NULL;

    char expectedNimi1[LEN] = "Kosonen";
    char expectedNimi2[LEN] = "Karjalainen";
    int expectedArvo1 = 4465;
    int expectedArvo2 = 11900;

    pSolmu1 = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);
    pJono1 = varaaMuistiaJonolle(pSolmu1);
    TEST_ASSERT_NOT_NULL(pJono1);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJono1->pSolmu->aNimi);

    pSolmu2 = varaaMuistiaPuulle(expectedNimi2, expectedArvo2);
    pJono2 = varaaMuistiaJonolle(pSolmu2);
    TEST_ASSERT_NOT_NULL(pJono2);
    TEST_ASSERT_EQUAL_INT(11900, pJono2->pSolmu->iArvo);

    free(pJono1);
    free(pJono2);
    free(pSolmu1);
    free(pSolmu2);
    return;
}

// Testataan, toimiiko jonon muistin vapautus.
void test_VapautaMuistiJono(void) {
    PUU *pSolmu1 = NULL;
    PUU *pSolmu2 = NULL;
    JONO *pJono1 = NULL;
    JONO *pJono2 = NULL;

    char expectedNimi1[LEN] = "Kosonen";
    char expectedNimi2[LEN] = "Karjalainen";
    int expectedArvo1 = 4465;
    int expectedArvo2 = 11900;

    pSolmu1 = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);
    pSolmu2 = varaaMuistiaPuulle(expectedNimi2, expectedArvo2);

    pJono1 = varaaMuistiaJonolle(pSolmu1);
    pJono2 = varaaMuistiaJonolle(pSolmu2);

    pJono1 = vapautaMuistiJono(pJono1);
    TEST_ASSERT_NULL(pJono1);

    pJono2 = vapautaMuistiJono(pJono2);
    TEST_ASSERT_NULL(pJono2);

    free(pSolmu1);
    free(pSolmu2);
    return;
}