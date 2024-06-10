#ifndef Win_H_INCLUDED
#define Win_H_INCLUDED
#include "scene.h"
#include "../element/button.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Win object]
*/
typedef struct _Win
{
   ALLEGRO_BITMAP *background;
   ALLEGRO_FONT *font;
   ALLEGRO_SAMPLE *song;
   ALLEGRO_SAMPLE_INSTANCE *sample_instance;
   int title_x, title_y;
} Win;
typedef enum WinEleType
{
   Win_Button_L,
}WinEleType;
Scene *New_Win(int label);
void Win_update(Scene *const pWinObj);
void Win_draw(Scene *const pWinObj);
void Win_destroy(Scene *const pWinObj);

#endif
