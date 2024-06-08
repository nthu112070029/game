#include "camp.h"
#include <stdio.h>
#include "../shapes/Rectangle.h"
ALLEGRO_BITMAP *bitmap_camp[3];

/*
   [camp function]
*/
Elements *New_camp(int label, int i, int j)
{
    camp *pDerivedObj = (camp *)malloc(sizeof(camp));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img[0] = bitmap_camp[0];
    pDerivedObj->img[1] = bitmap_camp[1];
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img[1]);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img[1]);
    //_camp_load_map(pDerivedObj); need to change
    pDerivedObj->x = i * pDerivedObj->width;
    pDerivedObj->y = j * pDerivedObj->height;
    pDerivedObj->img_state = 1;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    // interact
    pObj->inter_obj[pObj->inter_len++] = Tower_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = camp_draw;
    pObj->Update = camp_update;
    pObj->Interact = camp_interact;
    pObj->Destroy = camp_destory;
    return pObj;
}

void camp_update(Elements *const ele)
{
    return;
}
void camp_interact(Elements *const self_ele, Elements *const ele)
{
    camp * Obj = ((camp *)(self_ele->pDerivedObj));
    if (ele->label == Tower_L)
    {
        Tower *tower = (Tower *)(ele->pDerivedObj);
        if (tower->hitbox->overlap(tower->hitbox, Obj->hitbox))
        {
            Obj->img_state = 0;
        } else {
            //Obj->img_state = 1;
        }
    }
}
void camp_draw(Elements *const ele)
{
    camp *Obj = ((camp *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img[Obj->img_state], Obj->x, Obj->y, 0);
}
void camp_destory(Elements *const ele)
{
    camp *Obj = ((camp *)(ele->pDerivedObj));
    //al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}

void camp_load_bitmap()
{
    bitmap_camp[0] = al_load_bitmap("assets/image/transparent.png");
    bitmap_camp[1] = al_load_bitmap("assets/image/camp.png");
}