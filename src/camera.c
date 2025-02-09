#include "camera.h"

Camera camera_create(T3DViewport* viewport, float fov, float near, float far)
{
    Camera cam = (Camera)
    {
        .position = (T3DVec3){{0, 0, 0}},
        .target = (T3DVec3){{0, 0, 0}},
        .fov = fov,
        .nearClip = near,
        .farPlane = far,
        .viewport = viewport
    };
    t3d_viewport_set_projection(viewport, fov, near, far);
    return cam;
}

void camera_update(Camera* cam)
{
    
    t3d_viewport_set_projection(cam->viewport, cam->fov, cam->nearClip, cam->farPlane);
    t3d_viewport_look_at(cam->viewport, &cam->position, &cam->target, &(T3DVec3){{0, 1, 0}});
}