#include "poft.h"
#include "../shapes/Circle.h"
#include "../scene/sceneManager.h"
ALLEGRO_BITMAP *bitmap_poft;
/*
   [PofT function]
*/
Elements *New_PofT(int label, int x, int y, int vx, int vy)
{
    PofT *pDerivedObj = (PofT *)malloc(sizeof(PofT));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = bitmap_poft;
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x;
    pDerivedObj->y = y;
    pDerivedObj->vx = vx;
    pDerivedObj->vy = vy;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Monster_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    pObj->inter_obj[pObj->inter_len++] = Character_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = PofT_update;
    pObj->Interact = PofT_interact;
    pObj->Draw = PofT_draw;
    pObj->Destroy = PofT_destory;

    return pObj;
}
void PofT_update(Elements *self)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    _PofT_update_position(self, Obj->vx, Obj->vy);

    // if (!(timer%60))
    // {
    //     int a = 5;
    //     int b = 5;
    //     //create projectile of tower
    //     Elements *pro;
    //     pro = New_PofT(PofT_L,
    //                     Obj->x + ( Obj->width ) /2-5,
    //                     Obj->y + ( Obj->height ) /2-5,
    //                     a, b);
    //     _Register_elements(scene, pro);
    //     pro = New_PofT(PofT_L,
    //                     Obj->x + ( Obj->width ) /2-5,
    //                     Obj->y + ( Obj->height ) /2-5,
    //                     a, -b);
    //     _Register_elements(scene, pro);
    //     pro = New_PofT(PofT_L,
    //                     Obj->x + ( Obj->width ) /2-5,
    //                     Obj->y + ( Obj->height ) /2-5,
    //                     -a, b);
    //     _Register_elements(scene, pro);
    //     pro = New_PofT(PofT_L,
    //                     Obj->x + ( Obj->width ) /2-5,
    //                     Obj->y + ( Obj->height ) /2-5,
    //                     -a, -b);
    //     _Register_elements(scene, pro);
    //     self->dele = true;
    // }
}
void _PofT_update_position(Elements *self, int dx, int dy)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    if((Obj->x + dx) < 0 || (Obj->x + Obj->width + dx) > WIDTH)
    {
        self->dele = true;
        return;
    }
    if((Obj->y + dy) < 0 || (Obj->y + Obj->height + dy) > HEIGHT)
    {
        self->dele = true;
        return;
    }
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void PofT_interact(Elements *self, Elements *tar)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));//讓碰到邊緣讓砲彈消失的條件
    if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->y < 0 - Obj->height)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
        else if (Obj->y > HEIGHT + Obj->height)
            self->dele = true;
    }
    else if (tar->label == Monster_L)
    {
        Monster *monster = ((Monster *)(tar->pDerivedObj));
        if (monster->hitbox->overlap(monster->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
    else if (tar->label == Character_L)
    {
        Character *chara = ((Character *)(tar->pDerivedObj));
        if (chara->hitbox->overlap(chara->hitbox, Obj->hitbox))
        {
            self->dele = true;
            chara_Helath_Point--;
            if(chara_Helath_Point < 1) window = 2;
        }
    }
}
void PofT_draw(Elements *self)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0); 
}
void PofT_destory(Elements *self)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    //al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}

void poft_load_bitmap_sound()
{
    bitmap_poft = al_load_bitmap("assets/image/projectile.png");
    poft_Sound = al_create_sample_instance(al_load_sample("assets/sound/laser_sfx.ogg"));//taking_damage_sfx.ogg
    al_set_sample_instance_playmode(poft_Sound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(poft_Sound, al_get_default_mixer());
    al_set_sample_instance_gain(poft_Sound, 0.5);
}