#ifndef CAMERA_H
#define CAMERA_H

#include <t3d/t3d.h>
#include <t3d/t3dmath.h>
#include "game_math.h"

typedef struct 
{
    T3DVec3 position;
    T3DVec3 target;
    T3DVec3 right;
    T3DVec3 up;
    T3DVec3 forward;
    float fov;
    float nearClip;
    float farPlane;
    T3DViewport* viewport;
} Camera;

extern Camera mainCam;

Camera camera_create(T3DViewport* viewport, float fov, float near, float far);
void camera_update(Camera* cam);


#endif