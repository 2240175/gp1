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


Sprite* PlayerCard[5];

Sprite* sprck;
Sprite* fait[4];

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
	for (int i = 0; i < 4; i++) {
		safe_delete(fait[i]);
	}
	for (int i = 0; i < 5; i++) {
		safe_delete(PlayerCard[i]);
	}
}

void judge_update()
{
	switch (judge_state) {
	case 0:
		sprck = sprite_load(L"./Data/Images/maingame2.png");
		//勝敗画像
		fait[0] = sprite_load(L"./Data/Images/judge/vs.png");
		fait[1] = sprite_load(L"./Data/Images/judge/lost.png");
		fait[2] = sprite_load(L"./Data/Images/judge/get.png");
		fait[3] = sprite_load(L"./Data/Images/Aitem/black.png");
		//プレイヤーカード画像
		PlayerCard[0]=sprite_load(L"./Data/Images/Card/one.png");
		PlayerCard[1]=sprite_load(L"./Data/Images/Card/two.png");
		PlayerCard[2]=sprite_load(L"./Data/Images/Card/three.png");
		PlayerCard[3]=sprite_load(L"./Data/Images/Card/four.png");
		PlayerCard[4]=sprite_load(L"./Data/Images/Card/one.png");

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
		//無条件勝敗アイテムがオフの時
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
		debug::setString("TIMER:%d", judge_timer/60);

		if (getraund == false) {
			if (AitemDATE[5] == true && winner == DRAW) {
				winner = LOSS;
			}

			switch (winner) {
			case DRAW:
				break;
			case WIN:
				StarPiece += PLAYERNUM;
				winraund++;
				if (AitemDATE[4] == true) {
					winraund++;
				}
				break;
			case LOSS:
				NPCPiece += NPCNUM;
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
			if (judge_timer>240) {
				Game_Winner = 1;
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if (lossraund >= MAXRAUND) {
			if (judge_timer > 240) {
				Game_Winner = 2;
				nextScene = SCENE_SCORE;
				break;
			}
		}
		else if (judge_timer > 240) {
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
	sprite_render(fait[3],
		0, 0,
		1, 1,
		0, 0,
		1280, 720,
		0, 0,
		ToRadian(0),
		1, 1, 1, 0.6f);




	sprite_render(fait[0], 0, 0);

	primitive::rect(525, 200, 244, 30, 0, 0, ToRadian(0), 1, 1, 1, 1);
	primitive::rect(528, 202, 240, 26, 0, 0, ToRadian(0), 0, 0, 0, 1);
	if (judge_timer < 60) {
		primitive::rect(528, 202, judge_timer * 1.5f, 26, 0, 0, ToRadian(0), 0.5f, 0.5f, 0.7f, 1);
	}
	else if (judge_timer >= 60 && judge_timer < 209) {
		primitive::rect(528, 202, (judge_timer + 30), 26, 0, 0, ToRadian(0), 0.5f, 0.5f, 0.7f, 1);
	}
	else {
		primitive::rect(528, 202, 240, 26, 0, 0, ToRadian(0), 0.2f, 0.2f, 0.7f, 1);
	}

	if (winner == WIN) {
		sprite_render(fait[2], 0, 0);
	}
	else if (winner == LOSS) {
		sprite_render(fait[1], 0, 0);
	}

	sprite_render(PlayerCard[PLAYERNUM-1], 105, 200);

	enemy_render();
}