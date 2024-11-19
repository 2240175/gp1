#include "scene_enemy.h"

int enemy_timer;
int enemy_state;

int NPCCard;

void enemy_init()
{
	enemy_timer = 0;
	enemy_state = 0;
	NPCCard = 0;
}

void enemy_deinit()
{
	enemy_timer = 0;
	enemy_state = 0;
	NPCCard = 0;
}

void enemy_update()
{
}

void enemy_render()
{
}