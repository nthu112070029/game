#include "button.h"
#include "../scene/lose.h"
#include "../scene/win.h"
#include <stdio.h>
#include "../shapes/Rectangle.h"
extern int mouse_click_state;

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

    int init_x, init_y;
    if(window == 2) init_x = 730, init_y = 550;
    else init_x = 500, init_y = 625;
    
    pDerivedObj->x = init_x - pDerivedObj->width/2;
    pDerivedObj->y = init_y - pDerivedObj->height/2;

    // 初始化碰撞体
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    //interact objects
    pObj->inter_obj[pObj->inter_len++] = Win_Button_L;
    pObj->inter_obj[pObj->inter_len++] = Lose_Button_L;

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
    Button * Obj = (Button *)(ele->pDerivedObj);
    if ((mouse_state[1] == true) && (mouse_click_state == 0) && Obj->state==1)
    {
        window = 1;
        mouse_click_state = 1;
    }
    if (mouse_state[1] == false)
    {
        mouse_click_state = 0;
    }
}

void _Button_update_position(Elements *const self, int dx, int dy)
{

}

void Button_interact(Elements *const self_ele, Elements *const ele)
{
    Button *Obj = ((Button *)(self_ele->pDerivedObj));
    if(Obj->x < mouse.x && Obj->x+Obj->width > mouse.x && Obj->y < mouse.y && Obj->y+Obj->height > mouse.y)
    {
        Obj->state = 1;

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