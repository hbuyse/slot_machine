/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file main.c
 *
 * @brief   Slot machine simulator in C
 */

#include <stdio.h>          // printf, scanf
#include <stdlib.h>          // srand, NULL
#include <time.h>          // time

#include "player.h"          // Player_t, dump_player
#include "game.h"           // get_bet, ask_continue
#include "big_letters.h"          // BIG_EMPTY

#define PLAYER_NAME "Henri Buyse "          ///< Player's name
#define STARTING_CREDITS 10          ///< Credits at the beginnig of the game
#define STARTING_GAIN 0          ///< Gain at the beginning of the game
#define STARTING_BET 1          ///< Bet at the beginnig of the game


/**
 * @brief      Main program
 *
 * @return     Error code for the OS
 */
int main(void)
{
    unsigned char       i           = 0; // For loops
    unsigned char       j           = 0; // For loops
    char                continuing  = 'y';


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
                printf("%s   ", BIG_EMPTY[i]);
            }

            printf("\n");
        }

        printf("\n");
        dump_player(player);


        // Place the bet
        player.bet      = get_bet(player.credits);
        player.credits  -= player.bet;
        clear_screen();
        player.gain     = run_game() * player.bet;


        // Print the player's informations
        dump_player(player);


        // Ask if we continue
        continuing      = ask_continue();


        // Add the profit to the player's credits
        player.credits  += player.gain;
    }
    while ( ( (continuing == 'y') || (continuing == 'Y') ) && (player.credits > 0) );

    return (0);
}