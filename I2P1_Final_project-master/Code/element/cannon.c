#include "cannon.h"
#include "../scene/sceneManager.h"
#include "projectile.h"
#include "../shapes/Rectangle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>
/*
   [cannon function]
*/
Elements *New_cannon(int label)
{
    cannon *pDerivedObj = (cannon *)malloc(sizeof(cannon));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load cannon images
    pDerivedObj->img = al_load_bitmap("assets/image/castle.png");

    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/cannon.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

    // initial the geometric information of cannon
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);;
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 700;
    pDerivedObj->y = HEIGHT - pDerivedObj->height ;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
     
    // initial the animation component
    pDerivedObj->state = stop;
    pDerivedObj->new_proj = false;
    pObj->pDerivedObj = pDerivedObj;
    
   
    // setting derived object function
    pObj->Draw = cannon_draw;
    pObj->Update = cannon_update;
    pObj->Interact = cannon_interact;
    pObj->Destroy = cannon_destory;
    return pObj;
}
int kEY_UP_state = 0;
void cannon_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    cannon *chara = ((cannon *)(ele->pDerivedObj));
    
    if (!key_state[ALLEGRO_KEY_UP] && al_get_sample_instance_playing(chara->atk_Sound) == false)
    {
        chara->new_proj = false;
    }

    if (chara->state == stop)
    {
        if (key_state[ALLEGRO_KEY_UP] && chara->new_proj == false)
        {
            chara->state = atk;
            chara->new_proj = true;
        }else if (key_state[ALLEGRO_KEY_LEFT])
        {
          
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_RIGHT])
        {
            
            chara->state = move;
        }
        else
        {
            chara->state = stop;
        }
    }
    else if (chara->state == move)
    {
        if (key_state[ALLEGRO_KEY_UP])
        {
            chara->state = atk;
        }else{
            chara->new_proj = false;
        }
        if (key_state[ALLEGRO_KEY_LEFT])
        {
           
            _cannon_update_position(ele, -5, 0);
            chara->state = move;
        }
        else if (key_state[ALLEGRO_KEY_RIGHT])
        {
            _cannon_update_position(ele, 5, 0);
            chara->state = move;
        }
        else
        {
            chara->state = stop;
        }
    }
    else if (chara->state == atk)
    {
        Elements *pro;
        
            pro = New_Projectile(Projectile_L,
                                    chara->x +chara-> width/2,
                                    chara->y ,
                                    -5);
        
        _Register_elements(scene, pro);
        printf("cannon");
        money_num-=5;
        chara->state = move;
    }
   
}
void cannon_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    cannon *Obj = ((cannon *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    if (Obj->state == atk)
    {
        al_set_sample_instance_playing(Obj->atk_Sound, 1);
    }
}
void cannon_destory(Elements *const ele)
{
    cannon *Obj = ((cannon *)(ele->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _cannon_update_position(Elements *const ele, int dx, int dy)
{
    cannon *chara = ((cannon *)(ele->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}



void cannon_interact(Elements *const self_ele, Elements *const target_ele) {
    
    
}
