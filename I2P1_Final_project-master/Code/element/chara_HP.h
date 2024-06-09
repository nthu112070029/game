#ifndef chara_HP_H_INCLUDED
#define chara_HP_H_INCLUDED
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [chara_HP object]
*/
typedef struct _chara_HP
{
   ALLEGRO_FONT *font ;// 加載字體
} chara_HP;

Elements *New_chara_HP(int label);
void chara_HP_update(Elements *const ele);
void chara_HP_interact(Elements *const, Elements *const);
void chara_HP_draw(Elements *const ele);
void chara_HP_destory(Elements *const ele);

#endif
