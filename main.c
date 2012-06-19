#include <unistd.h>
#include <stdlib.h>
#include "quad.h"
#include "disp.h"

int
main (int argc, char *argv[])
{
  player_t turn;
  GameState game;
  move_t themove;
  int opt;

  while ((opt = getopt (argc, argv, "cD:ehl:sVv:20")) != -1)
    {
      switch (opt)
	{
	case 'l':
	  printf ("Level option (-l) is not yet implemented!\n");
	  printf (" -- you requested level %s.\n", optarg);
	  break;
	case 'e':
	  printf ("Expert option (-e) is not yet implemented!\n");
	  break;
	case 's':
	  printf ("Smiley option (-s) is not yet implemented!\n");
	  break;
	case 'v':
	  printf ("Verbose option (-v) is not yet implemented!\n");
	  printf (" -- you requested verbosity level %s.\n", optarg);
	  break;
	case '2':
	  printf ("2 player option (-2) is not yet implemented!\n");
	  break;
	case '0':
	  printf
	    ("Computer vs Computer option (-0) is not yet implemented!\n");
	  break;
	case 'D':
	  printf ("Debug option (-D) is not yet implemented!\n");
	  printf (" -- you requested Debug level %s.\n", optarg);
	  break;
	case 'V':
	  printf
	    ("Quad Version 0.8a By Jeremy Madea jmadea@cs.millersv.edu\n");
	  printf (" Please Play me!\n");
	  exit (0);
	  break;
	case 'h':
	  printf ("Usage: quad [-v]\n");
	  exit (0);
	  break;
	case '?':
	  printf ("Invocation error... exiting\n");
	  exit (1);
	  break;
	}
    }




  do
    {
      turn = whoGoesFirst ();
      initGameState (&game, turn);
      displayTheBoard (&game);
      while (!gameOver (&game))
	{
	  themove = getMove (turn, &game);
	  playTheMove (turn, themove, &game);
	  turn = other (turn);
	  displayTheBoard (&game);
	}
      displayGameResult (&game);

    }
  while (doYouWantToPlayAgain ());

  exit (0);
}
