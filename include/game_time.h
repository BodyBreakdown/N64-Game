#ifndef GAME_TIME_H
#define GAME_TIME_H
#include <libdragon.h>

static float accumulator;
static float deltaTime;
static float timeElapsed;
static float fixedDeltaTime;

#define TICK_60_PER_SECOND 0.0166f
#define TICK_30_PER_SECOND 0.0333f
#define TICK_20_PER_SECODN 0.05f

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

#endif


