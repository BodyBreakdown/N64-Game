#ifndef GAME_TIME_H
#define GAME_TIME_H

#include <libdragon.h>

extern float accumulator;
extern float deltaTime;
extern float timeElapsed;
extern float fixedDeltaTime;

#define TICK_60_PER_SECOND 0.0166f
#define TICK_30_PER_SECOND 0.0333f
#define TICK_20_PER_SECODN 0.05f

void init_timers(float fixedTickRate);

void update_timers();

#endif


