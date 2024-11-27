#include "scene_score.h"

int score_timer;
int score_state;

extern int Game_Winner;
extern bool restart;
extern bool UseCard[5];

Sprite* sprScore[4];

void score_init()
{
	//scene_game
	game_deinit();
	//マウスカーソル表示
	ShowCursor(true);
	restart = false;

	for (int i = 0; i < 5; i++) {
		UseCard[i]=false;
	}
	//music
	music::stop(2);
	music::stop(3);
	music::stop(4);

	score_timer = 0;
	score_state = 0;
}	

void score_deinit() 
{
	for (int i = 0; i < 4; i++) {
		safe_delete(sprScore[i]);
	}
}

void score_update() 
{
	switch (score_state) {
	case 0:
		sprScore[0] = sprite_load(L"./Data/Images/m.jpg");
		sprScore[1] = sprite_load(L"./Data/Images/win.png");
		sprScore[2] = sprite_load(L"./Data/Images/loss.png");
		sprScore[3] = sprite_load(L"./Data/Images/error.png");
		score_state++;
		/*fallthrough*/
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		score_state++;
		/*fallthrough*/
	case 2:
		if (score_timer > 300) {
			nextScene = SCENE_END;
			break;
		}
	}

	debug::setString("SCORE_TIMER:%d",score_timer);

	score_timer++;
}	 

void score_render()
{
	sprite_render(sprScore[0], 0, 0);
	switch (Game_Winner) {
	case 0:
		sprite_render(sprScore[3], 0, 250);
		break;
	case 1:
		sprite_render(sprScore[1], 0, 0);
		break;
	case 2:
		sprite_render(sprScore[2], 0, 0);
		break;
	}
}