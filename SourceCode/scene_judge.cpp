#include "Card.h"
#include "scene_enemy.h"
#include "scene_judge.h"

//•Êƒtƒ@ƒCƒ‹‚Ì•Ï”‚È‚Ç
extern OBJ2D AnyCard[CARD_MAX];
extern bool UseCard[10];

extern int winner;
extern int winraund;
extern int lossraund;
extern int raund;
extern int MAXRAUND;

extern int StarPiece;
extern int NPCPiece;

bool getraund = false;

Sprite* sprck;

int judge_timer;
int judge_state;
int judge_time;


int NPCNUM;
int PLAYERNUM;

void judge_init()
{
	judge_timer = 0;
	judge_state = 0;
	judge_time = 0;
	NPCNUM = 0;
	PLAYERNUM = 0;
	enemy_init();
}

void judge_deinit()
{
	judge_timer = 0;
	judge_state = 0;
	judge_time = 0;

	for (int i = 0; i < 10; i++) {
		UseCard[i] = false;
	}

	getraund = false;

	enemy_deinit();
	safe_delete(sprck);
}

void judge_update()
{
	switch (judge_state) {
	case 0:
		sprck = sprite_load(L"./Data/Images/m.png");
		enemy_update();

		judge_state++;
		/*fallthrough*/
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		judge_state++;
		/*fallthrough*/
	case 2:
		debug::setString("JUDGE TIME");
		debug::setString("judge_timer:%d", judge_timer/60);


		debug::setString("NPC:%d", NPCNUM);
		debug::setString("PLAYER:%d", PLAYERNUM);

		for (int i = 0; i < 10; i++) {
			if (UseCard[i] == true) {
				if (i < 5) {
					PLAYERNUM = i + 1;
				}
				else {
					NPCNUM = i - 4;
				}
			}
		}

		if (PLAYERNUM < NPCNUM) {
			debug::setString("NPC WIN");
			winner = LOSS;
		}
		else if (PLAYERNUM > NPCNUM) {
			debug::setString("PLAYER WIN");
			winner = WIN;
		}
		else {
			debug::setString("!!!!!DRAW!!!!!");
			winner = DRAW;
		}

		if (getraund == false) {
			if (winner == LOSS) {
				NPCPiece += NPCNUM;
				lossraund++;
			}
			else if (winner == WIN) {
				StarPiece += PLAYERNUM;
				winraund++;
			}
			else if (winner == DRAW) {
			}
			raund++;
			getraund = true;
		}

		if (winraund >= MAXRAUND || lossraund >= MAXRAUND) {
			if (TRG(0) & PAD_TRG1) {
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if (TRG(0) & PAD_TRG1) {
			nextScene = SCENE_GAME;
		}

		debug::setString("NEXT RAUND:%d",raund);

		break;
	}

	judge_timer++;
}

void judge_render()
{
	sprite_render(sprck, 0, 0);

	enemy_render();
}