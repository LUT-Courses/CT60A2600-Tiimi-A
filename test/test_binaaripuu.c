// 15.3.2026 Sofia Toropainen, Ainö Pöyhönen, Noora Vepsäläinen, test_binaaripuu.c, binaaripuu.c aliohjelmien testit, tiedostoa muokattu myöhemmin ja testejä lisätty.
#include "unity.h"
#include "../src/binaaripuu.h"


// Onnistuuko muistin varaaminen puulle, kun se on tyhjä?
void test_VaraaMuistiaPuulle(void) {
    PUU *pJuuriSolmu = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedArvo = 500;

    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi, expectedArvo);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu);

    // Pitäisi olla ainut solmu.
    TEST_ASSERT_NULL(pJuuriSolmu->pVasen);
    TEST_ASSERT_NULL(pJuuriSolmu->pOikea);

    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pJuuriSolmu->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo, pJuuriSolmu->iArvo);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Onnistuuko muistinvaraus useammalle solmulle puussa, kun se on tyhjä?
void test_VaraaMuistiaUsealleSolmullePuussa(void) {
    PUU *pJuuriSolmu = NULL;
    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "Gekko";
    int expectedArvo2 = 345;
    char expectedNimi3[] = "Karjalainen";
    int expectedArvo3 = 600;

    // Varataan muistia ensimmäiselle solmulle.
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, expectedNimi1, expectedArvo1);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);
    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJuuriSolmu->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pJuuriSolmu->iArvo);

    // Varataan muistia toiselle solmulle.
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, expectedNimi2, expectedArvo2);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);

    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pJuuriSolmu->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pJuuriSolmu->pVasen->iArvo);

    // Varataan muistia kolmannelle solmulle.
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, expectedNimi3, expectedArvo3);
    TEST_ASSERT_NOT_NULL(pJuuriSolmu->aNimi);
    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pJuuriSolmu->pOikea->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pJuuriSolmu->pOikea->iArvo);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Onnistuuko puun muistin vapauttaminen?
void test_VapautaPuunMuisti(void) {
    PUU *pJuuriSolmu = NULL;
    // Varataan muistia.
    pJuuriSolmu = varaaMuistiaPuulle("Kosonen", 500);

    // Vapautetaan muisti.
    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    // Tarkistetaan, onko vapautus onnistunut.
    TEST_ASSERT_NULL(pJuuriSolmu);
    return;
}

// Onnistuuko puun muistin vapauttaminen usealla alkiolla?
void test_VapautaPuunMuistiUseastaSolmusta(void) {
    PUU *pJuuriSolmu = NULL;
    // Varataan muistia
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Kosonen", 500);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Gekko", 560);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Karjalainen", 245);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Suomalainen", 4);

    // Vapautetaan muisti.
    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);

    // Tarkistetaan, onnistuiko vapautus.
    TEST_ASSERT_NULL(pJuuriSolmu);
    return;
}

// Onnistuuko vasen-vasen tasapainotus?
void test_LLtasapainotus(void) {
    PUU *pJuuriSolmu = NULL;
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Kosonen", 500);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Gekko", 400);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Karjalainen", 300);
    
    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->aNimi, "Gekko");
    TEST_ASSERT_EQUAL_INT(pJuuriSolmu->iArvo, 400);

    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->pOikea->aNimi, "Kosonen");

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Onnistuuko oikea-oikea tasapainotus?
void test_RRtasapainotus(void) {
    PUU *pJuuriSolmu = NULL;
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Kosonen", 500);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Gekko", 600);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Karjalainen", 700);
    
    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->aNimi, "Gekko");
    TEST_ASSERT_EQUAL_INT(pJuuriSolmu->iArvo, 600);

    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->pOikea->aNimi, "Karjalainen");
    TEST_ASSERT_NULL(pJuuriSolmu->pOikea->pOikea->aNimi);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Onnistuuko vasen-oikea tasapainotus?
void test_LRtasapainotus(void) {
    PUU *pJuuriSolmu = NULL;
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Kosonen", 500);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Gekko", 300);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Karjalainen", 400);
    
    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->aNimi, "Karjalainen");
    TEST_ASSERT_EQUAL_INT(pJuuriSolmu->iArvo, 400);

    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->pOikea->aNimi, "Kosonen");
    TEST_ASSERT_NULL(pJuuriSolmu->pOikea->pOikea->aNimi);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Onnistuuko oikea-vasen tasapainotus?
void test_RLtasapainotus(void) {
    PUU *pJuuriSolmu = NULL;
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Kosonen", 300);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Gekko", 500);
    pJuuriSolmu = lisaaSolmu(pJuuriSolmu, "Karjalainen", 400);
    
    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->aNimi, "Karjalainen");
    TEST_ASSERT_EQUAL_INT(pJuuriSolmu->iArvo, 400);

    TEST_ASSERT_EQUAL_STRING(pJuuriSolmu->pOikea->aNimi, "Gekko");
    TEST_ASSERT_NULL(pJuuriSolmu->pOikea->pOikea->aNimi);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Testataan, toimiiko lukuarvon tarkistus.
void test_onkoLuku(void) {
    char aLuku1[] = "50";
    char aLuku2[] = "abc";

    TEST_ASSERT_EQUAL_INT(1, onkoLuku(aLuku1));
    TEST_ASSERT_EQUAL_INT(0, onkoLuku(aLuku2));
    return;
}

// Testataan, löytyykö nimen avulla arvoa.
void test_nimenArvo(void) {
    PUU *pJuuriSolmu = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;

    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);

    TEST_ASSERT_EQUAL(500, nimenArvo("Kosonen", pJuuriSolmu));
    TEST_ASSERT_EQUAL(0, nimenArvo("Karjalainen", pJuuriSolmu));

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Testataan, poistuuko solmu nimellä.
void test_poistaSolmuNimi(void) {
    PUU *pJuuriSolmu = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;

    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);

    pJuuriSolmu = poistaSolmu(expectedNimi1, pJuuriSolmu);

    TEST_ASSERT_NULL(pJuuriSolmu);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}

// Testataan solmun poistamista arvolla.
void test_poistaSolmuArvo(void) {
    PUU *pJuuriSolmu = NULL;

    char expectedNimi1[] = "Kosonen";
    char aExpectedArvo[] = "500";
    int expectedArvo1 = 500;

    pJuuriSolmu = varaaMuistiaPuulle(expectedNimi1, expectedArvo1);

    pJuuriSolmu = poistaSolmu(aExpectedArvo, pJuuriSolmu);

    TEST_ASSERT_NULL(pJuuriSolmu);

    pJuuriSolmu = vapautaMuistiPuu(pJuuriSolmu);
    return;
}