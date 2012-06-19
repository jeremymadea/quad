#include <stdio.h>
#include <stdlib.h>
#include "quad.h"
#include "disp.h"


#define NUMWINS  10		/* There are ten rows we can win on. */
#define WINSIZE  4		/* It takes four pieces to win       */
#define BUFSIZE  80
#define LIMIT    100
#define MAXMOVES 16

const int AllWins[NUMWINS][WINSIZE] = { {0, 1, 2, 3},
{4, 5, 6, 7},
{8, 9, 10, 11},
{12, 13, 14, 15},
{0, 4, 8, 12},
{1, 5, 9, 13},
{2, 6, 10, 14},
{3, 7, 11, 15},
{0, 5, 10, 15},
{3, 6, 9, 12}
};

/************************/
/* Forward Declarations */
/************************/

void initBoard (board_t);
void initPieces (pieceset_t);
int randomPiece (void);
int isWin (int, int, int, int);

move_t getHumanMove (GameState *);
move_t getComputerMove (GameState *);
void updateGameStatus (GameState *);
int gameWon (GameState *);
move_t computeBestMove (GameState *, int *, int);
int staticEval (GameState *);


/***********************/
/* Interface Functions */
/***********************/

void
initGameState (GameState * thegame, player_t theplayer)
{
  int startpiece = randomPiece ();

  printf ("Initializing game...\n");
  thegame->GameStatus = 0;
  thegame->NumMoves = 0;
  thegame->LastToMove = other (theplayer);
  thegame->PieceInHand = startpiece;
  printf ("The first piece is %d. Random piece was %d.\n",
	  thegame->PieceInHand, startpiece);
  initBoard (thegame->TheBoard);
  initPieces (thegame->ThePieces);
  thegame->ThePieces[startpiece] = 0;
}


int
gameOver (GameState * thegame)
{
  return (thegame->GameStatus);
}

move_t
getMove (player_t theplayer, GameState * thegame)
{
  move_t move;
  if (theplayer == Human)
    {
      move = getHumanMove (thegame);
    }
  else
    {
      move = getComputerMove (thegame);
    }
  return move;
}

void
playTheMove (player_t theplayer, move_t themove, GameState * thegame)
{
  thegame->TheBoard[themove.Square] = thegame->PieceInHand;
  thegame->PieceInHand = themove.Piece;
  if (themove.Piece != -1)
    {
      thegame->ThePieces[themove.Piece] = 0;
    }
  thegame->LastToMove = theplayer;
  thegame->NumMoves++;
  updateGameStatus (thegame);
  return;
};


player_t
other (player_t theplayer)
{
  return ((theplayer) ? 0 : 1);
};


/****************************/
/* Implementation Functions */
/****************************/


/**********************************************************************/
/* Takes four pieces and determines whether they are a winning combo. */
/* Returns 0 if it is not a win and an int between 1 and 12 if it is. */
/* This int will have a 1 in the bit position(s) where the win(s) is. */

int
isWin (int a, int b, int c, int d)
{

  if ((a < 0) || (b < 0) || (c < 0) || (d < 0))
    return 0;			/* No win if a space is empty */

  return (~((a ^ b) | (a ^ c) | (a ^ d)) & (0xF));
}





/*******************************************/
/* Return a random number between 0 and 15 */
/* Primarily used when the computer needs  */
/* to give the first piece to the human.   */

int
randomPiece (void)
{
  int i, j;

  i = RAND_MAX / 15;
  i *= 15;
  while ((j = rand ()) >= i)
    {
      continue;
    }

  return (j % 16);
}


/****************************/
/* Sets all the spaces on the board to -1 indicating they are unoccupied */

void
initBoard (board_t board)
{
  char I;
  for (I = 0; I < NUMSQUARES; I++)
    {
      board[I] = -1;
    }
}



/* Sets all the pieces in the set to 1 indicating they are available */
void
initPieces (pieceset_t pieces)
{
  char I;
  for (I = 0; I < NUMPIECES; I++)
    {
      pieces[I] = 1;
    }
}


move_t
getHumanMove (GameState * thegame)
{
  move_t move;
  do
    {
      move.Square = getNumber ("Which square? [0..15] > ", 0, 15);
    }
  while (thegame->TheBoard[move.Square] != -1);
  if (thegame->NumMoves < (MAXMOVES - 1))
    {
      do
	{
	  move.Piece = getNumber ("Which piece?  [0..15] > ", 0, 15);
	}
      while (!thegame->ThePieces[move.Piece]);
    }
  else
    {
      printf ("No pieces left...\n");
    }
  return move;
}


move_t
getComputerMove (GameState * thegame)
{
  move_t move;
  int depth = 2;
  int score;
  if (thegame->NumMoves > 5)
    depth++;
  if (thegame->NumMoves > 10)
    depth += 2;

  move = computeBestMove (thegame, &score, depth);
  printf ("computer moves [sq,pc] %d,%d with a score of %d\n",
	  move.Square, move.Piece, score);
  return move;
}

move_t
computeBestMove (GameState * position, int *score, int godeeper)
{
  int curbestscore, tempscore;
  move_t curbestmove, tempmove;
  GameState temp_position;
  player_t thisplayer = other (position->LastToMove);

  if ((!godeeper) || (gameOver (position)))
    {
      curbestmove.Square = -1;
      curbestmove.Piece = -1;
      curbestscore = staticEval (position);
    }
  else
    {
      if (thisplayer == Computer)
	{
	  curbestscore = -LIMIT;
	  for (tempmove.Square = 0;
	       tempmove.Square < NUMSQUARES; tempmove.Square++)
	    {
	      if (position->TheBoard[tempmove.Square] != -1)
		{
		  continue;
		}

	      for (tempmove.Piece = 0;
		   tempmove.Piece < NUMPIECES; tempmove.Piece++)
		{
		  if (position->ThePieces[tempmove.Piece] != 1)
		    {
		      if (position->NumMoves >= (MAXMOVES - 1))
			{
			  tempmove.Piece = -1;	/* For last 1/2 ply */
			}
		      else
			continue;
		    }

		  temp_position = *position;
		  playTheMove (thisplayer, tempmove, &temp_position);
		  computeBestMove (&temp_position, &tempscore, godeeper - 1);
		  if ((curbestscore < tempscore) ||
		      ((curbestscore == tempscore) && !(rand () % 7)))
		    {
		      curbestscore = tempscore;
		      curbestmove = tempmove;
		    }
		  if (tempmove.Piece == -1)
		    break;	/* For last 1/2 ply */
		}
	    }
	}
      else
	{
	  curbestscore = LIMIT;
	  for (tempmove.Square = 0;
	       tempmove.Square < NUMSQUARES; tempmove.Square++)
	    {
	      if (position->TheBoard[tempmove.Square] != -1)
		{
		  continue;
		}
	      for (tempmove.Piece = 0;
		   tempmove.Piece < NUMPIECES; tempmove.Piece++)
		{
		  if (position->ThePieces[tempmove.Piece] != 1)
		    {
		      if (position->NumMoves >= (MAXMOVES - 1))
			{
			  tempmove.Piece = -1;	/* For last 1/2 ply */
			}
		      else
			continue;
		    }
		  temp_position = *position;
		  playTheMove (thisplayer, tempmove, &temp_position);
		  computeBestMove (&temp_position, &tempscore, godeeper - 1);
		  if ((curbestscore > tempscore) ||
		      ((curbestscore == tempscore) && !(rand () % 7)))
		    {
		      curbestscore = tempscore;
		      curbestmove = tempmove;
		    }
		  if (tempmove.Piece == -1)
		    break;	/* For last 1/2 ply */
		}
	    }
	}
    }
  *score = curbestscore;
  return curbestmove;
}


int
staticEval (GameState * position)
{
  int score = (position->LastToMove == Human) ? -1 : 1;

  if (position->GameStatus == 1)
    {
      score *= 100;
    }
  else
    {
      score = 0;
    }
  return score;
}




void
updateGameStatus (GameState * thegame)
{
  if (gameWon (thegame))
    {
      thegame->GameStatus = 1;
    }
  else
    {
      if (thegame->NumMoves >= 16)
	{
	  thegame->GameStatus = 0;
	}
    }
  return;
}

int
gameWon (GameState * thegame)
{
  int win;

  for (win = 0; win < NUMWINS; win++)
    {
      if (isWin (thegame->TheBoard[AllWins[win][0]],
		 thegame->TheBoard[AllWins[win][1]],
		 thegame->TheBoard[AllWins[win][2]],
		 thegame->TheBoard[AllWins[win][3]]))
	{
	  return 1;
	}
    }
  return 0;
}
