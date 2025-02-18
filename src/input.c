#include "input.h"

InputState input;

#define CURRENT_PAD input.gamepads[i]
#define JOYSTICK_X input.gamepads[i].inputs.stick_x
#define JOYSTICK_Y input.gamepads[i].inputs.stick_y

void input_init()
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

void input_update()
{
    joypad_poll();
    s8 x;
    s8 y;
    for (int i = 0; i < 4; i++)
    {
        if (joypad_is_connected(i))
        {
            CURRENT_PAD.isActive = true;
            CURRENT_PAD.inputs = joypad_get_inputs(i);
            
            //Clamp the joystick to a given range
            x = s8_clamp(JOYSTICK_X, -STICK_MAX_RANGE, STICK_MAX_RANGE);
            y = s8_clamp(JOYSTICK_Y, -STICK_MAX_RANGE, STICK_MAX_RANGE);

            //Convert to floating point and zero out anything below the deadzone 
            CURRENT_PAD.joystick.x = abs(x) > STICK_DEADZONE ? (float)x / STICK_MAX_RANGE_F : 0.0f;
            CURRENT_PAD.joystick.y = abs(y) > STICK_DEADZONE ? (float)y / STICK_MAX_RANGE_F : 0.0f;
            
            //Circularize the range
            CURRENT_PAD.joystick.x *= sqrtf(1.0f - (CURRENT_PAD.joystick.y * CURRENT_PAD.joystick.y / 2.0f));
            CURRENT_PAD.joystick.y *= sqrtf(1.0f - (CURRENT_PAD.joystick.x * CURRENT_PAD.joystick.x / 2.0f));
        }
        else
        {
            CURRENT_PAD.isActive = false;
        }
    }
}
