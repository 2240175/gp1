#include "scene_enemy.h"

int enemy_timer;
int enemy_state;

int NPCCard;

extern bool UseCard[10];
bool Check;

void enemy_init()
{
	enemy_timer = 0;
	enemy_state = 0;
	NPCCard = 0;
	Check = false;
}

void enemy_deinit()
{
	enemy_timer = 0;
	enemy_state = 0;
	NPCCard = 0;
}

void enemy_update()
{
	if (Check == false) {
		NPCCard = rand() % 5;
		UseCard[NPCCard + 4] == true;
	}
}

void enemy_render()
{
}