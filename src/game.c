/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file game.c
 *
 * @brief Source file containing the functions about the game
 */

#include <stdio.h>          // printf, scanf, EOF
#include <stdlib.h>         // srand, rand, NULL

#include "big_letters.h"    // BIG_B, BIG_E, BIG_L, BIG_N, BIG_O, BIG_S

#define ZERO_ASCII 48
#define LETTERS_PER_ROUND 3


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



unsigned char ask_continue(void)
{
    int     continuing = 'y';


    do
    {
        // Get the entry
        printf("Do you want to continue ? : ");
        continuing = fgetc(stdin);


        // Purge the standard input
        purge();
    }
    while ( (continuing != 'y') && (continuing != 'Y') && (continuing != 'n') && (continuing != 'N') );

    return (continuing);
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

        bet -= ZERO_ASCII;

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


unsigned int get_random_mod(unsigned int modulo)
{
    return rand() % modulo;
}


unsigned short run_game(void)
{
    unsigned short gain = 0;        // Gain from the round
    unsigned char  tab_res[LETTERS_PER_ROUND];      // Store the three res
    unsigned char i = 0;            // For loops

    for (i = 0; i < LETTERS_PER_ROUND; ++i)
    {
        tab_res[i] = get_random_mod(6);
        printf("%u", tab_res[i]);
    }
    printf("\n");

    return gain;
}

void display_results(unsigned char tab_res[])
{
    unsigned char i = 0;

    for(i = 0; i < sizeof(tab_res); ++i)
    {
        printf("%u", tab_res[i]);
    }
}