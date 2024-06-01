#include "ball.h"
#include "tree.h"
#include "projectile.h"
#include "charater.h"
#include "../scene/sceneManager.h"
#include "../shapes/Circle.h"
#include "../algif5/src/algif.h"
#include <stdio.h>

#include <allegro5/allegro_audio.h>
#include "allegro5/allegro_image.h"
#include "allegro5/allegro_font.h"
#include "allegro5/allegro_primitives.h"
#include "allegro5/allegro_primitives.h"

/*
   [Ball function]
*/
int counter_of_tower = 0;
bool camp_BallHit = false;
int campCenterX_Hit ,campCenterY_Hit;

Elements *New_Ball(int label)
{
    Ball *pDerivedObj = (Ball *)malloc(sizeof(Ball));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //pDerivedObj->img = al_load_bitmap("assets/image/projectile.png");
    //pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    //pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = mouse.x;
    pDerivedObj->y = mouse.y;
    pDerivedObj->r = 10;
    pDerivedObj->color = al_map_rgb(255, 0, 0);

    // 初始化碰撞体
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->r);

    // interact objects
    pObj->inter_obj[pObj->inter_len++] = camp_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ball_update;
    pObj->Interact = Ball_interact;
    pObj->Draw = Ball_draw;
    pObj->Destroy = Ball_destory;
    return pObj;
}

int mouse_click_state = 0;
bool tower_placed[1000];
void Ball_update(Elements *const ele)
{
    Ball *Obj = ((Ball *)(ele->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
    if ((mouse_state[1] == true) && (mouse_click_state == 0)  && camp_BallHit)
    {
        tower_placed[campID_CharacterHit] = true;
        _Register_elements(scene, New_Tower(Tower_L, campCenterX_Hit, campCenterY_Hit));
        mouse_click_state = 1;
        counter_of_tower++;
    }
    if (mouse_state[1] == false)
    {
        mouse_click_state = 0;
    }
    
    //_Ball_update_position(ele, Obj->v, 0);
}

void _Ball_update_position(Elements *const self, int dx, int dy)
{
    Ball *Obj = ((Ball *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
    
}

void Ball_interact(Elements *const self_ele, Elements *const ele)
{
    Ball *Obj = ((Ball *)(self_ele->pDerivedObj));
    if (ele->label == camp_L)
    {
        
        camp *camp1 = ((camp *)(ele->pDerivedObj));
        if(camp1->hitbox->overlap(camp1->hitbox, Obj->hitbox) && campID_CharacterHit == ele->id && !(tower_placed[campID_CharacterHit]))
        {
            Obj->color = al_map_rgb(0, 255, 0);
            camp_BallHit = true;
            campCenterX_Hit = camp1->x + camp1->width/2;
            campCenterY_Hit = camp1->y + camp1->height/2;
        }
        else
        {
            Obj->color = al_map_rgb(255, 0, 0);
            camp_BallHit = false;
        }
    }
}

void Ball_draw(Elements *const ele)
{
    Ball *Obj = ((Ball *)(ele->pDerivedObj));
    al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
    //al_flip_display();
}
void Ball_destory(Elements *const ele)
{
    Ball *Obj = ((Ball *)(ele->pDerivedObj));
    //al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}