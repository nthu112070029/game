#ifndef monster_H_INCLUDED
#define monster_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Circle.h"

#include "../scene/gamescene.h" // for element label
/*
   [monster object]
*/
typedef enum monsterType
{
	Run= 0,
	BATK
} monsterType;



typedef struct _Monster
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int state;
    Shape *hitbox; // the hitbox of object
} Monster;
Elements *New_Monster(int label);
void _monster_update_position(Elements *const self, int dx, int dy);
void monster_update(Elements *const ele);

void monster_interact(Elements *const, Elements *const);
void monster_draw(Elements *const ele);
void monster_destory(Elements *const ele);

#endif
