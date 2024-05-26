#include "money_col.h"
#include "../shapes/Rectangle.h"
/*
   [money_col function]
*/
Elements *New_money_col(int label)
{
    money_col *pDerivedObj = (money_col *)malloc(sizeof(money_col));
    Elements *pObj = New_Elements(label);
    // setting derived object member
  
   pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 30, 0);
    pDerivedObj->money=0;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = money_col_update;
    pObj->Interact = money_col_interact;
    pObj->Draw = money_col_draw;
    pObj->Destroy = money_col_destory;
    return pObj;
}
void money_col_update(Elements *const ele) {

    //要配合小怪的擊殺
}
void money_col_interact(Elements *const self_ele, Elements *const ele) {}
void money_col_draw(Elements *const ele)
{
    money_col *Obj = ((money_col *)(ele->pDerivedObj));
     al_draw_text(Obj->font, al_map_rgb(0, 0, 0), 0, 670, 0, "Money: 1000");
  
}
void money_col_destory(Elements *const ele)
{
    money_col *Obj = (( money_col *)(ele->pDerivedObj));
    al_destroy_font(Obj->font);
  
   
    free(Obj);
    free(ele);
}
