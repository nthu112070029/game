#include "gamescene.h"
#include "../scene/sceneManager.h"
// .h file註冊在gamescene.h

void New_camp_use_map(Scene *const);

/*
   [GameScene function]
*/
Scene *New_GameScene(int label)
{
    timer = 0;
    money_num = 1000;
    memset(tower_placed, 0, 1000);
    camp_load_bitmap();
    monster_load_bitmap();
    tower_load_bitmap();
    poft_load_bitmap_sound();

    GameScene *pDerivedObj = (GameScene *)malloc(sizeof(GameScene));
    Scene *pObj = New_Scene(label);
    // setting derived object member
    pDerivedObj->background = al_load_bitmap("assets/image/stage.png");
    

    //sound
    pDerivedObj->song = al_load_sample("assets/sound/game_scene.mp3");
    al_reserve_samples(20);
    pDerivedObj->sample_instance = al_create_sample_instance(pDerivedObj->song);
    // Loop the song until the display closes
    al_set_sample_instance_playmode(pDerivedObj->sample_instance, ALLEGRO_PLAYMODE_LOOP);
    al_restore_default_mixer();
    al_attach_sample_instance_to_mixer(pDerivedObj->sample_instance, al_get_default_mixer());
    // set the volume of instance
    al_set_sample_instance_gain(pDerivedObj->sample_instance, 0.1);
    pObj->pDerivedObj = pDerivedObj;
    //pObj->pDerivedObj = pDerivedObj;
    
    // register element
    _Register_elements(pObj, New_Floor(Floor_L));
    _Register_elements(pObj, New_Character(Character_L));
    _Register_elements(pObj, New_Ball(Ball_L));
    _Register_elements(pObj, New_castle(Castle_L));
    _Register_elements(pObj, New_money_col(money_col_L));  
    //_Register_elements(pObj, New_camp(camp_L));
    _Register_elements(pObj, New_Monster(Monster_L));
    _Register_elements(pObj, New_cannon(Cannon_L));
    New_camp_use_map(pObj);

    


    // setting derived object function
    pObj->Update = game_scene_update;
    pObj->Draw = game_scene_draw;
    pObj->Destroy = game_scene_destroy;
    return pObj;
}

int counter_of_monster = 0;
void game_scene_update(Scene *const pGameSceneObj)
{
    if(window != 1)
    {
        pGameSceneObj->scene_end = true;
    }
    if(monster_killed>50)// kill 6 game win
    {
        window=3;
        //pGameSceneObj->scene_end = true;
    }

    timer++;
    //create monster
    if (!(timer%600))
    {
        counter_of_monster = timer/60;
    }
    if (!(timer%60))
    {
        counter_of_monster--;
        if(counter_of_monster > 0)
        {
            _Register_elements(scene, New_Monster(Monster_L));
        }
    }
    if (!(timer%120))
    {
        if (counter_of_tower > 0)al_play_sample_instance(poft_Sound);
    };

    // update every element
    ElementVec allEle = _Get_all_elements(pGameSceneObj);
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
            ElementVec labelEle = _Get_label_elements(pGameSceneObj, inter_label);
            //printf( "labal:%d\n", labelEle.len );
            for (int i = 0; i < labelEle.len; i++)
            {
                ele->Interact(ele, labelEle.arr[i]);
                if(ele->label == Character_L && campID_CharacterHit != -1) break;
                if(ele->label == Ball_L && camp_BallHit) break;
            }
        }
    }
    // remove element
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        if (ele->dele)
            _Remove_elements(pGameSceneObj, ele);
    }
}
void game_scene_draw(Scene *const pGameSceneObj)
{
    al_clear_to_color(al_map_rgb(0, 0, 0));
    GameScene *gs = ((GameScene *)(pGameSceneObj->pDerivedObj));

    al_play_sample_instance(gs->sample_instance);

    al_draw_bitmap(gs->background, 0, 0, 0);
    ElementVec allEle = _Get_all_elements(pGameSceneObj);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Draw(ele);
    }
}
void game_scene_destroy(Scene *const pGameSceneObj)
{
    GameScene *Obj = ((GameScene *)(pGameSceneObj->pDerivedObj));
    ALLEGRO_BITMAP *background = Obj->background;
    al_destroy_bitmap(background);
    ElementVec allEle = _Get_all_elements(pGameSceneObj);
    for (int i = 0; i < allEle.len; i++)
    {
        Elements *ele = allEle.arr[i];
        ele->Destroy(ele);
    }
    al_destroy_sample_instance(Obj->sample_instance);
    free(Obj);
    free(pGameSceneObj);
}

void New_camp_use_map(Scene *const scene)
{
    int map_data[14][20];
    FILE *data;

    data = fopen("assets/map/camp.txt", "r");
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            fscanf(data, "%d", &map_data[i][j]);
        }
    }
    fclose(data);

    Elements *cam;
    for (int i = 0; i < 14; i++)
    {
        for (int j = 0; j < 20; j++)
        {
            if (map_data[i][j])
            {
              cam = New_camp(camp_L,j,i);
              _Register_elements(scene, cam);
            }
        }
    }
}