#include "Info.h"

Sprite* sprRule[5];

MouseManager cusol;


int  rule_timer;
int  rule_state;
bool  rule_time;

extern int game_timer;
void info_init()
{
	rule_timer = 0;

	sprRule[0] = sprite_load(L"./Data/Images/Info/rule1.png");
	sprRule[1] = sprite_load(L"./Data/Images/Info/rule2.png");
	sprRule[2] = sprite_load(L"./Data/Images/Info/rule3.png");
	sprRule[3] = sprite_load(L"./Data/Images/Info/rule4.png");
	sprRule[4] = sprite_load(L"./Data/Images/Info/rule5.png");
}

void info_deinit()
{
	rule_time = false;
	rule_state = 0;
	for (int i = 0; i < 5; i++) {
		safe_delete(sprRule[i]);
	}
}

void info_update()
{	//アイテムに触れて押したらその数値を送る
	// マウスの座標を更新し、取得する
	cusol.Update();
	POINT mousePos = cusol.GetPosition();
	if (rule_state > 0 && rule_state < 4) {
		if (mousePos.x > 22 && mousePos.y > 300 && mousePos.x < 134 && mousePos.y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&&rule_timer>10) {
				rule_state--;
				rule_timer = 0;
			}
		}
		else if (mousePos.x > 1143 && mousePos.y > 300 && mousePos.x < 1256 && mousePos.y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state++;
				rule_timer = 0;
			}
		}
	}
	if (rule_state == 0) {
		if (mousePos.x > 1143 && mousePos.y > 300 && mousePos.x < 1256 && mousePos.y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state++;
				rule_timer = 0;
			}
		}
	}
	if (rule_state == 4) {
		if (mousePos.x > 22 && mousePos.y > 300 && mousePos.x < 134 && mousePos.y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state--;
				rule_timer = 0;
			}
		}
		else if (mousePos.x > 1143 && mousePos.y > 300 && mousePos.x < 1256 && mousePos.y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_time = false;
				info_deinit();
				game_timer = 0;
			}
		}
	}

	rule_timer++;
}

void info_render()
{
	if (rule_time == true) {
		sprite_render(sprRule[rule_state], 0, 0);
	}
}