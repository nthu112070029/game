#ifndef camp_H_INCLUDED
#define camp_H_INCLUDED
#include "element.h"
#include "charater.h"
#include "../scene/gamescene.h" // for element label
/*
   [camp object]
*/
typedef struct _camp
{
    int x, y;          // the position of image
    int width, height; // the width and height of image
    int img_state;
    ALLEGRO_BITMAP *img[3];
    Shape *hitbox;
} camp;

Elements *New_camp(int label, int i, int j);
//void _camp_load_map(camp *const camp);
void camp_update(Elements *const ele);
void camp_interact(Elements *const, Elements *const);
void camp_draw(Elements *const ele);
void camp_destory(Elements *const ele);
void camp_load_bitmap();
#endif