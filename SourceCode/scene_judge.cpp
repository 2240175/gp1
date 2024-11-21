#include "Card.h"
#include "scene_enemy.h"
#include "scene_judge.h"
#include "Aitem.h"

//別ファイルの変数など
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

//どっちが勝つかな
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

		judge_state++;
		/*fallthrough*/
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		judge_state++;
		/*fallthrough*/
	case 2:
		debug::setString("JUDGE TIME");
		debug::setString("judge_timer:%d", judge_timer/60);


		debug::setString("NPC	:%d", NPCNUM);
		debug::setString("PLAYER:%d", PLAYERNUM);

		if (AitemDATE[2] == true&&NPCNUM>1) {
			NPCNUM-=1;
			debug::setString("Stae Dawn NPC	:%d", NPCNUM);
			AitemDATE[2] = false;
		}

		//無条件勝敗アイテムがオフの時
		if (AitemDATE[5] == false) {
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
			//時計効果ありの時（反転）
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
		//onの時
		else if (AitemDATE[5] == true) {
			randam = rand() % 5;
			if (randam == 3) {
				debug::setString("Ticket	WIN!");
				winner == WIN;
			}
			else {
				debug::setString("Ticket	LOSS");
				winner == LOSS;
			}
			AitemDATE[5] = false;
		}

		if (getraund == false) {
			if (AitemDATE[4] == false) {
				if (winner == WIN) {
					StarPiece += PLAYERNUM;
					winraund += 1;
				}
				else if (winner == DRAW) {
					winraund += 0;
					lossraund += 0;
				}
				else if (winner == LOSS) {

					NPCPiece += NPCNUM;
					lossraund += 1;

				}
			}
			else if (AitemDATE[4] == true) {
				if (winner == WIN) {
					StarPiece += PLAYERNUM;
					winraund += 2;
				}
				else if (winner == DRAW) {
					winraund += 0;
					lossraund += 0;
				}
				else if (winner == LOSS) {

					NPCPiece += NPCNUM;
					lossraund += 2;

				}
			}
			raund++;
			getraund = true;
		}



		if (winraund >= MAXRAUND) {
			if (TRG(0) & PAD_TRG1) {
				Game_Winner = 1;
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if(lossraund >= MAXRAUND){
			if (TRG(0) & PAD_TRG1) {
				Game_Winner = 2;
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