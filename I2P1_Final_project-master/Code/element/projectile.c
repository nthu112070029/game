#include "projectile.h"
#include "../shapes/Circle.h"
/*
   [Projectile function]
*/
Elements *New_Projectile(int label, int x, int y, int v)
{
    Projectile *pDerivedObj = (Projectile *)malloc(sizeof(Projectile));
    Elements *pObj = New_Elements(label);
    // setting derived object member
    pDerivedObj->img = al_load_bitmap("assets/image/cannonball.png");
    pDerivedObj->width = al_get_bitmap_width(pDerivedObj->img);
    pDerivedObj->height = al_get_bitmap_height(pDerivedObj->img);
    pDerivedObj->x = x - pDerivedObj->width/2;
    pDerivedObj->y = y - pDerivedObj->height/2;
    pDerivedObj->v = v;
    pDerivedObj->hitbox = New_Circle(pDerivedObj->x + pDerivedObj->width / 2,
                                     pDerivedObj->y + pDerivedObj->height / 2,
                                     min(pDerivedObj->width, pDerivedObj->height) / 2);
    // setting the interact object
    pObj->inter_obj[pObj->inter_len++] = Tree_L;
    pObj->inter_obj[pObj->inter_len++] = Floor_L;
    // setting derived object function
    pObj->pDerivedObj = pDerivedObj;
    pObj->Update = Projectile_update;
    pObj->Interact = Projectile_interact;
    pObj->Draw = Projectile_draw;
    pObj->Destroy = Projectile_destory;

    return pObj;
}

void Projectile_update(Elements *const ele)
{
    Projectile *Obj = ((Projectile *)(ele->pDerivedObj));
   
    _Projectile_update_position(ele, 0,Obj->v);
    
}
void _Projectile_update_position(Elements *const self, int dx, int dy)
{
    Projectile *Obj = ((Projectile *)(self->pDerivedObj));
    if(Obj->x < 0 || Obj->x > WIDTH)
    {
        self->dele = true;
        return;
    }
    if(Obj->y < 0 || (Obj->y > HEIGHT))
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
void Projectile_interact(Elements *const self_ele, Elements *const ele)
{
    Projectile *Obj = ((Projectile *)(self_ele->pDerivedObj));
    if (ele->label == Tree_L)
    {
        Tree *tree = ((Tree *)(ele->pDerivedObj));
        if (tree->hitbox->overlap(tree->hitbox, Obj->hitbox))
        {
            self_ele->dele = true;
        }
    }
}
void Projectile_draw(Elements *const ele)
{
    Projectile *Obj = ((Projectile *)(ele->pDerivedObj));
    if (Obj->v > 0)
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, ALLEGRO_FLIP_HORIZONTAL);
    else
        al_draw_bitmap(Obj->img, Obj->x, Obj->y, 0);
}
void Projectile_destory(Elements *const ele)
{
    Projectile *Obj = ((Projectile *)(ele->pDerivedObj));
    al_destroy_bitmap(Obj->img);
    free(Obj->hitbox);
    free(Obj);
    free(ele);
}
