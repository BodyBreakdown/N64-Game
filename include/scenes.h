#ifndef SCENES_H
#define SCENES_H

#include "camera.h"
#include "game_object.h"
#include "game_time.h"
#include "input.h"
#include "text.h"
#include <libdragon.h>
#include <t3d/t3d.h>
#include <t3d/t3ddebug.h>
#include <t3d/t3dmodel.h>
#include <t3d/tpx.h>

typedef enum GameState
{
    LOGOS = 0,
    //TITLE = 1,
    //OPTIONS = 2,
    //GAMEPLAY = 3,
} GameState;

extern GameState gameState;

void LogosStart(void);
void LogosUpdate(InputState* input);
void LogosDraw(void);
void LogosUnload(void);
int LogosEnd(void);

void TitleStart(void);
void TitleUpdate(InputState* input);
void TitleDraw(void);
void TitleUnload(void);
int TitleEnd(void);

void OptionsStart(void);
void OptionsUpdate(InputState* input);
void OptionsDraw(void);
void OptionsUnload(void);
int OptionsEnd(void);

void GameStart(void);
void GameUpdate(InputState* input);
void GameDraw(void);
void GameUnload(void);
int GameEnd(void);

#endif // SCENE_H