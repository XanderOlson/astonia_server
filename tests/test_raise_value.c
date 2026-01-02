#include <string.h>

#include "unity.h"
#include "../server.h"
#include "../skill.h"

int raise_value_player(int cn,int v);
int raise_value_npc(int cn,int v);

static struct character test_chars[MAXCHARS];
struct character *ch=test_chars;

void update_char(int cn)
{
    (void)cn;
}

int dlog(int cn,int in,char *format,...)
{
    (void)cn;
    (void)in;
    (void)format;
    return 0;
}

int check_levelup(int cn)
{
    (void)cn;
    return 0;
}

void reset_raise_value_state(void)
{
    memset(test_chars,0,sizeof(test_chars));
}

void test_raise_value_player_spends_exp(void)
{
    int cn=1;
    int v=V_DAGGER;
    int cost=raise_cost(v,1,0);
    unsigned int exp=cost;

    ch[cn].flags=CF_PLAYER;
    ch[cn].value[1][v]=1;
    ch[cn].exp=exp;
    ch[cn].exp_used=0;

    TEST_ASSERT_EQUAL_INT(1, raise_value_player(cn,v));
    TEST_ASSERT_EQUAL_INT(2, ch[cn].value[1][v]);
    TEST_ASSERT_EQUAL_UINT(exp, ch[cn].exp);
    TEST_ASSERT_EQUAL_UINT(cost, ch[cn].exp_used);
}

void test_raise_value_player_rejects_insufficient_exp(void)
{
    int cn=2;
    int v=V_DAGGER;
    int cost=raise_cost(v,1,0);

    ch[cn].flags=CF_PLAYER;
    ch[cn].value[1][v]=1;
    ch[cn].exp=cost-1;
    ch[cn].exp_used=0;

    TEST_ASSERT_EQUAL_INT(0, raise_value_player(cn,v));
    TEST_ASSERT_EQUAL_INT(1, ch[cn].value[1][v]);
    TEST_ASSERT_EQUAL_UINT(0, ch[cn].exp_used);
}

void test_raise_value_npc_grants_exp(void)
{
    int cn=3;
    int v=V_DAGGER;
    int cost=raise_cost(v,1,0);

    ch[cn].flags=0;
    ch[cn].value[1][v]=1;
    ch[cn].exp=0;
    ch[cn].exp_used=0;

    TEST_ASSERT_EQUAL_INT(1, raise_value_npc(cn,v));
    TEST_ASSERT_EQUAL_INT(2, ch[cn].value[1][v]);
    TEST_ASSERT_EQUAL_UINT(cost, ch[cn].exp);
    TEST_ASSERT_EQUAL_UINT(cost, ch[cn].exp_used);
}
