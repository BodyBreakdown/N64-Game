#include "scenes.h"

static GameObject* sky;
static GameObject* plane;
static GameObject* logo;
static GameObject* logo2;

float rotAngle = 0;

static Capsule logoCap;
static Capsule testCap;
static bool isCollide;
static bool hasDrawn = false;

bool CheckCollisionCapsules(Capsule* a, Capsule* b)
{
    float dx = a->position.x - b->position.x;
    float dz = a->position.z - b->position.z;
    float radiusSum = a->radius + b->radius;
    if (dx * dx + dz * dz > radiusSum * radiusSum)
    {
        return 0;
    }
    float aTop = a->position.y + a->height;
    float bTop = b->position.y + b->height;
    float aBottom = a->position.y;
    float bBottom = b->position.y;

    return !(aTop < bBottom || bTop < aBottom);
}

void LogosStart(void)
{
    mainCam.position = (T3DVec3) { { 0, 15, -30 } };

    logo = game_object_create(0, t3d_model_load("rom:/human.t3dm"), 0);
    t3d_vec3_scale(&logo->scale, &logo->scale, 0.2f);
    logoCap = (Capsule) {
        .height = 50,
        .radius = 4
    };
    
    logo2 = game_object_create(1, t3d_model_load("rom:/human.t3dm"), 0);
    t3d_vec3_scale(&logo2->scale, &logo2->scale, 0.2f);
    testCap = (Capsule) { .height = 50, .radius = 4 };
    
    t3d_mat4fp_from_srt_euler(logo2->matrix, logo2->scale.v, logo2->rotation.v, logo2->position.v);

    plane = game_object_create(2, t3d_model_load("rom:/test.t3dm"), 0);
    t3d_vec3_scale(&plane->scale, &plane->scale, 1.0f);
    plane->position.y = -10;
    t3d_mat4fp_from_srt_euler(plane->matrix, plane->scale.v, plane->rotation.v, plane->position.v);

    sky = game_object_create(3, t3d_model_load("rom:/skybox.t3dm"), 1);
    t3d_vec3_scale(&sky->scale, &sky->scale, 3.0f);
    t3d_mat4fp_from_srt_euler(sky->matrix, sky->scale.v, sky->rotation.v, sky->position.v);
}

void LogosUpdate(void)
{
    T3DVec3 forwardMove;
    T3DVec3 strafeMove;
    T3DVec3 move;

    t3d_vec3_scale(&strafeMove, &mainCam.right, GAMEPAD_1.joystick.x);
    t3d_vec3_scale(&forwardMove, &mainCam.forward, GAMEPAD_1.joystick.y);
    t3d_vec3_add(&move, &forwardMove, &strafeMove);
    t3d_vec3_scale(&move, &move, deltaTime * 60);
    t3d_vec3_add(&logo->position, &logo->position, &move);

    logoCap.position = logo->position;
    testCap.position = (T3DVec3) { { 40, 0, 0 } };
    isCollide = CheckCollisionCapsules(&logoCap, &testCap);

    if (t3d_vec3_len(&move) > 0.00001f)
    {
        logo->rotation.y += (wrap_angle(fm_atan2f(-move.x, move.z) - logo->rotation.y)) * 12 * deltaTime;
    }

    if (GAMEPAD_1.inputs.cstick_x != 0)
    {
        rotAngle += deltaTime * s8_sign(GAMEPAD_1.inputs.cstick_x) * 3;
    }

    float cos, sin;

    fm_sincosf(rotAngle, &sin, &cos);

    mainCam.position.x = logo->position.x + 40 * sin;
    mainCam.position.z = logo->position.z + 40 * cos;
    mainCam.position.y = logo->position.y + 25;

    mainCam.target.x = logo->position.x;
    mainCam.target.y = logo->position.y + 15;
    mainCam.target.z = logo->position.z;

    //sky->position.x = mainCam.position.x;
    //sky->position.y = mainCam.position.y + 60;
    //sky->position.z = mainCam.position.z;

    //t3d_mat4fp_set_pos(sky->matrix, sky->position.v);
    t3d_mat4fp_from_srt_euler(logo->matrix, logo->scale.v, logo->rotation.v, logo->position.v);
}

void LogosDraw(void)
{
    t3d_matrix_push_pos(1);
    
    //game_object_draw(sky);

    fog_enable((color_t) { 160, 40, 30, 0 }, 50, 150);

    game_object_draw(plane);
    game_object_draw(logo);
    game_object_draw(logo2);



    t3d_matrix_pop(1);

    rdpq_text_printf(&debugParms, 1, 8, 10, VecToString(GAMEPAD_1.joystick.v, 2));
    rdpq_text_printf(&debugParms, 1, 8, 20, "%i", isCollide);
}