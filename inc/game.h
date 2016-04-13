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
 * \brief      Ask the user if he wants to continue the game
 *
 * \return     Y / y / N / n
 */
unsigned char ask_continue(void);


/**
 * \brief      Get the bet from the stdin
 *
 * \return     The bet.
 */
unsigned char get_bet(void);


#endif          // __GAME_H__