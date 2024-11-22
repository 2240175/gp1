#include "Card.h"
#include "scene_enemy.h"
#include "scene_judge.h"
#include "Aitem.h"

//�ʃt�@�C���̕ϐ��Ȃ�
extern OBJ2D AnyCard[CARD_MAX];

extern bool OVERBUY[7];
extern bool AitemDATE[7];

extern int winner;
extern int winraund;
extern int lossraund;
extern int raund;
extern int MAXRAUND;

extern int StarPiece;
extern int NPCPiece;

extern int Game_Winner;

bool getraund;



Sprite* sprck;

int stopraund;
int judge_timer;
int judge_state;
int judge_time;

//�ǂ�����������
int randam;

int NPCNUM;
int PLAYERNUM;

void judge_init()
{
	stopraund = raund;
	getraund = false;
	judge_timer = 0;
	judge_state = 0;
	judge_time = 0;
	enemy_init();
}

void judge_deinit()
{
	judge_timer = 0;
	judge_state = 0;
	judge_time = 0;

	getraund = false;
	for (int i = 0; i < 7; i++) {
		OVERBUY[i] = false;
		AitemDATE[i] = false;
	}

	enemy_deinit();
	safe_delete(sprck);
}

void judge_update()
{
	switch (judge_state) {
	case 0:
		sprck = sprite_load(L"./Data/Images/m.png");
		enemy_update();
		randam = rand() % 5;

		judge_state++;
		/*fallthrough*/
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		judge_state++;
		/*fallthrough*/
	case 2:
		debug::setString("JUDGE TIME");
		debug::setString("judge_timer:%d", judge_timer / 60);


		debug::setString("NPC	:%d", NPCNUM);
		debug::setString("PLAYER:%d", PLAYERNUM);
		//���������s�A�C�e�����I�t�̎�
		if (AitemDATE[5] == false) {
			if (AitemDATE[2] == true && NPCNUM > 1) {
				NPCNUM -= 1;
				debug::setString("Stae Dawn NPC	:%d", NPCNUM);
				AitemDATE[2] = false;
			}
			if (AitemDATE[3] == false) {
				if (PLAYERNUM < NPCNUM && AitemDATE[1] == false) {
					debug::setString("			LOSS");
					winner = LOSS;
				}
				else if (PLAYERNUM < NPCNUM && AitemDATE[1] == true) {
					debug::setString("!!!!!DRAW!!!!!");
					winner = DRAW;
				}
				else if (PLAYERNUM > NPCNUM && AitemDATE[1] == false) {
					debug::setString("			WIN");
					winner = WIN;
				}
				else if (PLAYERNUM == NPCNUM) {
					debug::setString("!!!!!DRAW!!!!!");
					winner = DRAW;
				}
			}
			//���v���ʂ���̎��i���]�j
			else if (AitemDATE[3] == true) {
				if (PLAYERNUM < NPCNUM && AitemDATE[1] == false) {
					debug::setString("			WIN!");
					winner = WIN;
				}
				else if (PLAYERNUM > NPCNUM && AitemDATE[1] == true) {
					debug::setString("!!!!!DRAW!!!!!");
					winner = DRAW;
				}
				else if (PLAYERNUM > NPCNUM && AitemDATE[1] == false) {
					debug::setString("			LOSS");
					winner = LOSS;
				}
				else if (PLAYERNUM == NPCNUM) {
					debug::setString("!!!!!DRAW!!!!!");
					winner = DRAW;
				}
			}
		}
		//on�̎�
		else if (AitemDATE[5] == true) {
			if (randam == 3) {
				winner = WIN;
				debug::setString("Ticket	WIN!");
			}
			else {
				winner = LOSS;
				debug::setString("Ticket	LOSS");
			}
		}

		debug::setString("randam:%d", randam);

		if (getraund == false) {
			if (AitemDATE[5] == true && winner == DRAW) {
				winner = LOSS;
			}

			switch (winner) {
			case DRAW:
				break;
			case WIN:
				winraund++;
				if (AitemDATE[4] == true) {
					winraund++;
				}
				break;
			case LOSS:
				lossraund++;
				if (AitemDATE[4] == true) {
					lossraund++;
				}
				break;
			}
		}
		raund++;
		getraund = true;


		if (winraund >= MAXRAUND) {
			if (TRG(0) & PAD_TRG1) {
				Game_Winner = 1;
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if (lossraund >= MAXRAUND) {
			if (TRG(0) & PAD_TRG1) {
				Game_Winner = 2;
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if (TRG(0) & PAD_TRG1) {
			nextScene = SCENE_GAME;
		}

		debug::setString("NEXT RAUND:%d", raund);
		break;

	}
	judge_timer++;
}

void judge_render()
{
	sprite_render(sprck, 0, 0);

	enemy_render();
}