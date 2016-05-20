/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file game.h
 *
 * @brief Header file containing all informations and functions about the game
 */

#ifndef __GAME_H__
#define __GAME_H__


/**
 * @brief Number of random letter that is pulled for a game
 */
#define LETTERS_PER_ROUND 3


/**
 * @brief      Clear the terminal screen
 */
void clear_screen(void);


/**
 * @brief      Ask the user if he wants to continue the game
 *
 * @return     Y / y / N / n
 */
unsigned char ask_continue(void);


/**
 * @brief      Get the bet from the stdin
 *
 * @param[in]  Current credits from the player
 *
 * @return     The bet.
 */
unsigned char get_bet(unsigned short credits);


/**
 * @brief      Get a random number using a modulo.
 *
 * @param[in]  modulo  Modulo of the random number
 *
 * @return     The random number
 */
unsigned int get_random_mod(unsigned int modulo);


/**
 * @brief      Play a round
 *
 * @return     The gain won by the player
 */
short run_game(void);


#endif          // __GAME_H__