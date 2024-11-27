#include "end.h"

Sprite* sprEnd[3];

int end_timer;
int end_state;


void end_init()
{
	end_timer = 0;
	end_state = 0;
}

void end_deinit()
{
	for (int i = 0; i < 3; i++) {
		safe_delete(sprEnd[i]);
	}
}

void end_update()
{
	switch (end_state) {
	case 0:
		sprEnd[0] = sprite_load(L"./Data/Images/end/ed.png");
		sprEnd[1] = sprite_load(L"./Data/Images/end/ed2.png");
		sprEnd[2] = sprite_load(L"./Data/Images/end/ed3.png");
		end_state++;
		/*fallthrough*/
	case 1:
		GameLib::setBlendMode(Blender::BS_ALPHA);

		end_state++;
		/*fallthrough*/

	case 2:
		if (end_timer > 300) {
			nextScene = SCENE_TITLE;
		}
		break;
	}

	debug::setString("end_timer:%d",end_timer);
	end_timer++;
}

void end_render()
{
	sprite_render(sprEnd[0], 0, 0);
	sprite_render(sprEnd[1], 0, 0);
	sprite_render(sprEnd[2], 0, 0);
}