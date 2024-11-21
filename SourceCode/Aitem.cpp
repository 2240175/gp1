#include "Aitem.h"

bool AitemNum[10] = { false };

Sprite* AitemPNG;
Sprite* AitemPNG2;
MouseManager mouse;

extern int winner;
extern int raund;
extern int winraund;
extern int lossraund;

extern int StarPiece;

extern bool aitem_time;

bool AitemDATE[7] = { false };

int money = rand() % 3;


void Aitem_init()
{
	AitemPNG = sprite_load(L"./Data/Images/Aitem/Aitem.png");
	AitemPNG2 = sprite_load(L"./Data/Images/Aitem/Aitem2.png");
}

void Aitem_deinit()
{
	safe_delete(AitemPNG);
	safe_delete(AitemPNG2);
}

void Aitem_update()
{
	//アイテムに触れて押したらその数値を送る
	// マウスの座標を更新し、取得する
	mouse.Update();
	POINT mousePos = mouse.GetPosition();
	//望遠鏡
	if (mousePos.x > 399 && mousePos.y > 226 && mousePos.x < 520 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[0] = true;
		}
	}
	//キャンディー
	if (mousePos.x > 596 && mousePos.y > 226 && mousePos.x < 724 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[1] = true;
		}
	}
	//UFO
	if (mousePos.x > 770 && mousePos.y > 226 && mousePos.x < 900 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[2] = true;
		}
	}
	//時計
	if (mousePos.x > 399 && mousePos.y > 420 && mousePos.x < 520 && mousePos.y < 520) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[3] = true;
		}
	}
	//ベル
	if (mousePos.x > 596 && mousePos.y > 420 && mousePos.x < 724 && mousePos.y < 520) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[4] = true;
		}
	}
	//チケット
	if (mousePos.x > 770 && mousePos.y > 420 && mousePos.x < 900 && mousePos.y < 520) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			AitemDATE[5] = true;
		}
	}
	//戻る
	if (mousePos.x > 548 && mousePos.y > 486 && mousePos.x < 767 && mousePos.y < 513) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			aitem_time = false;
		}
	}
}

void Aitem_render()
{
	sprite_render(AitemPNG2, 340, 160);
}

void AitemBuy()
{

}
