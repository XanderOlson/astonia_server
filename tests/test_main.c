#include "unity.h"

void test_get_error_string_returns_first_entry_for_zero(void);
void test_get_error_string_clamps_negative_values(void);
void test_get_error_string_clamps_large_values(void);
void test_get_error_string_reads_specific_entry(void);
void reset_check_map_state(void);
void reset_mine_state(void);
void test_check_map_rejects_coordinates_below_minimum(void);
void test_check_map_rejects_coordinates_at_or_beyond_max(void);
void test_check_map_blocks_sightblocking_flags(void);
void test_check_map_accepts_clear_tile(void);
void test_check_map_handles_doors_when_enabled(void);
void test_gold_payout_respects_cap(void);
void test_silver_payout_respects_cap(void);

void setUp(void) {
    reset_check_map_state();
    reset_mine_state();
}

void tearDown(void) {
}

int main(void) {
    UNITY_BEGIN();

    RUN_TEST(test_get_error_string_returns_first_entry_for_zero);
    RUN_TEST(test_get_error_string_clamps_negative_values);
    RUN_TEST(test_get_error_string_clamps_large_values);
    RUN_TEST(test_get_error_string_reads_specific_entry);
    RUN_TEST(test_check_map_rejects_coordinates_below_minimum);
    RUN_TEST(test_check_map_rejects_coordinates_at_or_beyond_max);
    RUN_TEST(test_check_map_blocks_sightblocking_flags);
    RUN_TEST(test_check_map_accepts_clear_tile);
    RUN_TEST(test_check_map_handles_doors_when_enabled);
    RUN_TEST(test_gold_payout_respects_cap);
    RUN_TEST(test_silver_payout_respects_cap);

    return UNITY_END();
}
