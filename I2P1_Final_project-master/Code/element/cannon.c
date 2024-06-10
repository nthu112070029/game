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
    // char state_string[3][10] = {"stop", "move", "attack"};
    // for (int i = 0; i < 3; i++)
    // {
    //     char buffer[50];
    //     sprintf(buffer, "assets/image/ca_%s.gif", state_string[i]);
    //     pDerivedObj->gif_status[i] = algif_new_gif(buffer, -1);
    // }

    // load effective sound
    ALLEGRO_SAMPLE *sample = al_load_sample("assets/sound/cannon.mp3");
    pDerivedObj->atk_Sound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(pDerivedObj->atk_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(pDerivedObj->atk_Sound, al_get_default_mixer());

   

    // initial the geometric information of cannon

  
    // pDerivedObj->width = pDerivedObj->gif_status[0]->width;
    // pDerivedObj->height = pDerivedObj->gif_status[0]->height;
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
    
    if (!key_state[ALLEGRO_KEY_UP])
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
       /*if (chara->gif_status[chara->state]->done)
            chara->state = stop;*/ 
    }
    else if (chara->state == atk )
    {
       
        // if (chara->gif_status[chara->state]->done)
        // {
        //     chara->state = stop;
        //     chara->new_proj = false;
        // }
        // if ( chara->new_proj == false)
        // {
            Elements *pro;
            
                pro = New_Projectile(Projectile_L,
                                     chara->x +chara-> width/2,
                                     chara->y ,
                                     -5);
           
            _Register_elements(scene, pro);
            printf("cannon");
            money_num-=5;
            chara->state = move;
        // }
          

            
       
    }
   
}
void cannon_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    cannon *Obj = ((cannon *)(ele->pDerivedObj));
    //ALLEGRO_BITMAP *frame = algif_get_bitmap(Obj->gif_status[Obj->state], al_get_time());
    // if (frame)
    // {
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
    // }
    if (Obj->state == atk)//&& Obj->gif_status[Obj->state]->display_index == 2
    {
        al_play_sample_instance(Obj->atk_Sound);
    }
}
void cannon_destory(Elements *const ele)
{
    cannon *Obj = ((cannon *)(ele->pDerivedObj));
    al_destroy_sample_instance(Obj->atk_Sound);
    al_destroy_bitmap(Obj->img);
    // for (int i = 0; i < 3; i++)
    //     algif_destroy_animation(Obj->gif_status[i]);
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
