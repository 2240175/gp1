#include "all.h"
#include "player.h"
#include "Mausu.h"

int home_state;
int home_timer;

Sprite* sprBack;
Sprite* sprSelect[2];
MouseManager mouseManager;

void home_init()
{
    home_state = 0;
    home_timer = 0;
    player_init();
}