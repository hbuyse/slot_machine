/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file player.c
 *
 * @brief Source file containing the functions about players
 */

#include <stdio.h>   // fprintf

#include "utils.h"

#ifndef __OSX__
#  include <libintl.h>   // gettext, bindtextdomain, textdomain
#  define _(STRING) gettext(STRING)
#else
#  define _(STRING) STRING
#endif

#ifndef NDEBUG
#  include "rand.h"   // rand_get
#endif

/**
 * @brief Decimal number for the zero in the ASCII table
 */
#define ZERO_ASCII 48

#define MAX_BET 3

/**
 * @struct player_s
 * @brief Struture containing all informations about the player
 */
struct player_s {
  char* name;                       ///< Name of the player
  unsigned long long int credits;   ///< Player's credits
  short gain;                       ///< Player's gain
  unsigned short bet;               ///< Player's bet on the current round
  unsigned int ref;                 ///< Reference counter
};

#ifndef NDEBUG
static unsigned int priv_player_get_bet(void);
#endif

struct player_s* player_create(const char* name, unsigned long long int credits)
{
  struct player_s* p = NULL;

  sm_return_val_if_fail(name, NULL);
  sm_return_val_if_fail(credits != 0, NULL);

  p = sm_calloc(1, sizeof(*p));
  if (p)
  {
    p->name = sm_strdup(name);
    p->credits = credits;
    p->ref = 1;
  }

  return p;
}

int player_ref(struct player_s** p)
{
  sm_return_val_if_fail(p, -1);
  sm_return_val_if_fail(*p, -1);

  (*p)->ref++;

  return 0;
}

int player_unref(struct player_s** p)
{
  sm_return_val_if_fail(p, -1);
  sm_return_val_if_fail(*p, -1);

  if (--(*p)->ref == 0)
  {
    sm_free((*p)->name);
    sm_free(*p);
  }

  return 0;
}

void player_dump(struct player_s* p)
{
  sm_return_if_fail(p);

  fprintf(stdout, _("                       ╔═════════╦═════╦═══════╗\n"));
  fprintf(stdout, _("                       ║ CREDITS ║ BET ║ GAIN  ║\n"));
  fprintf(stdout, _("                       ╠═════════╬═════╬═══════╣\n"));
  fprintf(stdout, _("                       ║ %7llu ║ %3u ║ %5d ║\n"), p->credits, p->bet, p->gain);
  fprintf(stdout, _("                       ╚═════════╩═════╩═══════╝\n"));
}

char* player_get_name(struct player_s* p)
{
  return (p) ? p->name : NULL;
}

unsigned long long int player_get_credits(struct player_s* p)
{
  return (p) ? p->credits : 0;
}

short player_get_gain(struct player_s* p)
{
  return (p) ? p->gain : 0;
}

unsigned short player_get_bet(struct player_s* p)
{
  return (p) ? p->bet : 0;
}

int player_set_gain(struct player_s* p, short gain)
{
  sm_return_val_if_fail(p, -1);
  p->gain = gain;
  return 0;
}

int player_set_bet(struct player_s* p, unsigned short bet)
{
  sm_return_val_if_fail(p, -1);
  p->bet = bet;
  p->credits -= p->bet;
  return 0;
}

int player_add_gain_to_credits(struct player_s* p)
{
  sm_return_val_if_fail(p, -1);
  p->credits += p->gain;
  p->gain = 0;
  p->bet = 0;
  return 0;
}

int player_ask_bet(struct player_s* p)
{
  unsigned int bet = 0;        // Bet
  unsigned char bet_nok = 1;   // Bet OK or not OK?

  do
  {
#ifdef NDEBUG
    // Get the entry
    fprintf(stdout, _("Enter your bet ([1:3]): "));
    bet = fgetc(stdin);

    // Purge the standard input
    purge();

    bet -= ZERO_ASCII;
#else
    bet = priv_player_get_bet();
#endif
    if ((bet < 1) || (bet > 3))
    {
      bet_nok = 1;   // Bet Not OK
    }
    else if (bet > p->credits)
    {
      fprintf(stderr, _("You can not bet more than you currently have (bet = %u, credits = %llu).\n"), bet, p->credits);
      bet_nok = 1;   // Bet Not OK
    }
    else
    {
      fprintf(stdout, _("You bet %u credits.\n"), bet);
      bet_nok = 0;   // Bet Ok
    }
  } while (bet_nok);

  return (bet);
}

#ifndef NDEBUG
static unsigned int priv_player_get_bet(void)
{
  return rand_get(MAX_BET) + 1;
}
#endif