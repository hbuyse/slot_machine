/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file main.c
 *
 * @brief   Slot machine simulator in C
 */

#include <stdio.h>    // fprintf, scanf
#include <stdlib.h>   // srand, NULL
#include <time.h>     // time
#include <unistd.h>   // sleep

#include "big_letters.h"   // BIG_EMPTY
#include "game.h"          // ask_continue
#include "player.h"        // Player_t, player_dump

#define PLAYER_NAME "Henri Buyse "   ///< Player's name
#define STARTING_CREDITS 10          ///< Credits at the beginnig of the game

#ifndef __OSX__
#  include <libintl.h>   // gettext, bindtextdomain, textdomain
#  include <locale.h>    // setlocale
#  define _(STRING) gettext(STRING)
#else
#  define _(STRING) STRING
#endif

/**
 * @mainpage Slot Machine Simulator - Documentation
 *
 * @section objectives Project's objectives
 * This project consists in programming a slot machine simulator in C language.
 *
 *
 * @section rules Rules of the game
 * At the beginning of the game, the player has to deposit a certain number of credits (example: 100 credits).
 * After each play, the player choose to bet 1, 2 or 3 credits.
 * Then, the machine prints the gain in function of the combination which has appeared.
 * Of course, the obtained gain crrespond to the base gain of the combination multiply by the number of credits betted
 * by the player.
 * The game continues while the player wishes it and that his credits are positive.
 * The game automatically ends when the player has no more credits.
 * The player can also decide to collect his credits at every moment of the game.
 *
 *
 * @section author Author
 * hbuyse (https://github.com/hbuyse)
 */

/**
 * @brief      Main program
 *
 * @return     Error code for the OS
 */
int main(void)
{
  unsigned char i = 0;   // For loops
  unsigned char j = 0;   // For loops
  unsigned char continuing = 1;
  unsigned char figure_or_letter = 1;

  struct player_s* player = NULL;

#ifndef __OSX__

  /* LC_ALL is a catch-all Locale Category (LC); setting it will alter all LC categories. There are other, specific,
   * categories for translations; for example LC_MESSAGES is the LC (LC) for message translation; LC_CTYPE is the
   * category that indicates the character set supported.
   *
   * By setting the locale to "", you are implicitly assigning the locale to the user's defined locale (grabbed from
   * the user's LC or LANG environment variables). If there is no user-defined locale, the default locale "C" is used.
   */
  setlocale(LC_ALL, "");

  /* This command binds the name "foo" to the directory root of the message files. This is used to specify where you
   * want your locale files stored; using the standard /usr/local/share/locale or /usr/share/locale is a good idea.
   * "foo" should correspond to the application name; you will use it when setting the gettext domain through
   * textdomain(), and it corresponds to the name of the file to be looked up in the appropriate locale directory.
   *
   * The bindtextdomain() call is not mandatory; if you choose to install your file in the system's default locale
   * directory it can be omitted. Since the default can change from system to system, however, it is recommended.
   */
  bindtextdomain("locale", "./po");

  /* This sets the application name as "foo", as cited above. This makes gettext calls look for the file foo.po in
   * the appropriate directory. By binding various domains and setting the textdomain (or using dcgettext(), explained
   * elsewhere) at runtime, you can switch between different domains as desired.
   */
  textdomain("locale");
#endif

  // Initialize the random process
  srand(time(NULL));

  // Create the player object
  player = player_create(PLAYER_NAME, STARTING_CREDITS);

#ifdef NDEBUG
  figure_or_letter = ask_figure_or_letter();
#endif

  // Main loop
  do
  {
    // Print the informations
    // clear_screen();
    player_set_bet(player, 0);
    player_set_gain(player, 0);

    for (i = 0; i < BIG_LETTERS_LENGTH; ++i)
    {
      for (j = 0; j < LETTERS_PER_ROUND; ++j)
      {
        fprintf(stdout, "%s   ", BIG_EMPTY[i]);
      }

      fprintf(stdout, "\n");
    }

    fprintf(stdout, "\n");
    player_dump(player);

    // Place the bet
    unsigned short bet = player_ask_bet(player);
    player_set_bet(player, bet);
    // clear_screen();
    unsigned short gain = run_game(figure_or_letter) * player_get_bet(player);
    player_set_gain(player, gain);

    // Print the player's informations
    player_dump(player);

    // Ask if we continue
#ifdef NDEBUG
    continuing = ask_continue();
#else
    continuing = 1;
    usleep(150000);
#endif

    // Add the profit to the player's credits
    if ((player_get_gain(player) + player_get_credits(player)) <= 0)
    {
      fprintf(stderr, _("Impossible to continue, you have 0 credits.\n"));
#ifdef EASTER_EGG
      fprintf(stderr, _("GET OUT OF MY CASINO!!\n"));
#endif
      player_unref(&player);
    }
    else
    {
      player_add_gain_to_credits(player);
    }
  } while (continuing && player);

  return (0);
}