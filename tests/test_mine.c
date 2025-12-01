#include <stdlib.h>
#include <string.h>

#include "unity.h"
#include "../mine.h"

static unsigned char payout_drdata[6];

void reset_mine_state(void)
{
    memset(payout_drdata,0,sizeof(payout_drdata));
    srand(1);
}

void test_gold_payout_respects_cap(void)
{
    int miner_bonus=25;
    int amount_roll;
    int amount;

    payout_drdata[MINE_DRDATA_GOLD]=20;
    amount_roll=payout_drdata[MINE_DRDATA_GOLD]*2;

    amount=compute_mine_payout(MINE_METAL_GOLD,payout_drdata,miner_bonus,0,amount_roll);

    TEST_ASSERT_TRUE(amount<=2100);
    TEST_ASSERT_EQUAL_INT(2100, amount);
}

void test_silver_payout_respects_cap(void)
{
    int miner_bonus=15;
    int amount_roll;
    int amount;

    payout_drdata[MINE_DRDATA_SILVER]=12;
    amount_roll=payout_drdata[MINE_DRDATA_SILVER]*2;

    amount=compute_mine_payout(MINE_METAL_SILVER,payout_drdata,miner_bonus,0,amount_roll);

    TEST_ASSERT_TRUE(amount<=900);
    TEST_ASSERT_EQUAL_INT(900, amount);
}
