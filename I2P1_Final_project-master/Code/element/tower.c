#include "tower.h"
#include "../scene/sceneManager.h"
#include "poft.h"
#include "monster.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>
ALLEGRO_BITMAP *bitmap_tower ; 

/*
   [Tower function]
*/
Elements *New_Tower(int label, int x, int y)
{
    
    Tower *pDerivedObj = (Tower *)malloc(sizeof(Tower));
    Elements *pObj = New_Elements(label);

    /*
    // setting derived object member
    // load Tower images
    char state_string[3][10] = {"stop", "move", "attack"};
    for (int i = 0; i < 3; i++)
    {
        char buffer[50];
        sprintf(buffer, "assets/image/tower_%s.gif", state_string[i]);
        pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    }
    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/atk_sound.wav");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of Tower
    pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    pDerivedObj->height = pDerivedObj->gif_status[0]->height;
    pDerivedObj->x = x-(pDerivedObj->width)/2;
    pDerivedObj->y = y-(pDerivedObj->height)/2;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
    pDerivedObj->dir = false; // true: face to right, false: face to left
    // initial the animation component
    pDerivedObj->state = T_STOP;
    pDerivedObj->new_proj = false;
    */

    pDerivedObj->img = bitmap_tower;
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x-(pDerivedObj->width)/2;
    pDerivedObj->y = y-(pDerivedObj->height)/2;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x +1,
                                        pDerivedObj->y +1,
                                        pDerivedObj->x + pDerivedObj->width -1,
                                        pDerivedObj->y + pDerivedObj->height -1);

    pObj->pDerivedObj = pDerivedObj;
    // setting derived object function
    pObj->Draw = Tower_draw;
    pObj->Update = Tower_update;
    pObj->Interact = Tower_interact;
    pObj->Destroy = Tower_destory;
    return pObj;
}

void Tower_update(Elements *self)
{
    // use the idea of finite state machine to deal with different state
    Tower *chara = ((Tower *)(self->pDerivedObj));
    if (!(timer%120))
    {
        int a = 5;
        int b = 5;
        //create projectile of tower
        Elements *pro;
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        a, b);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        a, -b);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        -a, b);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        -a, -b);
        _Register_elements(scene, pro);
    }
}
void Tower_draw(Elements *self)
{
    
    // // with the state, draw corresponding image
    // Tower *chara = ((Tower *)(self->pDerivedObj));
    // ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    // if (frame)
    // {
    //     al_draw_bitmap(frame, chara->x, chara->y, 0/*((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0)*/);
    // }
    // if (chara->state == T_ATK && chara->gif_status[chara->state]->display_index == 2)
    // {
    //     al_play_sample_instance(chara->atk_Sound);
    // }

    Tower *Obj = ((Tower *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Tower_destory(Elements *self)
{
    Tower *Obj = ((Tower *)(self->pDerivedObj));
    // al_destroy_sample_instance(Obj->atk_Sound);
    // for (int i = 0; i < 3; i++)
    //     algif_destroy_animation(Obj->gif_status[i]);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void _Tower_update_position(Elements *self, int dx, int dy)
{
    Tower *chara = ((Tower *)(self->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void Tower_interact(Elements *self, Elements *tar) {}

void tower_load_bitmap()
{
    bitmap_tower = al_load_bitmap("assets/image/tower.png");
}