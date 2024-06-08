#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED
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
   [Button object]
*/


typedef struct _Button
{
    int x, y;          
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img[3];
    int state;         // the state of Button
    //ALGIF_ANIMATION* gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    //ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    //bool new_proj;
    Shape *hitbox; // the hitbox of object !!
    //ALLEGRO_BITMAP *img;
} Button;
Elements *New_Button(int label);
//void _Button_update_position(Elements *const self, int dx, int dy);
void Button_update(Elements *const self);
void Button_interact(Elements *const self, Elements *const target);
void Button_draw(Elements *const self);
void Button_destory(Elements *const self);

bool camp_ButtonHit;
int counter_of_tower;

#endif