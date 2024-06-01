#include "camp.h"
#include <stdio.h>
#include "../shapes/Rectangle.h"
ALLEGRO_BITMAP *bitmap_camp;

/*
   [camp function]
*/
Elements *New_camp(int label, int i, int j)
{
    camp *pDerivedObj = (camp *)malloc(sizeof(camp));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = bitmap_camp;
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    //_camp_load_map(pDerivedObj); need to change
    pDerivedObj->x = i * pDerivedObj->width;
    pDerivedObj->y = j * pDerivedObj->height;
    pDerivedObj->hitbox = New_Rectangle(pDerivedObj->x,
                                        pDerivedObj->y,
                                        pDerivedObj->x + pDerivedObj->width,
                                        pDerivedObj->y + pDerivedObj->height);

    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = camp_draw;
    pObj->Update = camp_update;
    pObj->Interact = camp_interact;
    pObj->Destroy = camp_destory;
    return pObj;
}
/*
void _camp_load_map(camp *const camp)
{
    FILE *data;
    data = fopen("assets/map/camp.txt", "r");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            fscanf(data, "%d", &camp->map_data[i][j]);
        }
    }
    fclose(data);
}
*/
void camp_update(Elements *const ele)
{
    return;
}
void camp_interact(Elements *const self_ele, Elements *const ele)
{
    if (ele->label == Character_L)
    {
        Character *chara = (Character *)(ele->pDerivedObj);
        if (chara->x < 0 - chara->width / 2)
            chara->x = 0 - chara->width / 2;
        else if (chara->x > WIDTH - chara->width / 2)
            chara->x = WIDTH - chara->width / 2;
    }
}
void camp_draw(Elements *const ele)
{
    camp *Obj = ((camp *)(ele->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
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
    bitmap_camp = al_load_bitmap("assets/image/camp.png");
}