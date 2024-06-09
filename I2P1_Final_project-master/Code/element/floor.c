#include "floor.h"
#include <stdio.h>
/*
   [floor function]
*/
Elements *New_Floor(int label)
{
    Floor *pDerivedObj = (Floor *)malloc(sizeof(Floor));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/floor.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    _Floor_load_map(pDerivedObj);
    pDerivedObj->x = 0;
    pDerivedObj->y = 0;
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Draw = Floor_draw;
    pObj->Update = Floor_update;
    pObj->Interact = Floor_interact;
    pObj->Destroy = Floor_destory;
    return pObj;
}
void _Floor_load_map(Floor *const floor)
{
    FILE *data;
    data = fopen("assets/map/map.txt", "r");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            fscanf(data, "%d", &floor->map_data[i][j]);
        }
    }
    fclose(data);
}
void Floor_update(Elements *const ele)
{
    return;
}
void Floor_interact(Elements *const self_ele, Elements *const ele)
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
void Floor_draw(Elements *const ele)
{
    Floor *Obj = ((Floor *)(ele->pDerivedObj));
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (Obj->map_data[i][j] == 1)
            {
                al_draw_bitmap(Obj->img, Obj->x + j * Obj->width, Obj->y + i * Obj->height, 0);
            }
        }
    }
}
void Floor_destory(Elements *const ele)
{
    Floor *Obj = ((Floor *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj);
    free(ele);
}
