#include "../src/punamustapuu.h"
#include "unity.h"

// Onnistuuko varata muistia RBSolmulle?
void test_VaraaMuistiaRBSolmulle() {
    RBSOLMU *pJuuriSolmuRB = NULL;
    char expectedNimi[] = "Kosonen";
    int expectedArvo = 500;

    pJuuriSolmuRB = varaaMuistiaRB(expectedNimi, expectedArvo);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);

    // Pitäisi olla ainut solmu.
    TEST_ASSERT_NULL(pJuuriSolmuRB->pOikea);
    TEST_ASSERT_NULL(pJuuriSolmuRB->pVasen);

    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo, pJuuriSolmuRB->iArvo); 

    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
}