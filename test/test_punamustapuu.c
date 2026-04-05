// 29.3.2026 Sofia Toropainen, Ainö Pöyhönen, Noora Vepsäläinen, test_punamustapuu.c, punamustapuu.c aliohjelmien testit, tiedostoa muokattu myöhemmin ja testejä lisätty.
#include "../src/punamustapuu.h"
#include "unity.h"

// Onnistuuko varata muistia RBSolmulle?
void test_VaraaMuistiaRBSolmulle(void) {
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
    return;
}

// Onnistuuko varata muistia usealle RBSolmulle?
void test_VaraaMuistiaUsealleRBSolmulle(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pUusi = NULL;
    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "Gekko";
    int expectedArvo2 = 345;
    char expectedNimi3[] = "Karjalainen";
    int expectedArvo3 = 600;

    // Lisätään ensimmäinen solmu
    pUusi = varaaMuistiaRB(expectedNimi1, expectedArvo1);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    // Löytyykö oikeat arvot, eikä puu ole tyhjä?
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pJuuriSolmuRB->iArvo); 


    // Lisätään toinen solmu
    pUusi = varaaMuistiaRB(expectedNimi2, expectedArvo2);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    // Löytyykö oikeat arvot ja että puussa on kaksi solmua?
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pVasen);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pJuuriSolmuRB->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pJuuriSolmuRB->pVasen->iArvo);


    // Lisätään kolmas solmu
    pUusi = varaaMuistiaRB(expectedNimi3, expectedArvo3);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

     // Löytyykö oikeat arvot ja että puussa on kaksi solmua?
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pVasen);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pOikea);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pJuuriSolmuRB->pOikea->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pJuuriSolmuRB->pOikea->iArvo);


    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
    return;
}

// Onnistuuko punamustapuun muistin vapauttaminen?
void test_VapautaRBMuisti(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;

    // Varataan muistia.
    pJuuriSolmuRB = varaaMuistiaRB("Kosonen", 500);

    // Vapautetaan muisti.
    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);

    // Tarkistetaan, onko vapautus onnistunut.
    TEST_ASSERT_NULL(pJuuriSolmuRB);

    return;
}

// Onnistuuko puun muistin vapauttaminen usealla alkiolla?
void test_VapautaRBMuistiUseastaSolmusta(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pUusi = NULL;

    // Varataan muistia.
    pUusi = varaaMuistiaRB("Kosonen", 500);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    pUusi = varaaMuistiaRB("Gekko", 345);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    pUusi = varaaMuistiaRB("Karjalainen", 600);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    // Vapautetaan muisti.
    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);

    // Tarkistetaan, onnistuiko vapautus.
    TEST_ASSERT_NULL(pJuuriSolmuRB);

    return;
}

// Toimiiko lisäyksen korjaus, jos puuta ei tarvitse korjata?
void test_RBlisayksenKorjaus(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pUusi = NULL;
    
    // Lisätään ensimmäinen solmu.
    pUusi = varaaMuistiaRB("Kosonen", 500);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    //Lisätään toinen solmu.
    pUusi = varaaMuistiaRB("Gekko", 345);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);


    // Ensimmäisenä lisätyn solmun pitäisi olla juurisolmu ja toisena lisätyn solmun pitäisi olla vasen solmu.
    // Tarkistetaan löytyykö puusta juurisolmu ja vasen solmu.
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pVasen);

    // Tarkitetaan, onko solmut oikein.
    TEST_ASSERT_EQUAL_STRING("Kosonen", pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(500, pJuuriSolmuRB->iArvo);
    TEST_ASSERT_EQUAL_STRING("Gekko", pJuuriSolmuRB->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(345, pJuuriSolmuRB->pVasen->iArvo);

    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
    return;
}

// Toimiiko lisäyksen korjaus, jos puuta tarvitsee korjata?
void test_RBLisayksenKorjausSolmujenPaikatVaihtuu(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pUusi = NULL;
    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "Gekko";
    int expectedArvo2 = 400;
    char expectedNimi3[] = "Karjalainen";
    int expectedArvo3 = 300;

    // Lisätään solmut.
    pUusi = varaaMuistiaRB(expectedNimi1, expectedArvo1);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi); 

    pUusi = varaaMuistiaRB(expectedNimi2, expectedArvo2);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    pUusi = varaaMuistiaRB(expectedNimi3, expectedArvo3);
    pJuuriSolmuRB = lisaaRBSolmu(pJuuriSolmuRB, pUusi);
    korjaaLisays(&pJuuriSolmuRB, pUusi);

    // Ensimmäisenä lisätyn solmun pitäisi olla oikea solmu, toisena lisätyn juurisolmu ja kolmantena lisätyn vasen solmu.

    // Tarkistetaan löytyykö puusta oikea, vasen ja juurisolmu.
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pOikea);
    TEST_ASSERT_NOT_NULL(pJuuriSolmuRB->pVasen);

    // Tarkitetaan, onko solmujen arvot oikeat.
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pJuuriSolmuRB->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJuuriSolmuRB->pOikea->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pJuuriSolmuRB->pOikea->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pJuuriSolmuRB->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pJuuriSolmuRB->pVasen->iArvo);

    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
    return;
}

// Toimiiko oikealle kiertäminen punamustassa puussa?
void test_RBKiertoOikealle(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pSolmuA = NULL;
    RBSOLMU *pSolmuB = NULL;
    RBSOLMU *pSolmuC = NULL;
    char expectedNimi1[] = "A";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "B";
    int expectedArvo2 = 300;
    char expectedNimi3[] = "C";
    int expectedArvo3 = 400;

    // Varataan muistia kolmelle solmulle.
    pSolmuA = varaaMuistiaRB(expectedNimi1, expectedArvo1);
    pSolmuB = varaaMuistiaRB(expectedNimi2, expectedArvo2);
    pSolmuC = varaaMuistiaRB(expectedNimi3, expectedArvo3);

    // Luodaan puu.
    pJuuriSolmuRB = pSolmuA;
    pSolmuA->pVasen = pSolmuB;
    pSolmuB->pVanhempi = pSolmuA;
    pSolmuB->pOikea = pSolmuC;
    pSolmuC->pVanhempi = pSolmuB;

    // Oikea kierto RB solmun pSolmuA ympärille.
    kierraOikealle(&pJuuriSolmuRB, pSolmuA);

    // Tarkistetaan, onko solmujen järjestys muuttunut. 
    // Juurisolmun tulisi olla B, juurisolmun oikea lapsi pitäisi olla A ja A:n vasen lapsi C
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pJuuriSolmuRB->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJuuriSolmuRB->pOikea->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pJuuriSolmuRB->pOikea->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pSolmuA->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pSolmuA->pVasen->iArvo);
    
    // Tarkistetaan, että muita lapsi solmuja ei ole ja että vanhemmat solmut ovat oikein.
    TEST_ASSERT_NULL(pJuuriSolmuRB->pVasen);
    TEST_ASSERT_NULL(pSolmuA->pOikea);
    TEST_ASSERT_NULL(pSolmuC->pVasen);
    TEST_ASSERT_NULL(pSolmuC->pOikea);

    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pSolmuA->pVanhempi->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pSolmuA->pVanhempi->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pSolmuC->pVanhempi->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pSolmuC->pVanhempi->iArvo);

    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
    return;
}

// Toimiiko vasemmalle kiertäminen punamustassa puussa?
void test_RBKiertoVasemmalle(void) {
    RBSOLMU *pJuuriSolmuRB = NULL;
    RBSOLMU *pSolmuA = NULL;
    RBSOLMU *pSolmuB = NULL;
    RBSOLMU *pSolmuC = NULL;
    char expectedNimi1[] = "A";
    int expectedArvo1 = 500;
    char expectedNimi2[] = "B";
    int expectedArvo2 = 300;
    char expectedNimi3[] = "C";
    int expectedArvo3 = 400;

    // Varataan muistia kolmelle solmulle.
    pSolmuA = varaaMuistiaRB(expectedNimi1, expectedArvo1);
    pSolmuB = varaaMuistiaRB(expectedNimi2, expectedArvo2);
    pSolmuC = varaaMuistiaRB(expectedNimi3, expectedArvo3);

    // Luodaan puu.
    pJuuriSolmuRB = pSolmuA;
    pSolmuA->pOikea = pSolmuB;
    pSolmuB->pVanhempi = pSolmuA;
    pSolmuB->pVasen = pSolmuC;
    pSolmuC->pVanhempi = pSolmuB;

    // Vasen kierto RB solmun pSolmuA ympärille.
    kierraVasemmalle(&pJuuriSolmuRB, pSolmuA);

    // Tarkistetaan, onko solmujen järjestys muuttunut. 
    // Juurisolmun tulisi olla B, juurisolmun vasen lapsi pitäisi olla A ja A:n oikea lapsi C
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pJuuriSolmuRB->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pJuuriSolmuRB->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pJuuriSolmuRB->pVasen->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pJuuriSolmuRB->pVasen->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pSolmuA->pOikea->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pSolmuA->pOikea->iArvo);
    
    // Tarkistetaan, että muita lapsi solmuja ei ole ja että vanhemmat solmut ovat oikein.
    TEST_ASSERT_NULL(pJuuriSolmuRB->pOikea);
    TEST_ASSERT_NULL(pSolmuA->pVasen);
    TEST_ASSERT_NULL(pSolmuC->pOikea);
    TEST_ASSERT_NULL(pSolmuC->pVasen);

    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pSolmuA->pVanhempi->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pSolmuA->pVanhempi->iArvo);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pSolmuC->pVanhempi->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo1, pSolmuC->pVanhempi->iArvo);

    pJuuriSolmuRB = vapautaMuistiRB(pJuuriSolmuRB);
    return;
}