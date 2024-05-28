#include "tower.h"
#include "../scene/sceneManager.h"
#include "poft.h"
#include "monster.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
#include <stdbool.h>

extern int timer;

int index_of_projit = 0;
/*
   [Tower function]
*/
Elements *New_Tower(int label, int x, int y)
{
    
    Tower *pDerivedObj = (Tower *)malloc(sizeof(Tower));
    Elements *pObj = New_Elements(label);
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
    if (!(timer%60))//(chara->gif_status[T_ATK]->display_index == 2 && chara->new_proj == false)
    {           
        //create projectile of tower
        Elements *pro;
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        5, 5);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        5, -5);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        -5, 5);
        _Register_elements(scene, pro);
        pro = New_PofT(PofT_L,
                        chara->x + ( chara->width ) /2-5,
                        chara->y + ( chara->height ) /2-5,
                        -5, -5);
        _Register_elements(scene, pro);
        chara->new_proj = true;
    }

    if (chara->state == T_STOP)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = T_ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            chara->state = T_MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            chara->state = T_MOVE;
        }
        else
        {
            chara->state = T_STOP;
        }
    }
    else if (chara->state == T_MOVE)
    {
        if (key_state[ALLEGRO_KEY_SPACE])
        {
            chara->state = T_ATK;
        }
        else if (key_state[ALLEGRO_KEY_A])
        {
            chara->dir = false;
            _Tower_update_position(self, -5, 0);
            chara->state = T_MOVE;
        }
        else if (key_state[ALLEGRO_KEY_D])
        {
            chara->dir = true;
            _Tower_update_position(self, 5, 0);
            chara->state = T_MOVE;
        }
        if (chara->gif_status[chara->state]->done)
            chara->state = T_STOP;
    }
    else if (chara->state == T_ATK)
    {
        if (chara->gif_status[chara->state]->done)
        {
            chara->state = T_STOP;
            chara->new_proj = false;
        }
        /*
        if (index_of_projit == 60)
        //(chara->gif_status[T_ATK]->display_index == 2 && chara->new_proj == false)
        {
            Elements *pro;
            pro = New_PofT(PofT_L,
                            chara->x + ( chara->width )  - 100,
                            chara->y + 10,
                            5, 5);
            _Register_elements(scene, pro);
            pro = New_PofT(PofT_L,
                            chara->x + ( chara->width )  - 100,
                            chara->y + 10,
                            5, -5);
            _Register_elements(scene, pro);
            pro = New_PofT(PofT_L,
                            chara->x + ( chara->width )  - 100,
                            chara->y + 10,
                            -5, 5);
            _Register_elements(scene, pro);
            pro = New_PofT(PofT_L,
                            chara->x + ( chara->width )  - 100,
                            chara->y + 10,
                            -5, -5);
            _Register_elements(scene, pro);
            chara->new_proj = true;
            index_of_projit = 0;
        }
        */
    }
}
void Tower_draw(Elements *self)
{
    // with the state, draw corresponding image
    Tower *chara = ((Tower *)(self->pDerivedObj));
    ALLEGRO_BITMAP *frame = algif_get_bitmap(chara->gif_status[chara->state], al_get_time());
    if (frame)
    {
        al_draw_bitmap(frame, chara->x, chara->y, ((chara->dir) ? ALLEGRO_FLIP_HORIZONTAL : 0));
    }
    if (chara->state == T_ATK && chara->gif_status[chara->state]->display_index == 2)
    {
        al_play_sample_instance(chara->atk_Sound);
    }
}
void Tower_destory(Elements *self)
{
    Tower *Obj = ((Tower *)(self->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    for (int i = 0; i < 3; i++)
        algif_destroy_animation(Obj->gif_status[i]);
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
