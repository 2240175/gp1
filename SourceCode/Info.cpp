#include "Info.h"

Sprite* sprRule[5];
Sprite* black;

MouseManager cusol;


int  rule_timer;
int  rule_state;
bool rule_date;

int  rule_pos_x;
int  rule_pos_y;
bool  rule_time;

extern int game_timer;
extern int home_timer;

void info_init()
{
	rule_timer = 0;

	sprRule[0] = sprite_load(L"./Data/Images/Info/rule1.png");
	sprRule[1] = sprite_load(L"./Data/Images/Info/rule2.png");
	sprRule[2] = sprite_load(L"./Data/Images/Info/rule3.png");
	sprRule[3] = sprite_load(L"./Data/Images/Info/rule4.png");
	sprRule[4] = sprite_load(L"./Data/Images/Info/rule5.png");
	black = sprite_load(L"./Data/Images/Aitem/black.png");
}

void info_deinit()
{
	rule_time = false;
	rule_state = 0;
	for (int i = 0; i < 5; i++) {
		safe_delete(sprRule[i]);
	}
		safe_delete(black);
}

void info_update()
{	//アイテムに触れて押したらその数値を送る
	// マウスの座標を更新し、取得する
	cusol.Update();
	POINT mousePos = cusol.GetPosition();
	if (rule_date == false) {
		rule_pos_x = mousePos.x;
		rule_pos_y = mousePos.y;
	}
	if (rule_state > 0 && rule_state < 4) {
		if (rule_pos_x > 22 && rule_pos_y > 300 && rule_pos_x < 134 && rule_pos_y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&&rule_timer>10) {
				rule_state--;
				rule_timer = 0;
			}
		}
		else if (rule_pos_x > 1143 && rule_pos_y > 300 && rule_pos_x < 1256 && rule_pos_y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state++;
				rule_timer = 0;
			}
		}
	}
	if (rule_state == 0) {
		if (rule_pos_x > 1143 && rule_pos_y > 300 && rule_pos_x < 1256 && rule_pos_y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state++;
				rule_timer = 0;
			}
		}
	}
	if (rule_state == 4) {
		if (rule_pos_x > 22 && rule_pos_y > 300 && rule_pos_x < 134 && rule_pos_y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_state--;
				rule_timer = 0;
			}
		}
		else if (rule_pos_x > 1143 && rule_pos_y > 300 && rule_pos_x < 1256 && rule_pos_y < 440) {
			if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && rule_timer > 10) {
				rule_time = false;
				game_timer = 0;
				home_timer = 0;
			}
		}
	}

	rule_timer++;
}

void info_render()
{
	sprite_render(
		black,
		0, 0,
		1, 1,
		0, 0,
		1280, 720,
		0, 0,
		ToRadian(0),
		1, 1, 1, 0.7f);

	if (rule_time == true) {
		sprite_render(sprRule[rule_state], 0, 0);
	}
}