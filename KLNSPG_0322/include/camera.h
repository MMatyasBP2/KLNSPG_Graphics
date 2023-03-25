#ifndef CAMERA_H
#define CAMERA_H
#include "utils.h"

typedef struct Camera
{
    vec3 position;
    vec3 rotation;
    vec3 speed;
	vec3 rotationSpeed;
} Camera;

void init_camera(Camera* camera);
void update_camera(Camera* camera, double time);
void set_view(const Camera* camera);
void set_camera_speed(Camera* camera, double speed);
void set_camera_side_speed(Camera* camera, double speed);
void set_camera_vert_speed(Camera* camera, double speed);
void set_camera_rotation_speed_x(Camera* camera, double speed);
void set_camera_rotation_speed_y(Camera* camera, double speed);
void set_camera_rotation_speed_z(Camera* camera, double speed);

#endif /* CAMERA_H */