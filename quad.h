#ifndef QUAD_H
#define QUAD_H

#define NUMSQUARES 16
#define NUMPIECES  16


typedef int player_t;

typedef struct
{
  int Square;
  int Piece;
} move_t;

typedef int board_t[NUMSQUARES];
typedef int pieceset_t[NUMPIECES];

typedef struct
{
  int GameStatus;
  int NumMoves;
  int PieceInHand;
  player_t LastToMove;
  board_t TheBoard;
  pieceset_t ThePieces;
} GameState;

/*
  const player_t Human    = 1;
  const player_t Computer = 0;
*/

#define Human 1
#define Computer 0


extern void initGameState (GameState *, player_t);
extern int gameOver (GameState *);

extern move_t getMove (player_t, GameState *);
extern void playTheMove (player_t, move_t, GameState *);
extern player_t other (player_t);

#endif
