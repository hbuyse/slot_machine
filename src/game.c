/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file game.c
 *
 * @brief Source file containing the functions about the game
 */

#include <stdio.h>          // printf, scanf, EOF
#include <stdlib.h>          // srand, rand, NULL

#include "big_letters.h"          // BIG_B, BIG_E, BIG_L, BIG_N, BIG_O, BIG_S

#define ZERO_ASCII 48
#define LETTERS_PER_ROUND 3


/**
 * @var belnos
 * @brief   Letters used for the program
 */
static const char     belnos[] = {'B', 'E', 'L', 'N', 'O', 'S'};


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
    return (rand() % modulo);
}



unsigned short run_game(void)
{
    unsigned short      gain    = 0; // Gain from the round
    unsigned char       tab_res[LETTERS_PER_ROUND]; // Store the three res
    unsigned char       i       = 0; // For loops
    unsigned char       j       = 0; // For loops


    for ( i = 0; i < LETTERS_PER_ROUND; ++i )
    {
        tab_res[i] = get_random_mod(6);
    }

    for (i = 0; i < BIG_LETTERS_LENGTH; ++i)
    {
        for (j = 0; j < LETTERS_PER_ROUND; ++j)
        {
            switch (tab_res[j])
            {
                case 0:
                    printf("%s   ", BIG_B[i]);
                    break;
                case 1:
                    printf("%s   ", BIG_E[i]);
                    break;
                case 2:
                    printf("%s   ", BIG_L[i]);
                    break;
                case 3:
                    printf("%s   ", BIG_N[i]);
                    break;
                case 4:
                    printf("%s   ", BIG_O[i]);
                    break;
                case 5:
                    printf("%s   ", BIG_S[i]);
                    break;

                default:
                    printf("????????????????????   ");
            }
        }
        printf("\n");
    }

    printf("\n");

    return (gain);
}