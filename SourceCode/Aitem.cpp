#include "Aitem.h"

bool AitemNum[10] = { false };

Sprite* AitemPNG;

extern int winner;
extern int raund;
extern int winraund;
extern int lossraund;

extern int StarPiece;

bool AitemNum[7] = { false };

int money = rand() % 3;
int AitemSelect = 0;

void Aitem_init()
{
	AitemPNG = sprite_load(L"./Data/Images/Aitem/Aitem.png");
}

void Aitem_deinit()
{
	safe_delete(AitemPNG);
}

void Aitem_update()
{
	//アイテムに触れて押したらその数値を送る
}

void Aitem_render()
{
	sprite_render(AitemPNG, 0, 0);
}

void AitemBuy()
{
	switch (AitemSelect) {
	case 0:
		break;
	case 1:
		if (AitemNum[0] == false&& StarPiece>=3) {
			AitemNum[0] = true;
			StarPiece += -3;
		}
		break;
	}
}
