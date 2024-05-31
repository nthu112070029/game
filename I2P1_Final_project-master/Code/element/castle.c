#include "castle.h"
#include "../shapes/Rectangle.h"
/*
   [castle function]
*/
Elements *New_castle(int label)
{
    Castle *pDerivedObj = (Castle *)malloc(sizeof(Castle));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/castle.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = 900;
    pDerivedObj->y =0;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    // interact obj
    pObj->inter_obj[pObj->inter_len++] = Monster_L;

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = castle_update;
    pObj->Interact = castle_interact;
    pObj->Draw = castle_draw;
    pObj->Destroy = castle_destory;
    return pObj;
}
void castle_update(Elements *const ele) {}

void castle_interact(Elements *const self_ele, Elements *const ele) {

    Castle *Obj = ((Castle *)(self_ele->pDerivedObj));
    if (ele->label == Monster_L)
    {
        Monster *monster = ((Monster *)(ele->pDerivedObj));

        if (monster->hitbox->overlap(monster->hitbox, Obj->hitbox))
        {
            
            window = 2;//here, you can add change scene code
        }
    }
}
void castle_draw(Elements *const ele)
{
    Castle *Obj = ((Castle *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void castle_destory(Elements *const ele)
{
    Castle *Obj = ((Castle *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
