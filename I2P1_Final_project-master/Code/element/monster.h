#ifndef CHARATER_H_INCLUDED
#define CHARATER_H_INCLUDED
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
	
	MOVE= 0,
	BATK
} monsterType;
typedef struct _monster
{
    int x, y;          
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    int state;         // the state of monster
    
    
   
    Shape *hitbox; // the hitbox of object
} monster;
Elements *New_Monster(int label);
void _monster_update_position(Elements *const self, int dx, int dy);
void monster_update(Elements *const self);
void monster_interact(Elements *const self, Elements *const target);
void monster_draw(Elements *const self);
void monster_destory(Elements *const self);

#endif
