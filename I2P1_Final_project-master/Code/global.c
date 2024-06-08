#include "global.h"
#include "shapes/Shape.h"
// variables for global usage
const double FPS = 60.0;
const int WIDTH = 1000;
const int HEIGHT = 700;
int window = 0;
int monster_killed=0;
int timer = 0;
int mouse_click_state = 0;
ALLEGRO_EVENT_QUEUE *event_queue = NULL;
ALLEGRO_EVENT event;
ALLEGRO_TIMER *fps = NULL;
bool key_state[ALLEGRO_KEY_MAX] = {false};
bool mouse_state[ALLEGRO_MOUSE_MAX_EXTRA_AXES] = {false};
Point mouse;
bool debug_mode = true;

int money_num = 1000;