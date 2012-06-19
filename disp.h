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
 *
 */

#include <stdio.h>
#include "quad.h"


extern void displayGameResult (GameState *);
extern void displayTheBoard (GameState *);

extern player_t whoGoesFirst (void);
extern int doYouWantToPlayAgain (void);

extern int getNumber (char *, int, int);
extern int getYNanswer (void);
