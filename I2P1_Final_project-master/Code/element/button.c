#include "button.h"
#include "../scene/lose.h"
// #include "../scene/sceneManager.h"
// #include "../shapes/Circle.h"
// #include "../algif5/src/algif.h"
#include <stdio.h>
#include "../shapes/Rectangle.h"
// #include <allegro5/allegro_audio.h>
// #include "allegro5/allegro_image.h"
// #include "allegro5/allegro_font.h"
// #include "allegro5/allegro_primitives.h"
// #include "allegro5/allegro_primitives.h"

/*
   [Button function]
*/

Elements *New_Button(int label)
{
    Button *pDerivedObj = (Button *)malloc(sizeof(Button));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img[0] = al_load_bitmap("assets/image/button.png");
    pDerivedObj->img[1] = al_load_bitmap("assets/image/button1.png");
    pDerivedObj->state = 0;
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img[0]);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img[0]);
    pDerivedObj->x = 500 - pDerivedObj->width/2;
    pDerivedObj->y = 500 - pDerivedObj->height/2;

    // 初始化碰撞体
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    //interact objects
    pObj->inter_obj[pObj->inter_len++] = Button_L;

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
    // Button *Obj = ((Button *)(ele->pDerivedObj));
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, Obj->x);
    //hitbox->update_center_y(hitbox, Obj->y);
    //Obj->x = 500;
    //Obj->y = 500;
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
    // Button *Obj = ((Button *)(self->pDerivedObj));
    // Obj->x += dx;
    // Obj->y += dy;
    // Shape *hitbox = Obj->hitbox;
    // hitbox->update_center_x(hitbox, dx);
    // hitbox->update_center_y(hitbox, dy);
    
}

void Button_interact(Elements *const self_ele, Elements *const ele)
{
    Button *Obj = ((Button *)(self_ele->pDerivedObj));
    if(400 < mouse.x && 600 > mouse.x && 400 < mouse.y && 600 > mouse.y)
    {
        Obj->state = 1;
//      al_draw_scaled_bitmap(Obj->img,
//      Obj->x, Obj->y, Obj->width, Obj->height,
//      Obj->x, Obj->y, Obj->width*2, (Obj->height)*2, 0);
    }
    else
    {
        Obj->state = 0;
    }

}

void Button_draw(Elements *const ele)
{
    Button *Obj = ((Button *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img[Obj->state], Obj->x, Obj->y, 0);
}
void Button_destory(Elements *const ele)
{
    Button *Obj = ((Button *)(ele->pDerivedObj));
    while (Obj->state--)
    {
        al_destroy_bitmap(Obj->img[1]);
    }
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}