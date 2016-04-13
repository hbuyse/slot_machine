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

    char                tab[6]      = {'B', 'E', 'L', 'N', 'O', 'S'};

    for ( i = 0; i < sizeof(tab); ++i )
    {
        for ( j = 0; j < sizeof(tab); ++j )
        {
            for ( k = 0; k < sizeof(tab); ++k )
            {
                printf("%c%c%c\n", tab[i], tab[j], tab[k]);
            }
        }
    }
#endif


    // Main loop
    do
    {
        // Place the bet
        player.bet  = get_bet();


        // Print the informations
        dump_player(player);


        // Ask if we continue
        continuing  = ask_continue();
    }
    while ( ( (continuing == 'y') || (continuing == 'Y') ) && (player.credits > 0) );

    return (0);
}