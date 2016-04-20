/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file player.h
 *
 * @brief Header file containing all informations and functions about players
 */

#ifndef __PLAYER_H__
#define __PLAYER_H__


/**
 * @struct Player_s
 * @brief Struture containing all informations about the player
 */
struct Player_s {
    char *name;          ///< Name of the player
    unsigned int credits;                ///< Player's credits
    short gain;                   ///< Player's gain
    unsigned char bet;                    ///< Player's bet on the current round
};


/**
 * @typedef Player_t
 * @brief Type definition of the structure Player_s
 */
typedef struct Player_s Player_t;


/**
 * @brief      Display all informations on the player
 *
 * @param[in]  player  The player we want to check the infos
 */
void dump_player(Player_t player);


/**
 * @brief      Get the player name.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player name.
 */
char* get_player_name(Player_t p);


/**
 * @brief      Get the player credits.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player credits.
 */
unsigned short get_player_credits(Player_t p);


/**
 * @brief      Get the player gain.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player gain.
 */
unsigned short get_player_gain(Player_t p);


/**
 * @brief      Get the player bet.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player bet.
 */
unsigned char get_player_bet(Player_t p);


#endif          // __PLAYER_H__