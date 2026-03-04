/* Tests */
#include "unity.h"
#include <stdlib.h>
#include "../src/module.h"

TIEDOT *pAlku = NULL;

void setUp(void) {
    pAlku = NULL;
}

void tearDown() {
}

void test_VapautaMuisti(void) {
    pAlku = varaaMuistia(NULL, "Kosonen", 500);
    pAlku = varaaMuistia(pAlku, "Toropainen", 400);
    pAlku = vapautaMuisti(pAlku);
    TEST_ASSERT_NULL(pAlku);
}

int main(void) {
    UNITY_BEGIN();
    RUN_TEST(test_VapautaMuisti);
    return UNITY_END();
}