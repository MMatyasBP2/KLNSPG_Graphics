#ifndef CAMERA_H
#define CAMERA_H

#include "utils.h"

/* Camera def */
typedef struct Camera
{
    vec3 worldPosition;
    vec3 position;
    vec3 rotation;
    vec3 speed;
} Camera;

struct Action
{
    int move_forward;
    int move_backward;
    int step_left;
    int step_right;
} action;

/*Initialize the camera to the start position. */
void init_camera(Camera *camera);

/* Update the position of the camera. */
void update_camera(Camera *camera, double time);

/* Apply the camera settings to the view transformation. */
void set_view(const Camera *camera);

/* Set the horizontal and vertical rotation of the view angle. */
void rotate_camera(Camera *camera, double horizontal, double vertical);

/* Set the speed of forward and backward motion. */
void set_camera_speed(Camera *camera, double speed);

/* Set the speed of left and right side steps. */
void set_camera_side_speed(Camera *camera, double speed);

/* Main function to call collision checks*/
int check_collisions(vec3 newPosition);

/* Function that calculates collision */
int calc_collision(vec3 newPosition, float posX, float posY, float boxSizeX, float boxSizeY);

#endif /* CAMERA_H */