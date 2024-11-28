#include "end.h"

Sprite* sprEnd[3];

int end_timer;
int end_state;


void end_init()
{
	end_timer = 0;
	end_state = 0;
	music::play(5, false);
}

void end_deinit()
{
	for (int i = 0; i < 3; i++) {
		safe_delete(sprEnd[i]);
	}
	music::stop(5);
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
		if (end_timer > 7380 || end_timer > 30 && GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			nextScene = SCENE_TITLE;
		}
		break;
	}

	
	end_timer++;
}

void end_render()
{
	GameLib::clear(0.0f, 0.0f, 0.0f);

		
	sprite_render(sprEnd[0], 0, ((-end_timer)+ 2057)*0.35f);
	
	sprite_render(sprEnd[1], 0, ((-end_timer) + 4114)*0.35f);
	
	sprite_render(sprEnd[2], 0, ((-end_timer) + 6891)*0.35f);

	if (end_timer> 6891) {
		sprite_render(sprEnd[2], 0, 0);
	}
		
	
	//debug::display(1.0f, 1.0f, 1.0f, 1.5f, 1.2f);
	//debug::setString("end_timer:%d", end_timer);
	if (end_timer > 30) {
		font::textOut(4, "Click Skip", VECTOR2(1070, 700), VECTOR2(1.0f, 1.0f), VECTOR4(0.7f, 0.7f, 0.7f, 0.7f));
	}
}