#ifndef GAME_H
#define GAME_H

#include "ball.h"
#include "pad.h"

typedef struct Game
{
    Ball ball;
    Pad left_pad;
    Pad right_pad;
    int width;
    int height;
    int leftPoints;
    int rightPoints;
} Game;

void resize_game(Game* game, int width, int height);
void restart_game(Game* game);

/**
 * Update the state of the game.
 * @param time elapsed time in seconds
 */
void update_game(Game* game, double time);
void move_left_pad(Game* game, float position);
void move_right_pad(Game* game, float position);

#endif /* GAME_H */