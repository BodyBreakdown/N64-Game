#ifndef SCENES_H
#define SCENES_H

#include "camera.h"
#include "game_object.h"
#include "game_time.h"
#include "game_math.h"
#include "input.h"
#include "text.h"
#include "render_helper.h"
#include <t3d/t3ddebug.h>
#include <t3d/t3dmodel.h>
#include <t3d/tpx.h>


typedef enum GameState
{
    LOGOS = 0,
    //TITLE = 1,
    //OPTIONS = 2,
    GAMEPLAY = 3,
} GameState;

const static rdpq_textparms_t debugParms = {
    .width = 100,
    .height = 100
};

extern GameState gameState;

void LogosStart(void);
void LogosUpdate(void);
void LogosDraw(void);
void LogosUnload(void);
int LogosEnd(void);

void TitleStart(void);
void TitleUpdate(void);
void TitleDraw(void);
void TitleUnload(void);
int TitleEnd(void);

void OptionsStart(void);
void OptionsUpdate(void);
void OptionsDraw(void);
void OptionsUnload(void);
int OptionsEnd(void);

void GameStart(void);
void GameUpdate(void);
void GameDraw(void);
void GameUnload(void);
int GameEnd(void);

#endif // SCENE_H