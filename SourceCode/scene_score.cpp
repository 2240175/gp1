#include "scene_score.h"

int score_timer;
int score_state;

extern int Game_Winner;

Sprite* sprScore[4];

void score_init()
{
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

		break;
	}
}	 

void score_render()
{
	sprite_render(sprScore[0], 0, 0);
	switch (Game_Winner) {
	case 0:
		sprite_render(sprScore[3], 0, 250);
		break;
	case 1:
		sprite_render(sprScore[1], 0, 250);
		break;
	case 2:
		sprite_render(sprScore[2], 0, 250);
		break;
	}
}