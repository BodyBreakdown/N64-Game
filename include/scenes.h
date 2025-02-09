#ifndef SCENES_H
#define SCENES_H

#include <libdragon.h>
#include "game_time.h"
#include "game_object.h"
#include <t3d/t3d.h>
#include <t3d/t3dmodel.h>
#include <t3d/t3ddebug.h>
#include <t3d/tpx.h>
#include "camera.h"
#include "text.h"

typedef enum GameState
{
    LOGOS = 0,
    //TITLE = 1,
    //OPTIONS = 2,
    //GAMEPLAY = 3,
} GameState;

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