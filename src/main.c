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

#define PLAYER_NAME "Henri Buyse "          ///< Player's name
#define STARTING_CREDITS 100          ///< Credits at the beginnig of the game
#define STARTING_GAIN 0          ///< Gain at the beginning of the game
#define STARTING_BET 1          ///< Bet at the beginnig of the game


/**
 * @brief      Main program
 *
 * @return     Error code for the OS
 */
int main(void)
{
    char            continuing  = 'y';


    // Create the player
    Player_t        player      =
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
        // Add the profit to the player's credits
        player.credits  += player.gain;


        // Print the informations
        dump_player(player);


        // Place the bet
        player.bet      = get_bet(player.credits);
        player.credits  -= player.bet;
        player.gain     = run_game() * player.bet;


        // Print the player's informations
        dump_player(player);


        // Ask if we continue
        continuing      = ask_continue();
    }
    while ( ( (continuing == 'y') || (continuing == 'Y') ) && (player.credits > 0) );

    return (0);
}