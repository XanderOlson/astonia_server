#include "mine.h"

int compute_mine_payout(int metal_type,unsigned char *drdata,int miner_prof_bonus,int chance_roll,int amount_roll)
{
    int base,range,amount;

    if (chance_roll) return 0;

    switch (metal_type) {
        case MINE_METAL_GOLD:     base=drdata[MINE_DRDATA_GOLD]; break;
        case MINE_METAL_SILVER:   base=drdata[MINE_DRDATA_SILVER]; break;
        default:        return 0;
    }

    if (base<=0) return 0;

    range=base*2+1;
    if (amount_roll<0) amount_roll=0;
    if (amount_roll>=range) amount_roll%=range;

    amount=amount_roll+base;
    amount*=10;

    if (miner_prof_bonus) amount+=amount*miner_prof_bonus/10;

    return amount;
}
