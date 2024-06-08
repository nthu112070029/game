#include <allegro5/allegro_primitives.h>
#include "Lose.h"
/*
   [Lose function]
*/
Scene *New_Lose(int label)
{
    Lose *pDerivedObj = (Lose *)malloc(sizeof(Lose));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    
    pDerivedObj->font = al_load_ttf_font("assets/font/pirulen.ttf", 12, 0);
     pDerivedObj->background = al_load_bitmap("assets/image/lose.png");
    // Load sound
    pDerivedObj->song = al_load_sample("assets/sound/lose.mp3");
    //al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    pDerivedObj->title_x = WIDTH / 2;
    pDerivedObj->title_y = HEIGHT / 2;
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    // register element
    _Register_elements(pObj, New_Button(Button_L));
    // setting derived object function
    pObj->Update = Lose_update;
    pObj->Draw = Lose_draw;
    pObj->Destroy = Lose_destroy;
    return pObj;
}
void Lose_update(Scene *const pLoseObj)
{
   // update every element
    ElementVec allEle = _Get_all_elements(pLoseObj);
    for (int i = 0; i < allEle.len; i++)
    {
        allEle.arr[i]->Update(allEle.arr[i]);
    }

    // run interact for every element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        // run every interact object
        for (int j = 0; j < ele->inter_len; j++)
        {
            int inter_label = ele->inter_obj[j];
            ElementVec labelEle = _Get_label_elements(pLoseObj, inter_label);
            //printf( "labal:%d\n", labelEle.len );
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(pLoseObj, ele);
    }
}
void Lose_draw(Scene *const pLoseObj)
{
     
    Lose *Obj = ((Lose *)(pLoseObj->pDerivedObj));
     al_draw_bitmap(Obj->background, 0, 0, 0);
   //al_draw_text(Obj->font, al_map_rgb(255, 255, 255), Obj->title_x, Obj->title_y, ALLEGRO_ALIGN_CENTRE, "YOU LOSE");
    //al_draw_rectangle(Obj->title_x - 150, Obj->title_y - 30, Obj->title_x + 150, Obj->title_y + 30, al_map_rgb(255, 255, 255), 0);
    al_play_sample_instance(Obj->sample_instance);
    ElementVec allEle = _Get_all_elements(pLoseObj);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void Lose_destroy(Scene *const pLoseObj)
{
    Lose *Obj = ((Lose *)(pLoseObj->pDerivedObj));
     ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    al_destroy_font(Obj->font);
    al_destroy_sample(Obj->song);
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(pLoseObj);
}
