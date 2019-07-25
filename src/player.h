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
 * @typedef struct player_s
 * @brief Opaque definition of a player
 */
struct player_s;

struct player_s* player_create(const char* name, unsigned long long int credits);
int player_ref(struct player_s** p);
int player_unref(struct player_s** p);

/**
 * @brief      Display all informations on the player
 *
 * @param[in]  player  The player we want to check the infos
 */
void player_dump(struct player_s* player);

/**
 * @brief      Get the player name.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player name.
 */
char* player_get_name(struct player_s* player);

/**
 * @brief      Get the player credits.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player credits.
 */
unsigned long long int player_get_credits(struct player_s* player);

/**
 * @brief      Get the player gain.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player gain.
 */
unsigned short player_get_gain(struct player_s* player);

/**
 * @brief      Get the player bet.
 *
 * @param[in]  p     The player concerned
 *
 * @return     The player bet.
 */
unsigned short player_get_bet(struct player_s* player);

int player_set_gain(struct player_s* p, unsigned short gain);
int player_set_bet(struct player_s* p, unsigned short bet);
int player_add_gain_to_credits(struct player_s* p);
int player_ask_bet(struct player_s* p);

#endif   // __PLAYER_H__