/*
 * Copyright 1996-2012 Jeremy Madea
 *
 * This file is part of quad.
 *
 * Quad is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 *
 * Quad is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with quad; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */ 

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
