#include "scene_enemy.h"
#include "Aitem.h"

Sprite* sprNPC[5];


int enemy_timer;
int enemy_state;

int NPCCard;

extern int NPCNUM;
extern int money;

extern bool AitemDATE[7];
//�I�Ԃ͈̂�񂾂��ł���
bool Check;

//�����̂�I�΂Ȃ��悤��
bool npc[5] = {false};

void enemy_init()
{
	enemy_timer = 0;
	enemy_state = 0;
	NPCCard = -1;
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
		sprNPC[4] = sprite_load(L"./Data/Images/Card/one.png");
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
	//�G�̃J�[�h���f���ꏊ
	if (AitemDATE[2] == true && NPCNUM > 1) {
		NPCCard -= 1;
		debug::setString("Stae Dawn NPC	:%d", NPCNUM);
		AitemDATE[2] = false;
	}
	//�A�j���\�V�����p
	switch (NPCCard) {
	case 0:
		sprite_render(sprNPC[NPCCard], 900, 200);
		NPCNUM = 1;
		break;
	case 1:
		sprite_render(sprNPC[NPCCard], 900, 200);
		NPCNUM = 2;
		break;
	case 2:
		sprite_render(sprNPC[NPCCard], 900, 200);
		NPCNUM = 3;
		break;
	case 3:
		sprite_render(sprNPC[NPCCard], 900, 200);
		NPCNUM = 4;
		break;
	case 4:
		sprite_render(sprNPC[NPCCard], 900, 200);
		NPCNUM =5;
		break;
	}
}