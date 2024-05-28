#include "poft.h"
#include "../shapes/Circle.h"
/*
   [PofT function]
*/
Elements *New_PofT(int label, int x, int y, int vx, int vy)
{
    PofT *pDerivedObj = (PofT *)malloc(sizeof(PofT));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/projectile.png");
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
    //pObj->inter_obj[pObj->inter_len++] = Tree_L;
    //pObj->inter_obj[pObj->inter_len++] = Floor_L;
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
}
void _PofT_update_position(Elements *self, int dx, int dy)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    Obj->x += dx;
    Obj->y += dy;
    Shape *hitbox = Obj->hitbox;
    hitbox->update_center_x(hitbox, dx);
    hitbox->update_center_y(hitbox, dy);
}
void PofT_interact(Elements *self, Elements *tar)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->y < 0 - Obj->height)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
        else if (Obj->x > HEIGHT + Obj->height)
            self->dele = true;
    /*
    if (tar->label == Floor_L)
    {
        if (Obj->x < 0 - Obj->width)
            self->dele = true;
        else if (Obj->y < 0 - Obj->height)
            self->dele = true;
        else if (Obj->x > WIDTH + Obj->width)
            self->dele = true;
        else if (Obj->x > HEIGHT + Obj->height)
            self->dele = true;
    }
    else if (tar->label == Tree_L)
    {
        Tree *tree = ((Tree *)(tar->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self->dele = true;
        }
    }
    */
}
void PofT_draw(Elements *self)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    if (Obj->vx > 0) //need to fix
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void PofT_destory(Elements *self)
{
    PofT *Obj = ((PofT *)(self->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(self);
}
