#include "chara_HP.h"
#include "../shapes/Rectangle.h"
/*
   [chara_HP function]
*/
Elements *New_chara_HP(int label)
{
    chara_HP *pDerivedObj = (chara_HP *)malloc(sizeof(chara_HP));
    Elements *pObj = New_Elements(label);
    // setting derived object member
  
   pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
 
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = chara_HP_update;
    pObj->Interact = chara_HP_interact;
    pObj->Draw = chara_HP_draw;
    pObj->Destroy = chara_HP_destory;
    return pObj;
}
void chara_HP_update(Elements *const ele) {

    //要配合小怪的擊殺
}
void chara_HP_interact(Elements *const self_ele, Elements *const ele) {}
void chara_HP_draw(Elements *const ele)
{
    chara_HP *Obj = ((chara_HP *)(ele->pDerivedObj));
    char text[100];
    
    sprintf(text, "chara_HP: %d", chara_Helath_Point);
  
    al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 450, 250, ALLEGRO_ALIGN_CENTRE, text);
  
}
void chara_HP_destory(Elements *const ele)
{
    chara_HP *Obj = (( chara_HP *)(ele->pDerivedObj));
    al_destroy_font(Obj->font);
  
   
    free(Obj);
    free(ele);
}
