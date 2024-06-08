#ifndef PofT_H_INCLUDED
#define PofT_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [PofT
 object]
*/
typedef struct _PofT // projectile of tower
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int vx, vy;        // the velocity of PofT

    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} PofT;
Elements *New_PofT(int label, int x, int y, int vx, int vy);
void PofT_update(Elements *self);
void PofT_interact(Elements *self, Elements *tar);
void PofT_draw(Elements *self);
void PofT_destory(Elements *self);
void _PofT_update_position(Elements *self, int dx, int dy);
void poft_load_bitmap_sound();
ALLEGRO_SAMPLE_INSTANCE *poft_Sound;
#endif
