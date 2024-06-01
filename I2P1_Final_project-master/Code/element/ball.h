#ifndef BALL_H_INCLUDED
#define BALL_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"

/*
   [Ball object]
*/


typedef struct _Ball
{
    int x, y, r;          
    //int width, height; // the width and height of image
    //bool dir;          // true: face to right, false: face to left
    //int state;         // the state of Ball
    ALLEGRO_COLOR color;
    //ALGIF_ANIMATION* gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    //ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    //int anime;      // counting the time of animation
    //int anime_time; // indicate how long the animation
    //bool new_proj;
    Shape *hitbox; // the hitbox of object !!
    //ALLEGRO_BITMAP *img;
} Ball;
Elements *New_Ball(int label);
//void _Ball_update_position(Elements *const self, int dx, int dy);
void Ball_update(Elements *const self);
void Ball_interact(Elements *const self, Elements *const target);
void Ball_draw(Elements *const self);
void Ball_destory(Elements *const self);

bool camp_BallHit;
int counter_of_tower;

#endif