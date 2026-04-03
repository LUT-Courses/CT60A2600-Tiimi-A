#include "../src/linkitettylista.h"
#include "unity.h"

// Onnistuuko muistin varaaminen, kun lista on tyhjä?
void test_VaraaMuistia(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi[LEN] = "Kosonen";
    int expectedYhteensa = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi, expectedYhteensa);
    TEST_ASSERT_NOT_NULL(pAlku);

    // Pitäisi olla ainut solmu listassa.
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava);

    // Löytyykö oikeat arvot?
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa, pAlku->iYhteensa);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan, onnistuuko muistin vapauttaminen?
void test_VapautaMuisti(void) {
    TIEDOT *pAlku = NULL;
    pAlku = varaaMuistia(NULL, "Kosonen", 500);
    pAlku = varaaMuistia(pAlku, "Toropainen", 400);
    pAlku = vapautaMuisti(pAlku);
    TEST_ASSERT_NULL(pAlku);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Onnistuuko muistin varaaminen usealle alkiolle, kun lista on tyhjä?
void test_VaraaMuistiUsealleAlkiolle(void) {
    TIEDOT *pAlku = NULL;

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

    // Löytyykö oikeat arvot.
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->iYhteensa);
    ptr = pAlku->pSeuraava;
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, ptr->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, ptr->iYhteensa);
    ptr = ptr->pSeuraava;
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, ptr->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, ptr->iYhteensa);

    // ptr pitäisi olla viimeisessä solmussa ja pAlku pitäisi olla ensimmäinen solmu.
    ptr = ptr->pSeuraava;
    TEST_ASSERT_NULL(ptr);
    TEST_ASSERT_NULL(pAlku->pEdellinen);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Onnistuuko yhden alkion lisääminen tyhjälle listalle?
void test_lisaaListaan_tyhja(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedArvo = 500;
    int iIndeksi = 20;

    pAlku = lisaaListaan(pAlku, iIndeksi, expectedNimi, expectedArvo);
    TEST_ASSERT_NULL(pAlku->pSeuraava);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo, pAlku->iYhteensa);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan, onnistuuko listan alkuun lisääminen.
void test_lisaaListaan_alkuun(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;

    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 300;
    int iIndeksi2 = 2;

    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    char expectedNimi3[] = "Suomalainen";
    int expectedArvo3 = 200;
    int iIndeksi3 = 1;

    pAlku = lisaaListaan(pAlku, iIndeksi3, expectedNimi3, expectedArvo3);

    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aNimi);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan indeksin mukaan lisääminen.
void test_lisaaListaan_indeksilla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;

    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 300;
    int iIndeksi2 = 2;

    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    char expectedNimi3[] = "Suomalainen";
    int expectedArvo3 = 200;
    int iIndeksi3 = 1;

    pAlku = lisaaListaan(pAlku, iIndeksi3, expectedNimi3, expectedArvo3);

    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pAlku->iYhteensa);

    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pAlku->pSeuraava->pSeuraava->iYhteensa);

    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aNimi);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan, onnistuuko alkioiden määrän laskeminen.
void test_useammalleAlkiolleSamaLKM(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;
    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 500;
    int iIndeksi2 = 2;
    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    int iLKMSama = useammallaAlkiollaSamaLKM(pAlku, 500);

    TEST_ASSERT_EQUAL_INT(2, iLKMSama);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan, onnistuuko poistaminen lukumäärän perusteella.
void test_poistaListaLkmPerusteella(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;
    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 300;
    int iIndeksi2 = 2;
    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    TEST_ASSERT_EQUAL_INT(expectedArvo2, pAlku->pSeuraava->iYhteensa);

    pAlku = poistaListastaLkmPeruusteella(pAlku, 300);

    TEST_ASSERT_NULL(pAlku->pSeuraava);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aNimi);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan, onnistuuko poistaminen nimen perusteella.
void test_poistaListaNimenPerusteella(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;
    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 300;
    int iIndeksi2 = 2;
    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aNimi);

    pAlku = poistaListastaNimenPerusteella(pAlku, "Kosonen");

    TEST_ASSERT_NULL(pAlku->pSeuraava);
    TEST_ASSERT_EQUAL_STRING("Karjalainen", pAlku->aNimi);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lomituslajittelu, kun lista on tyhjä.
void test_lomitusLajitteluTyhjaLista(void) {
    TIEDOT *pAlku = NULL;

    pAlku = lomitusLajittelu(pAlku);
    TEST_ASSERT_NULL(pAlku);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lomituslajittelu yhdellä alkiolla.
void test_lomitusLajitteluYhdellaAlkiolla() {
    TIEDOT *pAlku = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedYhteensa = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi, expectedYhteensa);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa, pAlku->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lomituslajittelu kahdella alkiolla.
void test_lomitusLajitteluKahdellaAlkiolla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 500;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 300;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lomituslajittelu usealla alkiolla.
void test_lomitusLajitteluUseallaAlkiolla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 300;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 500;
    char expectedNimi3[] = "Ankka";
    int expectedYhteensa3 = 50;
    char expectedNimi4[] = "Hanhi";
    int expectedYhteensa4 = 1;
    char expectedNimi5[] = "Hiiri";
    int expectedYhteensa5 = 10000;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = varaaMuistia(pAlku, expectedNimi3, expectedYhteensa3);
    pAlku = varaaMuistia(pAlku, expectedNimi4, expectedYhteensa4);
    pAlku = varaaMuistia(pAlku, expectedNimi5, expectedYhteensa5);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi4, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa4, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi5,
                             pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa5,
                          pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lomituslajittelu, kun on sama arvo. Pitäisi mennä aakkosten mukaan.
void test_lomitusLajitteluSamaArvo(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 50;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 50;
    char expectedNimi3[] = "Ankka";
    int expectedYhteensa3 = 50;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = varaaMuistia(pAlku, expectedNimi3, expectedYhteensa3);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lisäyslajittelu, kun lista on tyhjä.
void test_lisaysLajitteluTyhjaLista(void) {
    TIEDOT *pAlku = NULL;

    pAlku = lisaysLajittelu(pAlku);
    TEST_ASSERT_NULL(pAlku);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan lisäyslajittelu yhdellä alkiolla.
void test_lisaysLajitteluYhdellaAlkiolla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedYhteensa = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi, expectedYhteensa);
    pAlku = lisaysLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa, pAlku->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lisäyslajittelu kahdella alkiolla.
void test_lisaysLajitteluKahdellaAlkiolla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 300;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = lisaysLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lisäyslajittelu usealla alkiolla.
void test_lisaysLajitteluUseallaAlkiolla(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 300;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 500;
    char expectedNimi3[] = "Ankka";
    int expectedYhteensa3 = 50;
    char expectedNimi4[] = "Hanhi";
    int expectedYhteensa4 = 1;
    char expectedNimi5[] = "Hiiri";
    int expectedYhteensa5 = 10000;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = varaaMuistia(pAlku, expectedNimi3, expectedYhteensa3);
    pAlku = varaaMuistia(pAlku, expectedNimi4, expectedYhteensa4);
    pAlku = varaaMuistia(pAlku, expectedNimi5, expectedYhteensa5);
    pAlku = lisaysLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi5, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa5, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->pSeuraava->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, pAlku->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi4,
                             pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa4,
                          pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}

// Testataan lisäyslajittelu, kun on sama arvo. Pitäisi mennä aakkosten mukaan
// (väärinpäin koska CodeGrade).
void test_lisaysLajitteluSamaArvo(void) {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Karjalainen";
    int expectedYhteensa1 = 50;
    char expectedNimi2[] = "Ankka";
    int expectedYhteensa2 = 50;
    char expectedNimi3[] = "Kosonen";
    int expectedYhteensa3 = 50;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = varaaMuistia(pAlku, expectedNimi3, expectedYhteensa3);
    pAlku = lisaysLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->pSeuraava->aNimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
    return;
}
