#ifndef castle_H_INCLUDED
#define castle_H_INCLUDED
#include "element.h"
#include "../scene/gamescene.h" // for element label
#include "../shapes/Shape.h"
/*
   [castle object]
*/
typedef struct _castle
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    ALLEGRO_BITMAP *img;
    Shape *hitbox; // the hitbox of object
} castle;
Elements *New_castle(int label);
void castle_update(Elements *const ele);
void castle_interact(Elements *const, Elements *const);
void castle_draw(Elements *const ele);
void castle_destory(Elements *const ele);

#endif
