#include <stdio.h>
#include <string.h>
#include "../src/hello.h"

static int assert_str_eq(const char* expected, const char* actual, const char* name) {
    if (strcmp(expected, actual) != 0) {
        fprintf(stderr, "[FAIL] %s: expected=\"%s\" actual=\"%s\"\n", name, expected, actual);
        return 0; // failed
    } else {
        fprintf(stdout, "[PASS] %s\n", name);
        return 1; // passed
    }
}

int main(void) {
    int tests_run = 0;
    int tests_failed = 0;

    tests_run++;
    if (!assert_str_eq("Hello, World!", hello_message(), "hello_message returns greeting")) {
        tests_failed++;
    }

    if (tests_failed) {
        fprintf(stderr, "\n%d/%d tests failed.\n", tests_failed, tests_run);
        return 1;
    }

    fprintf(stdout, "\nAll %d tests passed.\n", tests_run);
    return 0;
}
