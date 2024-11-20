#include "scene_score.h"

int score_timer;
int score_state;

Sprite* sprScore;

void score_init()
{
	score_timer = 0;
	score_state = 0;
}	

void score_deinit() 
{
	safe_delete(sprScore);
}

void score_update() 
{
	switch (score_state) {
	case 0:
		sprScore = sprite_load(L"./Data/Images/m.jpg");
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
	sprite_render(sprScore, 0, 0);
}