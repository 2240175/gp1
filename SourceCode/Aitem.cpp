#include "Aitem.h"

bool AitemNum[10] = { false };

Sprite* AitemPNG;

extern int winner;
extern int raund;
extern int winraund;
extern int lossraund;

extern int StarPiece;

bool AitemDATE[7] = { false };

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
	//�A�C�e���ɐG��ĉ������炻�̐��l�𑗂�
}

void Aitem_render()
{
	sprite_render(AitemPNG, 340, 160);
}

void AitemBuy()
{
	switch (AitemSelect) {
	case 0:
		break;
	case 1:
		//�]����
		if (AitemDATE[0] == false&& StarPiece>=8) {
			AitemDATE[0] = true;
			StarPiece += -8;
		}
		break;
	case 2:
		//�L�����f�B�[
		if (AitemDATE[1] == false && StarPiece >= 8) {
			AitemDATE[1] = true;
			StarPiece += -8;
		}
		break;
	case 3:
		//UFO
		if (AitemDATE[2] == false && StarPiece >= 4) {
			AitemDATE[2] = true;
			StarPiece += -4;
		}
		break;
	case 4:
		//���v
		if (AitemDATE[3] == false && StarPiece >= 8) {
			AitemDATE[3] = true;
			StarPiece += -8;
		}
		break;
	case 5:
		//�x��
		if (AitemDATE[4] == false && StarPiece >= 8) {
			AitemDATE[4] = true;
			StarPiece += -8;
		}
		break;
	case 6:
		//�`�P�b�g
		if (AitemDATE[5] == false && StarPiece >= 8) {
			AitemDATE[5] = true;
			StarPiece += -8;
		}
	}
}
