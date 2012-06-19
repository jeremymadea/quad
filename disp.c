#include <stdlib.h>
#include "disp.h"

#define BUFSIZE  80

/************************/
/* Forward Declarations */
/************************/

void printLayout (void);
void printPieces (void);
void printBoard (board_t);
void printPieceSet (pieceset_t);
void printPiecesVerbose (void);



/***********************/
/* Interface Functions */
/***********************/

void
displayGameResult (GameState * thegame)
{
  if ((thegame->GameStatus) && (thegame->GameStatus != 1))
    {
      printf (" ***   The game was a tie!   ***\n\n");
      return;
    }
  else
    {
      if (thegame->LastToMove == Human)
	{
	  printf (" ***   You won the game!   ***\n\n");
	  return;
	}
      else
	{
	  printf (" ***   I won the game!   ***\n\n");
	  return;
	}
    }
}


void
displayTheBoard (GameState * thegame)
{
  printf ("\n*** Moves made: %d ***\n\n", thegame->NumMoves);
  printPieces ();
  printBoard (thegame->TheBoard);
  printPieceSet (thegame->ThePieces);
  if (thegame->PieceInHand < 0)
    {
      printf ("There are no more pieces to play.\n");
    }
  else
    {
      printf ("The piece to be played is %d.\n", thegame->PieceInHand);
    }
  return;
};


int
doYouWantToPlayAgain (void)
{
  printf ("Do you want to play again? ");
  return getYNanswer ();
}


player_t
whoGoesFirst (void)
{
  printf ("Do you want to go first? ");
  if (getYNanswer ())
    {
      return Human;
    }
  else
    {
      return Computer;
    }
}

int
getNumber (char *prompt, int lo, int hi)
{
  int num;
  static char buf[10];

  do
    {
      printf ("%s", prompt);
      if (!fgets (buf, 10, stdin))
	{
	  printf ("\nEOF or error encountered while getting number!\n");
	  exit (0);
	}
      sscanf (buf, "%d", &num);
    }
  while (!isdigit (buf[0]) || num < lo || num > hi);

  return num;
}




int
getYNanswer (void)
{
  char buffer[BUFSIZE];
  buffer[0] = 0;
  do
    {
      printf ("[yn] > ");
      if (!fgets (buffer, BUFSIZE, stdin))
	{
	  printf ("\nEOF or error occured while reading from stdin!\n");
	  exit (0);
	}
      buffer[0] = tolower (buffer[0]);
    }
  while (buffer[0] != 'y' && buffer[0] != 'n');

  return (buffer[0] == 'y') ? 1 : 0;
}



/****************************/
/* Implementation Functions */
/****************************/



/************************************/
/* Show how we number our spaces... */

void
printLayout (void)
{

  printf ("The board is layed out like this:\n"
	  "|----|----|----|----|\n"
	  "|  0 |  1 |  2 |  3 |\n"
	  "|----|----|----|----|\n"
	  "|  4 |  5 |  6 |  7 |\n"
	  "|----|----|----|----|\n"
	  "|  8 |  9 | 10 | 11 |\n"
	  "|----|----|----|----|\n"
	  "| 12 | 13 | 14 | 15 |\n" "|----|----|----|----|\n\n");
}





/************************************/
/* Show how we number our pieces... */

void
printPieces (void)
{

  printf ("The pieces are numbered as follows:\n"
	  "  0  0  0  0  0  0  0  0  1  1  1  1  1  1  1  1  [0=black  1=white]\n"
	  "  0  0  0  0  1  1  1  1  0  0  0  0  1  1  1  1  [0=short  1=tall ]\n"
	  "  0  0  1  1  0  0  1  1  0  0  1  1  0  0  1  1  [0=square 1=round]\n"
	  "  0  1  0  1  0  1  0  1  0  1  0  1  0  1  0  1  [0=hollow 1=solid]\n"
	  "-------------------------------------------------\n"
	  "  0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15\n");
}



void
printPiecesVerbose (void)
{
  printf (" 0  --  Black Short Square Hollow\n"
	  " 1  --  Black Short Square Solid \n"
	  " 2  --  Black Short Round  Hollow\n"
	  " 3  --  Black Short Round  Solid \n"
	  " 4  --  Black Tall  Square Hollow\n"
	  " 5  --  Black Tall  Square Solid \n"
	  " 6  --  Black Tall  Round  Hollow\n"
	  " 7  --  Black Tall  Round  Solid \n"
	  " 8  --  White Short Square Hollow\n"
	  " 9  --  White Short Square Solid \n"
	  "10  --  White Short Round  Hollow\n"
	  "11  --  White Short Round  Solid \n"
	  "12  --  White Tall  Square Hollow\n"
	  "13  --  White Tall  Square Solid \n"
	  "14  --  White Tall  Round  Hollow\n"
	  "15  --  White Tall  Round  Solid \n");

}

/* Takes a board and displays it */
void
printBoard (board_t board)
{
  char I, J;
  printf ("\n");
  for (I = 0; I < 16; I += 4)
    {
      printf ("|----|----|----|----|\n|");
      for (J = 0; J < 4; J++)
	{
	  if (board[I + J] != -1)
	    {
	      printf (" %2d |", board[I + J]);
	    }
	  else
	    {
	      printf ("    |");
	    }
	}
      printf ("\n");
    }
  printf ("|----|----|----|----|\n");
  printf ("\n");
  return;
}



void
printPieceSet (pieceset_t pieces)
{
  int I;

  printf ("Pieces still available: ");
  for (I = 0; I < NUMPIECES; I++)
    {
      if (pieces[I])
	{
	  printf (" %d ", I);
	}
    }
  printf ("\n");
  return;
}
