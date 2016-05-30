#include <stdio.h>

#include <game.h>

#include "../minunit/minunit.h"

MU_TEST(test_get_random_mod)
{
    unsigned char       i   = 0;
    unsigned char       res = 10;


    for ( i = 0; i < 100; ++i )
    {
        res = get_random_mod(6);
        mu_check(res < 6);
    }
}

MU_TEST_SUITE(slot_machine)
{
    fprintf(stdout, "\n\e[1m[test_get_random_mod]\e[0m\t");
    MU_RUN_TEST(test_get_random_mod);
}

int main(void)
{
    MU_RUN_SUITE(slot_machine);
    MU_REPORT();

    return ( (minunit_fail == 0) ? 0 : 1);
}