#include "kill_num.h"
#include "../shapes/Rectangle.h"
/*
   [kill_num function]
*/
Elements *New_kill_num(int label)
{
    kill_num *pDerivedObj = (kill_num *)malloc(sizeof(kill_num));
    Elements *pObj = New_Elements(label);
    // setting derived object member
  
   pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
 
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = kill_num_update;
    pObj->Interact = kill_num_interact;
    pObj->Draw = kill_num_draw;
    pObj->Destroy = kill_num_destory;
    return pObj;
}
void kill_num_update(Elements *const ele) {

    //要配合小怪的擊殺
}
void kill_num_interact(Elements *const self_ele, Elements *const ele) {}
void kill_num_draw(Elements *const ele)
{
    kill_num *Obj = ((kill_num *)(ele->pDerivedObj));
    char text[100];
    
    sprintf(text, "kill_num: %d", money_num);
  
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 400, 150, ALLEGRO_ALIGN_CENTRE, text);
  
}
void kill_num_destory(Elements *const ele)
{
    kill_num *Obj = (( kill_num *)(ele->pDerivedObj));
    al_destroy_font(Obj->font);
  
   
    free(Obj);
    free(ele);
}
