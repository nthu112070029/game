#include "button.h"
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
   [Button function]
*/

Elements *New_Button(int label)
{
    printf("hsdjfbj");
    Button *pDerivedObj = (Button *)malloc(sizeof(Button));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    //pDerivedObj->img = al_load_bitmap("assets/image/projectile.png");
    //pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    //pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 500;
    pDerivedObj->y = 500;
    pDerivedObj->r = 10;
    pDerivedObj->color = al_map_rgb(255, 0, 0);

    // 初始化碰撞体
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x,
                                     pDerivedObj->y,
                                     pDerivedObj->r);

    // interact objects
    //pObj->inter_obj[pObj->inter_len++] = camp_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Button_update;
    pObj->Interact = Button_interact;
    pObj->Draw = Button_draw;
    pObj->Destroy = Button_destory;
    return pObj;
}


void Button_update(Elements *const ele)
{
    Button *Obj = ((Button *)(ele->pDerivedObj));
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, Obj->x);
    hitbox->update_center_y(hitbox, Obj->y);
    Obj->x = 500;
    Obj->y = 500;
    // if ((mouse_state[1] == true) && (mouse_click_state == 0)  && camp_ButtonHit)
    // {
    //     //tower_placed[campID_CharacterHit] = true;
    //     //_Register_elements(scene, New_Tower(Tower_L, campCenterX_Hit, campCenterY_Hit));
    //     mouse_click_state = 1;
    //     counter_of_tower++;
    //     money_num -= 400;
    // }
    // if (mouse_state[1] == false)
    // {
    //     mouse_click_state = 0;
    // }
    
    //_Button_update_position(ele, Obj->v, 0);
}

void _Button_update_position(Elements *const self, int dx, int dy)
{
    Button *Obj = ((Button *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
    
}

void Button_interact(Elements *const self_ele, Elements *const ele)
{
    Button *Obj = ((Button *)(self_ele->pDerivedObj));
    Obj->color = al_map_rgb(255, 0, 0);
    // if (ele->label == camp_L)
    // {
        
    //     camp *camp1 = ((camp *)(ele->pDerivedObj));
    //     if(camp1->hitbox->overlap(camp1->hitbox, Obj->hitbox) && (money_num > 400)  && campID_CharacterHit == ele->id && !(tower_placed[campID_CharacterHit]))
    //     {
    //         Obj->color = al_map_rgb(0, 255, 0);
    //         camp_ButtonHit = true;
    //         campCenterX_Hit = camp1->x + camp1->width/2;
    //         campCenterY_Hit = camp1->y + camp1->height/2;
    //     }
    //     else
    //     {
    //         Obj->color = al_map_rgb(255, 0, 0);
    //         camp_ButtonHit = false;
    //     }
    // }
}

void Button_draw(Elements *const ele)
{
    Button *Obj = ((Button *)(ele->pDerivedObj));
    al_draw_circle(Obj->x, Obj->y, Obj->r, Obj->color, 10);
    //al_flip_display();
}
void Button_destory(Elements *const ele)
{
    Button *Obj = ((Button *)(ele->pDerivedObj));
    //al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}