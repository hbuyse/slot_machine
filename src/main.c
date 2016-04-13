/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file main.c
 *
 * @brief   Slot machine simulator in C
 */

#include <stdio.h>          // printf, scanf
#include <stdlib.h>         // srand, NULL
#include <time.h> // time

#include "player.h"          // Player_t, dump_player
#include "game.h"           // get_bet, ask_continue

#define PLAYER_NAME "Henri Buyse "          ///< Player's name
#define STARTING_CREDITS 100          ///< Credits at the beginnig of the game
#define STARTING_GAIN 0          ///< Gain at the beginning of the game
#define STARTING_BET 1          ///< Bet at the beginnig of the game


/**
 * @var belnos
 * @brief   Letters used for the program
 */
static char                belnos[6]      = {'B', 'E', 'L', 'N', 'O', 'S'};


/**
 * @brief      Main program
 *
 * @return     Error code for the OS
 */
int main(void)
{
    char                continuing  = 'y';


    // Create the player
    Player_t            player      =
    {
        .name       = PLAYER_NAME,
        .credits    = STARTING_CREDITS,
        .gain       = STARTING_GAIN,
        .bet        = STARTING_BET
    };


#ifdef PRINT_COMBINATION
    unsigned char       i           = 0;
    unsigned char       j           = 0;
    unsigned char       k           = 0;


    for ( i = 0; i < sizeof(belnos); ++i )
    {
        for ( j = 0; j < sizeof(belnos); ++j )
        {
            for ( k = 0; k < sizeof(belnos); ++k )
            {
                printf("%c%c%c\n", belnos[i], belnos[j], belnos[k]);
            }
        }
    }
#endif
    // Initialize the random process
    srand(time(NULL));

    // Main loop
    do
    {
        // Add the profit to the player's credits
        player.credits  += player.gain;


        // Print the informations
        dump_player(player);

        // Place the bet
        player.bet      = get_bet();


        // Print the player's informations
        dump_player(player);


        // Ask if we continue
        continuing      = ask_continue();
    }
    while ( ( (continuing == 'y') || (continuing == 'Y') ) && (player.credits > 0) );

    return (0);
}