#ifndef BALL_H
#define BALL_H

typedef struct Ball
{
    float x;
    float y;
    float radius;
    float speed_x;
    float speed_y;
    float currentRotation;
} Ball;

void move_ball(Ball* ball, float x, float y);
void start_ball(Ball* ball, float x, float y);

/**
 * Update the ball.
 * @param time elapsed time in seconds.
 */
void update_ball(Ball* ball, double time);

#endif /* BALL_H */