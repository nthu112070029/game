#ifndef TOWER_H_INCLUDED
#define TOWER_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_image.h>
#include "element.h"
#include "../shapes/Shape.h"
#include "../algif5/src/algif.h"
#include <stdbool.h>

/*
   [Tower object]
*/
typedef enum TowerType
{
    T_STOP = 0,
    T_MOVE,
    T_ATK
} TowerType;
typedef struct _Tower
{
    int x, y;
    int width, height;              // the width and height of image
    bool dir;                       // true: face to right, false: face to left
    int state;                      // the state of Tower
    ALGIF_ANIMATION *gif_status[3]; // gif for each state. 0: stop, 1: move, 2:attack
    ALLEGRO_SAMPLE_INSTANCE *atk_Sound;
    int anime;      // counting the time of animation
    int anime_time; // indicate how long the animation
    bool new_proj;  //What is this line function?
    Shape *hitbox; // the hitbox of object
} Tower;
Elements *New_Tower(int label);
void _Tower_update_position(Elements *self, int dx, int dy);
void Tower_update(Elements *self);
void Tower_interact(Elements *self, Elements *target);
void Tower_draw(Elements *self);
void Tower_destory(Elements *self);

#endif
