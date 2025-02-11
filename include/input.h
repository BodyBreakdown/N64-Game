#ifndef INPUT_H
#define INPUT_H

#include "game_math.h"
#include <libdragon.h>

typedef struct
{
    joypad_inputs_t inputs;
    Vec2 joystick;
    bool isActive;
    bool isRumbleSupported;
    bool isRumbleActive;
} Controller;

Controller controllers[4];

#define STICK_MAX_RANGE 75
#define STICK_DEADZONE 10
#define JOYSTICK_X controllers[i].inputs.stick_x
#define JOYSTICK_Y controllers[i].inputs.stick_y

void input_init(void);
void input_update();

inline Vec2 joystick_value(joypad_port_t port)
{
    return controllers[port].joystick;
}

#endif // INPUT_H