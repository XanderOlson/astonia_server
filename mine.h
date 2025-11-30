#ifndef MINE_H
#define MINE_H

#define MINE_METAL_GOLD   1
#define MINE_METAL_SILVER 2

#define MINE_DRDATA_SILVER 0
#define MINE_DRDATA_GOLD   1

int compute_mine_payout(int metal_type,unsigned char *drdata,int miner_prof_bonus,int chance_roll,int amount_roll);

#endif
