#ifndef INPUT_H
#define INPUT_H

#include "game_math.h"
#include <libdragon.h>

typedef struct
{
    joypad_inputs_t inputs;
    Vec2 joystick;
    Vec2 joystickNorm;
    bool isActive;
    bool isRumbleSupported;
    bool isRumbleActive;
} Gamepad;

typedef struct 
{
    Gamepad gamepads[4];

} InputState;




#define STICK_MAX_RANGE 75
#define STICK_DEADZONE 10

#define GAMEPAD_1 input->gamepads[0]
#define GAMEPAD_2 input->gamepads[1]
#define GAMEPAD_3 input->gamepads[2]
#define GAMEPAD_4 input->gamepads[3]

void input_init(InputState* input);
void input_update(InputState* input);

#endif // INPUT_H