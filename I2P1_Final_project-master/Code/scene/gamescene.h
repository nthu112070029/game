#ifndef GAMESCENE_H_INCLUDED
#define GAMESCENE_H_INCLUDED
#include "scene.h"
#include "../element/element.h"
#include "../element/charater.h"
#include "../element/floor.h"
#include "../element/teleport.h"
#include "../element/tree.h"
#include "../element/projectile.h"
#include "../element/tower.h"
#include "../element/poft.h"
#include "../element/ball.h"
#include "../element/castle.h"
#include "../element/money_col.h"
#include "../element/camp.h"
#include "../element/monster.h"

/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    Monster_L,
    camp_L,
    Character_L,
    Projectile_L,
    PofT_L,
    Tower_L,//must below PofT_L
    Castle_L,
    money_col_L,
    Ball_L,
    
}EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;

} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *const pGameSceneObj);
void game_scene_draw(Scene *const pGameSceneObj);
void game_scene_destroy(Scene *const pGameSceneObj);

#endif
