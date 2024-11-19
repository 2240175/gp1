#include "scene_enemy.h"

Sprite* sprNPC[5];


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
	for (int i = 0; i < 5; i++) {
		safe_delete(sprNPC[i]);
	}
}

void enemy_update()
{
	switch (enemy_state) {
	case 0:
		sprNPC[0] = sprite_load(L"./Data/Images/one.png");
		sprNPC[1] = sprite_load(L"./Data/Images/two.png");
		sprNPC[2] = sprite_load(L"./Data/Images/one.png");
		sprNPC[3] = sprite_load(L"./Data/Images/one.png");
		sprNPC[4] = sprite_load(L"./Data/Images/one.png");
	}
	if (Check == false) {
		NPCCard = rand() % 5;
		UseCard[NPCCard + 4] == true;
	}
}

void enemy_render()
{
	switch (NPCCard) {
	case 0:
		sprite_render(sprNPC[NPCCard], 300, 500);
		break;
	case 1:
		sprite_render(sprNPC[NPCCard], 300, 500);
		break;
	case 2:
		sprite_render(sprNPC[NPCCard], 300, 500);
		break;
	case 3:
		sprite_render(sprNPC[NPCCard], 300, 500);
		break;
	case 4:
		sprite_render(sprNPC[NPCCard], 300, 500);
		break;
	}
}