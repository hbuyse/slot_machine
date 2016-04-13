/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file main.c
 *
 * @brief   Slot machine simulator in C
 */

#include <stdio.h>          // printf, scanf

#include "player.h"          // Player_t, dump_player
#include "game.h"           // get_bet

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
    unsigned char       continuing  = 1;


    // Create the player
    Player_t            player      =
    {
        .name       = PLAYER_NAME,
        .credits    = STARTING_CREDITS,
        .gain       = STARTING_GAIN,
        .bet        = STARTING_BET
    };


    // Main loop
    do
    {
        // Place the bet
        player.bet  = get_bet();


        // Print the informations
        dump_player(player);


        // Ask if we continue
        continuing  = 1;
    }
    while ( (continuing) && (player.credits > 0) );

    return (0);
}