/**
 * @author hbuyse
 * @date 13/04/2016
 *
 * @file player.c
 *
 * @brief Source file containing the functions about players
 */

#include <stdio.h>          // fprintf

#include "player.h"          // Player_t

#ifndef __OSX__
    #include <libintl.h>      // gettext, bindtextdomain, textdomain
#define _(STRING) gettext(STRING)
#else
#define _(STRING) STRING
#endif


void dump_player(Player_t player)
{
    fprintf(stdout, _("                       ╔═════════╦═════╦═══════╗\n") );
    fprintf(stdout, _("                       ║ CREDITS ║ BET ║ GAIN  ║\n") );
    fprintf(stdout, _("                       ╠═════════╬═════╬═══════╣\n") );
    fprintf(stdout, _("                       ║ %7d ║ %3u ║ %5d ║\n"), player.credits, player.bet, player.gain);
    fprintf(stdout, _("                       ╚═════════╩═════╩═══════╝\n") );
}



char* get_player_name(Player_t p)
{
    return (p.name);
}



unsigned short get_player_credits(Player_t p)
{
    return (p.credits);
}



unsigned short get_player_gain(Player_t p)
{
    return (p.gain);
}



unsigned char get_player_bet(Player_t p)
{
    return (p.bet);
}