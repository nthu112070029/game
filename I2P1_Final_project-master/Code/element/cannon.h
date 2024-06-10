#ifndef CANNON_H_INCLUDED
#define CANNON_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include "../scene/gamescene.h" // for element label
/*
   [cannon object]
*/
typedef enum cannonType
{
	stop = 0,
	move,
	atk
} cannonType;
typedef struct _cannon
{
   int x, y;          
   int width, height; // the width and height of image
   bool dir;          // true: face to right, false: face to left
   int state;         // the state of character
   //ALGIF_ANIMATION* gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
   ALLEGRO_BITMAP *img;
   ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
   int anime;      // counting the time of animation
   int anime_time; // indicate how long the animation
   bool new_proj;
   Shape *hitbox; // the hitbox of object
} cannon;
Elements *New_cannon(int label);
void _cannon_update_position(Elements *const self, int dx, int dy);
void cannon_update(Elements *const self);
void cannon_interact(Elements *const self, Elements *const target);
void cannon_draw(Elements *const self);
void cannon_destory(Elements *const self);

extern int campID_cannonHit;

#endif