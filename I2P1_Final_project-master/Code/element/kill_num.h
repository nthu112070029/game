#ifndef kill_num_H_INCLUDED
#define kill_num_H_INCLUDED
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [kill_num object]
*/
typedef struct _kill_num
{
   

// 加載字體
   ALLEGRO_FONT *font ;
   
} kill_num;
Elements *New_kill_num(int label);
void kill_num_update(Elements *const ele);
void kill_num_interact(Elements *const, Elements *const);
void kill_num_draw(Elements *const ele);
void kill_num_destory(Elements *const ele);

#endif
