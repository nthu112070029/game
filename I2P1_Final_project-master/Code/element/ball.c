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
//mouse
#include <allegro5/allegro.h>

al_install_mouse;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
al_register_event_source(event_queue, al_get_mouse_event_source());
*/

/*
   [Ball function]
*/

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

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Ball_update;
    pObj->Interact = Ball_interact;
    pObj->Draw = Ball_draw;
    pObj->Destroy = Ball_destory;
    return pObj;
}
int mouse_click_state = 0;
void Ball_update(Elements *const ele)
{
    Ball *Obj = ((Ball *)(ele->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, mouse.x - Obj->x);
    hitbox->update_center_y(hitbox, mouse.y - Obj->y);
    Obj->x = mouse.x;
    Obj->y = mouse.y;
    //for(int i = 0 ; i < 100 ; i++)
    if ((mouse_state[1] == true) && (mouse_click_state == 0))
    {
        //printf("i is : %d\n", i);
        _Register_elements(scene, New_Tower(Tower_L, mouse.x, mouse.y));
        printf("Mouse button down at: (%d, %d)\n", event.mouse.x, event.mouse.y);
        mouse_click_state = 1;
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
    if (ele->label == Character_L)
    {
        Character *chara = ((Character *)(ele->pDerivedObj));
        if(chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            Obj->color = al_map_rgb(0, 255, 0);
        }
        else
        {
            Obj->color = al_map_rgb(255, 0, 0);
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