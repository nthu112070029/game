#ifndef money_col_H_INCLUDED
#define money_col_H_INCLUDED
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [money_col object]
*/
typedef struct _money_col
{
   

// 加載字體
   ALLEGRO_FONT *font ;
   int money;
} money_col;
Elements *New_money_col(int label);
void money_col_update(Elements *const ele);
void money_col_interact(Elements *const, Elements *const);
void money_col_draw(Elements *const ele);
void money_col_destory(Elements *const ele);

#endif
