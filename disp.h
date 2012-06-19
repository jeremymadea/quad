#include <stdio.h>
#include "quad.h"


extern void displayGameResult (GameState *);
extern void displayTheBoard (GameState *);

extern player_t whoGoesFirst (void);
extern int doYouWantToPlayAgain (void);

extern int getNumber (char *, int, int);
extern int getYNanswer (void);
