#include "camera.h"

Camera mainCam;


Camera camera_create(T3DViewport* viewport, float fov, float near, float far)
{
    Camera cam = (Camera)
    {
        .position = (T3DVec3){{0, 0, 0}},
        .target = (T3DVec3){{0, 0, 0}},
        .up = (T3DVec3){{0, 1, 0}},
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
    //vec3_directions_from_matrix(&cam->right, &cam->up, &cam->forward, &cam->viewport->matCamProj);
    //t3d_vec3_diff(&cam->forward, &cam->target, &cam->position);
    vec3_forward_from_matrix(&cam->forward, &cam->viewport->matCamProj);
    cam->forward.y = 0;
    t3d_vec3_norm(&cam->forward);

    vec3_right_from_matrix(&cam->right, &cam->viewport->matCamProj);
    cam->right.y = 0;
    t3d_vec3_norm(&cam->right);


    t3d_viewport_set_projection(cam->viewport, cam->fov, cam->nearClip, cam->farPlane);
    t3d_viewport_look_at(cam->viewport, &cam->position, &cam->target, &(T3DVec3){{0, 1, 0}});
}