#include "unity.h"
#include "../error.h"

void test_get_error_string_returns_first_entry_for_zero(void) {
    TEST_ASSERT_EQUAL_STRING("Everything's fine, dear", get_error_string(0));
}

void test_get_error_string_clamps_negative_values(void) {
    TEST_ASSERT_EQUAL_STRING("Error number out of bounds", get_error_string(-1));
}

void test_get_error_string_clamps_large_values(void) {
    TEST_ASSERT_EQUAL_STRING("Error number out of bounds", get_error_string(100));
}

void test_get_error_string_reads_specific_entry(void) {
    TEST_ASSERT_EQUAL_STRING("Illegal coordinates", get_error_string(1));
}
