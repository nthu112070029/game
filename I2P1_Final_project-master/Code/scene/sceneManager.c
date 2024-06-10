#include "sceneManager.h"
#include "menu.h"
#include "Win.h"
#include "Lose.h"
#include "gamescene.h"
Scene *scene = NULL;
void create_scene(SceneType type)
{
    switch (type)
    {
    case Menu_L:
        scene = New_Menu(Menu_L);
        break;
    case GameScene_L:
        scene = New_GameScene(GameScene_L);
        break;
     case Lose_L:
        scene = New_Lose(Lose_L);
        break;
     case Win_L:
        scene = New_Win(Win_L);
        break;
    default:
        break;
    }
}