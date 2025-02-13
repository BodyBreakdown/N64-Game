#include "input.h"

#define CURRENT_PAD input->gamepads[i]
#define JOYSTICK_X input->gamepads[i].inputs.stick_x
#define JOYSTICK_Y input->gamepads[i].inputs.stick_y

void input_init(InputState* input)
{
    joypad_init();
    for (int i = 0; i < 4; i++)
    {
        if (joypad_is_connected(i))
        {
            CURRENT_PAD.isActive = true;
            CURRENT_PAD.isRumbleSupported = joypad_get_rumble_supported(i);
        }
    }
}

void input_update(InputState* input)
{
    joypad_poll();
    for (int i = 0; i < 4; i++)
    {
        if (joypad_is_connected(i))
        {
            CURRENT_PAD.isActive = true;
            CURRENT_PAD.inputs = joypad_get_inputs(i);
            CURRENT_PAD.joystick.x = abs(JOYSTICK_X) > STICK_DEADZONE ? i8_bit_clamp(JOYSTICK_X, -STICK_MAX_RANGE, STICK_MAX_RANGE) : 0;
            CURRENT_PAD.joystick.y = abs(JOYSTICK_Y) > STICK_DEADZONE ? i8_bit_clamp(JOYSTICK_Y, -STICK_MAX_RANGE, STICK_MAX_RANGE) : 0;
            CURRENT_PAD.joystickNorm = vec2_normalize(CURRENT_PAD.joystick);
        }
        else
        {
            CURRENT_PAD.isActive = false;
        }
    }
}
