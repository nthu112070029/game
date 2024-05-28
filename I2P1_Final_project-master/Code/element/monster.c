#include "monster.h"
#include "../shapes/Rectangle.h"
#include <stdio.h>

/*
   [monster function]
*/
Elements *New_Monster(int label)
{
    Monster *pDerivedObj = (Monster *)malloc(sizeof(Monster));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    // load monster images
    
    
    

    // initial the geometric information of monster
    pDerivedObj->img = al_load_bitmap("assets/image/monster_Move.png");
    pDerivedObj->width =al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 0;
    pDerivedObj->y = 100;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);
   
    // initial the animation component
    pDerivedObj->state = Run;
    pObj->pDerivedObj = pDerivedObj;
    //interact obj
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = PofT_L;
    // setting derived object function
    pObj->Draw = monster_draw;
    pObj->Update = monster_update;
    pObj->Interact = monster_interact;
    pObj->Destroy = monster_destory;
   
    return pObj;
}
void monster_update(Elements *const ele)
{
    // use the idea of finite state machine to deal with different state
    Monster *chara = ((Monster *)(ele->pDerivedObj));
    if (chara-> state == BATK)
    {
        
    }
    else if (chara->state == Run)
    {
        if(chara->x <200 && chara->y==100)
        {
            _monster_update_position(ele, 1, 0);

        }
        else if(chara->x ==200 && chara->y<400 )
        {
            _monster_update_position(ele, 0, 1);

        }
         else if(chara->x <650 && chara->y==400 )
        {
            _monster_update_position(ele, 1, 0);

        }
         else if(chara->x ==650 && chara->y>100 )
        {
            _monster_update_position(ele, 0, -1);

        } else if(chara->x <1000 && chara->y==100 )
        {
            _monster_update_position(ele, 1, 0);

        }
    }
    
    
}
void monster_draw(Elements *const ele)
{
    // with the state, draw corresponding image
    Monster *Obj = ((Monster *)(ele->pDerivedObj));
   al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void monster_destory(Elements *const ele)
{
    Monster *Obj = ((Monster *)(ele->pDerivedObj));
     al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void _monster_update_position(Elements *const ele, int dx, int dy)
{
    Monster *chara = ((Monster *)(ele->pDerivedObj));
    chara->x += dx;
    chara->y += dy;
    Shape *hitbox = chara->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}

void monster_interact(Elements *const self, Elements *const target) {

    Monster *Obj = ((Monster *)(self->pDerivedObj));
    if (target->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
    }
    else if (target->label == PofT_L)
    {
        PofT *poft = ((PofT *)(target->pDerivedObj));
        if (poft->hitbox->overlap(poft->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
}
