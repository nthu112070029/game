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
#include "../element/cannon.h"
#include "../element/kill_num.h"
#include "../element/chara_HP.h"
/*
   [game scene object]
*/
typedef enum EleType
{
    Floor_L,
    Teleport_L,
    Tree_L,
    camp_L,
    Projectile_L,
    PofT_L,
    Tower_L,
    Castle_L,
    money_col_L,
    Monster_L,
    Cannon_L,
    Character_L,
    kill_num_L,
    chara_HP_L,
    Ball_L, //ball should be last
    
}EleType;
typedef struct _GameScene
{
    ALLEGRO_BITMAP *background;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    
} GameScene;
Scene *New_GameScene(int label);
void game_scene_update(Scene *const pGameSceneObj);
void game_scene_draw(Scene *const pGameSceneObj);
void game_scene_destroy(Scene *const pGameSceneObj);

#endif
