#include <string.h>

#include "unity.h"
#include "../server.h"

int test_check_map(int x,int y);
void test_set_door_context(int enable,int x,int y);

static struct map test_map[MAXMAP*MAXMAP];
struct map *map=test_map;

void reset_check_map_state(void) {
    memset(test_map,0,sizeof(test_map));
    test_set_door_context(0,0,0);
}

void test_check_map_rejects_coordinates_below_minimum(void) {
    TEST_ASSERT_EQUAL_INT(0, test_check_map(0,1));
    TEST_ASSERT_EQUAL_INT(0, test_check_map(1,0));
}

void test_check_map_rejects_coordinates_at_or_beyond_max(void) {
    TEST_ASSERT_EQUAL_INT(0, test_check_map(MAXMAP,1));
    TEST_ASSERT_EQUAL_INT(0, test_check_map(1,MAXMAP));
}

void test_check_map_blocks_sightblocking_flags(void) {
    int m=5+5*MAXMAP;
    map[m].flags=MF_SIGHTBLOCK;
    TEST_ASSERT_EQUAL_INT(0, test_check_map(5,5));

    map[m].flags=MF_TSIGHTBLOCK;
    TEST_ASSERT_EQUAL_INT(0, test_check_map(5,5));
}

void test_check_map_accepts_clear_tile(void) {
    int m=10+10*MAXMAP;
    map[m].flags=0;
    TEST_ASSERT_EQUAL_INT(1, test_check_map(10,10));
}

void test_check_map_handles_doors_when_enabled(void) {
    int m=3+3*MAXMAP;
    map[m].flags=MF_DOOR;
    test_set_door_context(1,2,2);

    TEST_ASSERT_EQUAL_INT(1, test_check_map(3,3));
}
