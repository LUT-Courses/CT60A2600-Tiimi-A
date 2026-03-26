#include "../src/linkitettylista.h"
#include "unity.h"

// Onnistuuko varaaMuistia, kun lista on tyhjä
void test_VaraaMuistia(void) {
    TIEDOT *pAlku = NULL;

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

    pAlku = vapautaMuisti(pAlku);
}

// Testataan, onnistuuko muistin vapauttaminen.
void test_VapautaMuisti(void) {
    TIEDOT *pAlku = NULL;
    pAlku = varaaMuistia(NULL, "Kosonen", 500);
    pAlku = varaaMuistia(pAlku, "Toropainen", 400);
    pAlku = vapautaMuisti(pAlku);
    TEST_ASSERT_NULL(pAlku);

    pAlku = vapautaMuisti(pAlku);
}

// Onnistuuko varata muistia usealle alkiolle kun lista on tyhjä
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

    pAlku = vapautaMuisti(pAlku);
}

void test_lisaaListaan_tyhja() {
    TIEDOT *pAlku = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedArvo = 500;
    int iIndeksi = 20;

    pAlku = lisaaListaan(pAlku, iIndeksi, expectedNimi, expectedArvo);
    TEST_ASSERT_NULL(pAlku->pSeuraava);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo, pAlku->iYhteensa);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan, onnistuuko listan alkuun lisaaminen.
void test_lisaaListaan_alkuun() {
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
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aSukunimi);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan indeksin mukaan lisaaminen.
void test_lisaaListaan_indeksilla() {
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

    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo3, pAlku->iYhteensa);

    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedArvo2, pAlku->pSeuraava->pSeuraava->iYhteensa);

    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aSukunimi);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan, onnistuuko alkioiden maaran laskeminen.
void test_useammalleAlkiolleSamaLKM() {
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
}

// Testataan, onnistuuko poistaminen lukumaaran perusteella.
void test_poistaListaLkmPerusteella() {
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
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aSukunimi);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan, onnistuuko poistaminen nimen perusteella.
void test_poistaListaNimenPerusteella() {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedArvo1 = 500;
    int iIndeksi1 = 1;
    pAlku = lisaaListaan(pAlku, iIndeksi1, expectedNimi1, expectedArvo1);

    char expectedNimi2[] = "Karjalainen";
    int expectedArvo2 = 300;
    int iIndeksi2 = 2;
    pAlku = lisaaListaan(pAlku, iIndeksi2, expectedNimi2, expectedArvo2);

    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->aSukunimi);

    pAlku = poistaListastaNimenPerusteella(pAlku, "Kosonen");

    TEST_ASSERT_NULL(pAlku->pSeuraava);
    TEST_ASSERT_EQUAL_STRING("Karjalainen", pAlku->aSukunimi);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan lomituslajittelu, tyhjä lista
void test_lomitusLajitteluTyhjaLista() {
    TIEDOT *pAlku = NULL;

    pAlku = lomitusLajittelu(pAlku);
    TEST_ASSERT_NULL(pAlku);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan lomituslajittelu yhdellä alkiolla
void test_lomituLajitteluYhdellaAlkiolla() {
    TIEDOT *pAlku = NULL;

    char expectedNimi[] = "Kosonen";
    int expectedYhteensa = 500;

    pAlku = varaaMuistia(pAlku, expectedNimi, expectedYhteensa);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa, pAlku->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan lomituslajittelu kahdella alkiolla
void test_lomitusLajitteluKahdellaAlkiolla() {
    TIEDOT *pAlku = NULL;

    char expectedNimi1[] = "Kosonen";
    int expectedYhteensa1 = 500;
    char expectedNimi2[] = "Karjalainen";
    int expectedYhteensa2 = 300;

    pAlku = varaaMuistia(pAlku, expectedNimi1, expectedYhteensa1);
    pAlku = varaaMuistia(pAlku, expectedNimi2, expectedYhteensa2);
    pAlku = lomitusLajittelu(pAlku);

    TEST_ASSERT_NOT_NULL(pAlku);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
}

// Testataan lomituslajittelu usealla alkiolla
void test_lomitusLajitteluUseallaAlkiolla() {
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
    TEST_ASSERT_EQUAL_STRING(expectedNimi4, pAlku->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa4, pAlku->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi3, pAlku->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa3, pAlku->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi1, pAlku->pSeuraava->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa1, pAlku->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi2, pAlku->pSeuraava->pSeuraava->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa2, pAlku->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_EQUAL_STRING(expectedNimi5,
                             pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->aSukunimi);
    TEST_ASSERT_EQUAL_INT(expectedYhteensa5,
                          pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->iYhteensa);
    TEST_ASSERT_NULL(pAlku->pEdellinen);
    TEST_ASSERT_NULL(pAlku->pSeuraava->pSeuraava->pSeuraava->pSeuraava->pSeuraava);

    pAlku = vapautaMuisti(pAlku);
}
