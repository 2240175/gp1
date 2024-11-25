#include "scene_enemy.h"
#include "Aitem.h"

Sprite* sprNPC[5];


int enemy_timer;
int enemy_state;

int NPCCard;
int NPCLAST;

extern int NPCNUM;
extern int money;
extern int judge_timer;

extern bool AitemDATE[7];
//選ぶのは一回だけでいい
bool Check;

//同じのを選ばないように
bool npc[5] = {false};

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
		sprNPC[0] = sprite_load(L"./Data/Images/Card/one.png");
		sprNPC[1] = sprite_load(L"./Data/Images/Card/two.png");
		sprNPC[2] = sprite_load(L"./Data/Images/Card/three.png");
		sprNPC[3] = sprite_load(L"./Data/Images/Card/four.png");
		sprNPC[4] = sprite_load(L"./Data/Images/Card/five.png");
		break;
	}
	if (Check == false) {
		//NPCCard = 4;
		if (AitemDATE[0] == false) {
			while (1) {
				NPCCard = rand() % 5;
				if (npc[NPCCard] == false) break;
			}
			NPCNUM = NPCCard + 1;
			npc[NPCCard] = true;
		}
		else {
			NPCCard =money;
			NPCNUM = NPCCard + 1;
		}
	}

}

void enemy_render()
{
	//アニメ―ション用
	switch (NPCCard) {
	case 0:
		if (judge_timer < 22.5f) {
			sprite_render(sprNPC[NPCCard], (1280 - (judge_timer * 16.0f)), 200);
		}
		else {
			sprite_render(sprNPC[NPCCard], 920, 200);
		}
		NPCNUM = 1;
		break;
	case 1:
		if (judge_timer < 22.5f) {
			sprite_render(sprNPC[NPCCard], (1280 - (judge_timer * 16.0f)), 200);
		}
		else {
			sprite_render(sprNPC[NPCCard], 920, 200);
		}
		NPCNUM = 2;
		break;
	case 2:
		if (judge_timer < 22.5f) {
			sprite_render(sprNPC[NPCCard], (1280 - (judge_timer * 16.0f)), 200);
		}
		else {
			sprite_render(sprNPC[NPCCard], 920, 200);
		}
		NPCNUM = 3;
		break;
	case 3:
		if (judge_timer < 22.5f) {
			sprite_render(sprNPC[NPCCard], (1280 - (judge_timer * 16.0f)), 200);
		}
		else {
			sprite_render(sprNPC[NPCCard], 920, 200);
		}
		NPCNUM = 4;
		break;
	case 4:
		if (judge_timer < 22.5f) {
			sprite_render(sprNPC[NPCCard], (1280 - (judge_timer * 16.0f)), 200);
		}
		else {
			sprite_render(sprNPC[NPCCard], 920, 200);
		}
		NPCNUM =5;
		break;
	}
}

void enemy_reset()
{
	enemy_timer = 0;
	enemy_state = 0;
	Check = false;
	NPCCard = 0;
}