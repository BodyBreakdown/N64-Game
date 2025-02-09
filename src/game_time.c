#include "game_time.h"

float accumulator;
float deltaTime;
float timeElapsed;
float fixedDeltaTime;

void init_timers(float fixedTickRate)
{
    accumulator = 0;
    deltaTime = 0;
    timeElapsed = 0;
    fixedDeltaTime = fixedTickRate;
}

void update_timers()
{
    deltaTime = display_get_delta_time();
    timeElapsed += deltaTime;
    accumulator += deltaTime;
}