/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file game.c
 *
 * @brief Source file containing the functions about the game
 */

#include <stdio.h>          // printf, scanf, EOF

/**
 * \brief      Purge the standard input
 */
static void purge(void)
{
    int     c;


    while ( (c = getchar() ) != '\n' && c != EOF )
    {
        ;
    }
}



unsigned char get_bet(void)
{
    unsigned int        bet     = 0; // Bet
    unsigned char       bet_nok = 1; // Bet OK or not OK?


    do
    {
        // Get the entry
        printf("Enter your bet ([1:3]): ");
        bet = fgetc(stdin);
        // Purge the standard input
        purge();

        bet -= 48;

        if ( (bet < 1) || (bet > 3) )
        {
            bet_nok = 1;          // Bet Not OK
        }
        else
        {
            printf("You bet %u credits.\n", bet);
            bet_nok = 0;          // Bet Ok
        }
    }
    while ( bet_nok );

    return (bet);
}