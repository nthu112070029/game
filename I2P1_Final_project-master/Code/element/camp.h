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
    ALLEGRO_BITMAP *img;
    int map_data[14][20];
} camp;

Elements *New_camp(int label);
void _camp_load_map(camp *const camp);
void camp_update(Elements *const ele);
void camp_interact(Elements *const, Elements *const);
void camp_draw(Elements *const ele);
void camp_destory(Elements *const ele);

#endif
