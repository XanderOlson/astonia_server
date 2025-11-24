#include "unity.h"

void test_get_error_string_returns_first_entry_for_zero(void);
void test_get_error_string_clamps_negative_values(void);
void test_get_error_string_clamps_large_values(void);
void test_get_error_string_reads_specific_entry(void);

void setUp(void) {
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_error_string_returns_first_entry_for_zero);
    RUN_TEST(test_get_error_string_clamps_negative_values);
    RUN_TEST(test_get_error_string_clamps_large_values);
    RUN_TEST(test_get_error_string_reads_specific_entry);

    return UNITY_END();
}
