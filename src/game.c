/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file game.c
 *
 * @brief Source file containing the functions about the game
 */

#include <stdio.h>          // printf, scanf, EOF
#include <stdlib.h>          // srand, rand, NULL

#include "game.h"          // LETTERS_PER_ROUND
#include "big_letters.h"          // BIG_B, BIG_E, BIG_L, BIG_N, BIG_O, BIG_S

#define ZERO_ASCII 48


/**
 * @var belnos
 * @brief   Letters used for the program
 */
static const char     belnos[] = {'B', 'E', 'L', 'N', 'O', 'S'};


/**
 * @struct Gain_s
 * @brief Structure that contains the gain in function of the results
 */
struct Gain_s {
    char first;          ///< First letter result
    char second;          ///< Second letter result
    char third;          ///< Third letter result
    short gain;          ///< Gain
};


/**
 * @typedef Gain_t
 */
typedef struct Gain_s Gain_t;


/**
 * @brief Contains some possible results
 */
const Gain_t     gains[] =
{
    {.first = 'B', .second = 'E', .third = 'L', .gain = 20},
    {.first = 'B', .second = 'O', .third = 'L', .gain = 100},
    {.first = 'B', .second = 'O', .third = 'N', .gain = 500},
    {.first = 'L', .second = 'O', .third = 'L', .gain = 1000},
    {.first = 'L', .second = 'E', .third = 'S', .gain = 30},
    {.first = 'L', .second = 'O', .third = 'S', .gain = 250},
    {.first = 'N', .second = 'E', .third = 'O', .gain = 10000},
    {.first = 'N', .second = 'O', .third = 'B', .gain = 20},
    {.first = 'S', .second = 'E', .third = 'L', .gain = 50},
    {.first = 'S', .second = 'O', .third = 'B', .gain = 10},
    {.first = 'S', .second = 'O', .third = 'L', .gain = 40},
    {.first = 'S', .second = 'S', .third = 'L', .gain = -10},
    {.first = 'B', .second = 'B', .third = 'B', .gain = 400},
    {.first = 'E', .second = 'E', .third = 'E', .gain = 400},
    {.first = 'L', .second = 'L', .third = 'L', .gain = 400},
    {.first = 'N', .second = 'N', .third = 'N', .gain = 400},
    {.first = 'O', .second = 'O', .third = 'O', .gain = 400},
    {.first = 'S', .second = 'S', .third = 'S', .gain = 400},
};


/**
 * \brief      Purge the standard input
 */
static void purge(void)
{
    int     c;


    while ( (c = getchar() ) != '\n' && c != EOF )
    {
        ;
    }
}



void clear_screen(void)
{
    // Animation - clear the previous display
    printf("%c[2J", 0x1B);


    // Animation - Move the cursor top-left
    printf("%c[%d;%dH", 0x1B, 1, 1);
}



unsigned char ask_continue(void)
{
    int     continuing = 'y';


    do
    {
        // Get the entry
        printf("Do you want to continue ? : ");
        continuing = fgetc(stdin);


        // Purge the standard input
        purge();
    }
    while ( (continuing != 'y') && (continuing != 'Y') && (continuing != 'n') && (continuing != 'N') );

    return (continuing);
}



unsigned char get_bet(unsigned short credits)
{
    unsigned int        bet     = 0; // Bet
    unsigned char       bet_nok = 1; // Bet OK or not OK?


    do
    {
        // Get the entry
        printf("Enter your bet ([1:3]): ");
        bet = fgetc(stdin);


        // Purge the standard input
        purge();

        bet -= ZERO_ASCII;

        if ( (bet < 1) || (bet > 3) )
        {
            bet_nok = 1;          // Bet Not OK
        }
        else if ( bet > credits )
        {
            printf("You can not bet more than you currently have (bet = %u, credits = %u).\n", bet, credits);
            bet_nok = 1;          // Bet Not OK
        }
        else
        {
            printf("You bet %u credits.\n", bet);
            bet_nok = 0;          // Bet Ok
        }
    }
    while ( bet_nok );

    return (bet);
}



unsigned int get_random_mod(unsigned int modulo)
{
    return (rand() % modulo);
}



unsigned short run_game(void)
{
    unsigned char       belnos_res[LETTERS_PER_ROUND]; // Store the three res in the BELNOS format
    unsigned char       i   = 0;     // For loops
    unsigned char       j   = 0;     // For loops


    for ( i = 0; i < LETTERS_PER_ROUND; ++i )
    {
        belnos_res[i] = belnos[get_random_mod(6)];
    }

    for ( i = 0; i < BIG_LETTERS_LENGTH; ++i )
    {
        for ( j = 0; j < LETTERS_PER_ROUND; ++j )
        {
            switch ( belnos_res[j] )
            {
                case 'B':
                    printf("%s   ", BIG_B[i]);
                    break;

                case 'E':
                    printf("%s   ", BIG_E[i]);
                    break;

                case 'L':
                    printf("%s   ", BIG_L[i]);
                    break;

                case 'N':
                    printf("%s   ", BIG_N[i]);
                    break;

                case 'O':
                    printf("%s   ", BIG_O[i]);
                    break;

                case 'S':
                    printf("%s   ", BIG_S[i]);
                    break;

                default:
                    printf("%s   ", BIG_EMPTY[i]);
            }
        }

        printf("\n");
    }

    printf("\n");

    // Gain part
    // sizeof(gains) / sizeof(Gain_t) is the number of boxes from the gain array
    for ( i = 0; i < (sizeof(gains) / sizeof(Gain_t) ); ++i )
    {
        if ( (belnos_res[0] == gains[i].first) && (belnos_res[1] == gains[i].second) &&
             (belnos_res[2] == gains[i].third) )
        {
#ifdef EASTER_EGG
            switch ( i )
            {
                case 7:
                    printf(
                        " __          __  _                            _          _   _            __  __       _        _       \n");
                    printf(
                        " \\ \\        / / | |                          | |        | | | |          |  \\/  |     | |      (_)      \n");
                    printf(
                        "  \\ \\  /\\  / /__| | ___ ___  _ __ ___   ___  | |_ ___   | |_| |__   ___  | \\  / | __ _| |_ _ __ ___  __ \n");
                    printf(
                        "   \\ \\/  \\/ / _ \\ |/ __/ _ \\| '_ ` _ \\ / _ \\ | __/ _ \\  | __| '_ \\ / _ \\ | |\\/| |/ _` | __| '__| \\ \\/ / \n");
                    printf(
                        "    \\  /\\  /  __/ | (_| (_) | | | | | |  __/ | || (_) | | |_| | | |  __/ | |  | | (_| | |_| |  | |>  <  \n");
                    printf(
                        "     \\/  \\/ \\___|_|\\___\\___/|_| |_| |_|\\___|  \\__\\___/   \\__|_| |_|\\___| |_|  |_|\\__,_|\\__|_|  |_/_/\\_\\ \n");
                    printf("\n\n");
                    break;

                case 12:
                    printf("  _______         _               _          _                _                    ___   \n");
                    printf(
                        " |__   __|       (_)             | |        | |              | |                  |__ \\  \n");
                    printf("    | |_ __ _   _ _ _ __   __ _  | |_ ___   | |__   __ _  ___| | __  _ __ ___   ___  ) | \n");
                    printf(
                        "    | | '__| | | | | '_ \\ / _` | | __/ _ \\  | '_ \\ / _` |/ __| |/ / | '_ ` _ \\ / _ \\/ /  \n");
                    printf("    | | |  | |_| | | | | | (_| | | || (_) | | | | | (_| | (__|   <  | | | | | |  __/_|   \n");
                    printf(
                        "    |_|_|   \\__, |_|_| |_|\\__, |  \\__\\___/  |_| |_|\\__,_|\\___|_|\\_\\ |_| |_| |_|\\___(_)   \n");
                    printf("             __/ |         __/ |                                                         \n");
                    printf("            |___/         |___/                                                          \n");
                    printf("\n\n");
                    break;

                case 16:
                    printf("  _   _         _   _         _   _         _   _       \n");
                    printf(" | \\ | |       | \\ | |       | \\ | |       | \\ | |      \n");
                    printf(" |  \\| | __ _  |  \\| | __ _  |  \\| | __ _  |  \\| | __ _ \n");
                    printf(" | . ` |/ _` | | . ` |/ _` | | . ` |/ _` | | . ` |/ _` |\n");
                    printf(" | |\\  | (_| | | |\\  | (_| | | |\\  | (_| | | |\\  | (_| |\n");
                    printf(" |_| \\_|\\__,_| |_| \\_|\\__,_| |_| \\_|\\__,_| |_| \\_|\\__,_|\n");
                    printf(" | \\ | |       | \\ | |       | \\ | |       | \\ | |      \n");
                    printf(" |  \\| | __ _  |  \\| | __ _  |  \\| | __ _  |  \\| | __ _ \n");
                    printf(" | . ` |/ _` | | . ` |/ _` | | . ` |/ _` | | . ` |/ _` |\n");
                    printf(" | |\\  | (_| | | |\\  | (_| | | |\\  | (_| | | |\\  | (_| |\n");
                    printf(" |_|_\\_|\\__,_|_|_| \\_|\\__,_| |_| \\_|\\__,_|_|_| \\_|\\__,_|\n");
                    printf(" |  _ \\      | |                       | | |            \n");
                    printf(" | |_) | __ _| |_ _ __ ___   __ _ _ __ | | |            \n");
                    printf(" |  _ < / _` | __| '_ ` _ \\ / _` | '_ \\| | |            \n");
                    printf(" | |_) | (_| | |_| | | | | | (_| | | | |_|_|            \n");
                    printf(" |____/ \\__,_|\\__|_| |_| |_|\\__,_|_| |_(_|_)            \n");
                    printf("\n\n");
                    break;

                default:
                    break;
            }
#endif

            return (gains[i].gain);
        }
    }

    return (0);
}