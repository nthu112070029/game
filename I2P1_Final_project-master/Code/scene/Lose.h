#ifndef Lose_H_INCLUDED
#define Lose_H_INCLUDED
#include "scene.h"
#include "../element/button.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
/*
   [Lose object]
*/
typedef enum LostEleType
{
    Button_L,
}LostEleType;
typedef struct _Lose
{
     ALLEGRO_BITMAP *background;
    ALLEGRO_FONT *font;
    ALLEGRO_SAMPLE *song;
    ALLEGRO_SAMPLE_INSTANCE *sample_instance;
    int title_x, title_y;
} Lose;
Scene *New_Lose(int label);
void Lose_update(Scene *const pLoseObj);
void Lose_draw(Scene *const pLoseObj);
void Lose_destroy(Scene *const pLoseObj);

#endif