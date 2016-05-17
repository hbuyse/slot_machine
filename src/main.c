/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file main.c
 *
 * @brief   Slot machine simulator in C
 */

#include <stdio.h>          // fprintf, scanf
#include <stdlib.h>          // srand, NULL
#include <time.h>          // time
#include <unistd.h>          // sleep

#include "player.h"          // Player_t, dump_player
#include "game.h"           // get_bet, ask_continue
#include "big_letters.h"          // BIG_EMPTY

#define PLAYER_NAME "Henri Buyse "          ///< Player's name
#define STARTING_CREDITS 10          ///< Credits at the beginnig of the game
#define STARTING_GAIN 0          ///< Gain at the beginning of the game
#define STARTING_BET 1          ///< Bet at the beginnig of the game


/**
 * @mainpage Slot Machine Simulator - Documentation
 *
 * @section objectives Project's objectives
 * This project consists in programming a slot machine simulator in C language.
 *
 *
 * @section rules Rules of the game
 * At the beginning of the game, the player has to deposit a certain number of credits (example: 100 credits).
 * After each play, the player choose to bet 1, 2 or 3 credits.
 * Then, the machine prints the gain in function of the combination which has appeared.
 * Of course, the obtained gain crrespond to the base gain of the combination multiply by the number of credits betted
 * by the player.
 * The game continues while the player wishes it and that his credits are positive.
 * The game automatically ends when the player has no more credits.
 * The player can also decide to collect his credits at every moment of the game.
 *
 *
 * @section author Author
 * hbuyse (https://github.com/hbuyse)
 */


/**
 * @brief      Main program
 *
 * @return     Error code for the OS
 */
int main(void)
{
    unsigned char       i           = 0; // For loops
    unsigned char       j           = 0; // For loops
    unsigned char       continuing  = 1;


    // Create the player
    Player_t            player      =
    {
        .name       = PLAYER_NAME,
        .credits    = STARTING_CREDITS,
        .gain       = STARTING_GAIN,
        .bet        = STARTING_BET
    };


    // Initialize the random process
    srand(time(NULL) );


    // Main loop
    do
    {
        // Print the informations
        clear_screen();
        player.bet  = 0;
        player.gain = 0;

        for ( i = 0; i < BIG_LETTERS_LENGTH; ++i )
        {
            for ( j = 0; j < LETTERS_PER_ROUND; ++j )
            {
                fprintf(stdout, "%s   ", BIG_EMPTY[i]);
            }

            fprintf(stdout, "\n");
        }

        fprintf(stdout, "\n");
        dump_player(player);


        // Place the bet
#ifndef __DEBUG__
        player.bet      = get_bet(player.credits);
#else
        do
        {
            player.bet = get_random_mod(3) + 1;
        }
        while ( player.bet > player.credits );
#endif
        player.credits  -= player.bet;
        clear_screen();
        player.gain     = run_game() * player.bet;


        // Print the player's informations
        dump_player(player);


        // Ask if we continue
#ifndef __DEBUG__
        continuing      = ask_continue();
#else
        continuing      = 1;
        usleep(150000);
#endif


        // Add the profit to the player's credits
        if ( (player.gain + player.credits) <= 0 )
        {
            player.credits = 0;
        }
        else
        {
            player.credits += player.gain;
        }
    }
    while ( continuing && (player.credits > 0) );

    if ( continuing && (player.credits == 0) )
    {
        fprintf(stderr, "Impossible to continue, you have 0 credits.\n");

#ifdef EASTER_EGG
        fprintf(stderr, "GET OUT OF MY CASINO!!\n");
#endif
    }

    return (0);
}