#include "input.h"

void input_init(void)
{
    //controllers[4] = (Controller){};
    joypad_init();
    for (int i = 0; i < 4; i++)
    {
        
        if (joypad_is_connected(i))
        {
            controllers[i].isActive = true;
            controllers[i].isRumbleSupported = joypad_get_rumble_supported(i);
        }
    }
}

void input_update()
{
    joypad_poll();
    for (int i = 0; i < 4; i++)
    {
        if (joypad_is_connected(i))
        {
            controllers[i].isActive = true;
            controllers[i].inputs = joypad_get_inputs(i);
            controllers[i].joystick.x = abs(JOYSTICK_X) > STICK_DEADZONE ? i8_bit_clamp(JOYSTICK_X, -STICK_MAX_RANGE, STICK_MAX_RANGE) : 0;
            controllers[i].joystick.y = abs(JOYSTICK_Y) > STICK_DEADZONE ? i8_bit_clamp(JOYSTICK_Y, -STICK_MAX_RANGE, STICK_MAX_RANGE) : 0;
        }
        else
        {
            controllers[i].isActive = false;
        }
    }
}
