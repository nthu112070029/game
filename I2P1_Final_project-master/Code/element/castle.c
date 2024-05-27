#include "castle.h"
#include "../shapes/Rectangle.h"
/*
   [castle function]
*/
Elements *New_castle(int label)
{
    castle *pDerivedObj = (castle *)malloc(sizeof(castle));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/castle.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 900;
    pDerivedObj->y =0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x + pDerivedObj->width / 3,
                                        pDerivedObj->y + pDerivedObj->height / 3,
                                        pDerivedObj->x + 2 * pDerivedObj->width / 3,
                                        pDerivedObj->y + 2 * pDerivedObj->height / 3);
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = castle_update;
    pObj->Interact = castle_interact;
    pObj->Draw = castle_draw;
    pObj->Destroy = castle_destory;
    return pObj;
}
void castle_update(Elements *const ele) {}
void castle_interact(Elements *const self_ele, Elements *const ele) {}
void castle_draw(Elements *const ele)
{
    castle *Obj = ((castle *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void castle_destory(Elements *const ele)
{
    castle *Obj = ((castle *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
