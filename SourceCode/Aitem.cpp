#include "Aitem.h"

bool AitemNum[10] = { false };

Sprite* AitemPNG;
Sprite* AitemPNG2;
Sprite* AitemCard[5];
MouseManager mouse;

extern int winner;
extern int raund;
extern int lossraund;

extern int StarPiece;

extern bool aitem_time;

bool AitemDATE[7] = { false };
bool OVERBUY[7] = { false };

int money;


void Aitem_init()
{
	AitemPNG = sprite_load(L"./Data/Images/Aitem/Aitem.png");
	AitemPNG2 = sprite_load(L"./Data/Images/Aitem/Aitem2.png");
	AitemCard[0] = sprite_load(L"./Data/Images/Card/one.png");
	AitemCard[1] = sprite_load(L"./Data/Images/Card/two.png");
	AitemCard[2] = sprite_load(L"./Data/Images/Card/three.png");
	AitemCard[3] = sprite_load(L"./Data/Images/Card/four.png");
	AitemCard[4] = sprite_load(L"./Data/Images/Card/one.png");
}

void Aitem_deinit()
{
	safe_delete(AitemPNG);
	safe_delete(AitemPNG2);
	for (int i = 0; i < 5; i++) {
		safe_delete(AitemCard[i]);
	}
}

void Aitem_update()
{
	//�A�C�e���ɐG��ĉ������炻�̐��l�𑗂�
	// �}�E�X�̍��W���X�V���A�擾����
	mouse.Update();
	POINT mousePos = mouse.GetPosition();
	//�]����
	if (mousePos.x > 399 && mousePos.y > 226 && mousePos.x < 520 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&& AitemDATE[0] == false&&StarPiece>=8) {
			AitemDATE[0] = true;
		}
	}
	//�L�����f�B�[
	if (mousePos.x > 596 && mousePos.y > 226 && mousePos.x < 724 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[1] == false && StarPiece >= 8) {
			AitemDATE[1] = true;
		}
	}
	//UFO
	if (mousePos.x > 770 && mousePos.y > 226 && mousePos.x < 900 && mousePos.y < 343) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[2] == false && StarPiece >= 4) {
			AitemDATE[2] = true;
		}
	}
	//���v
	if (mousePos.x > 399 && mousePos.y > 420 && mousePos.x < 520 && mousePos.y < 480) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[3] == false && StarPiece >= 8) {
			AitemDATE[3] = true;
		}
	}

	//�x��
	if (mousePos.x > 596 && mousePos.y > 420 && mousePos.x < 724 && mousePos.y < 480) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[4] == false && StarPiece >= 8) {
			AitemDATE[4] = true;
		}
	}
	//�`�P�b�g
	if (mousePos.x > 770 && mousePos.y > 420 && mousePos.x < 900 && mousePos.y < 480) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[5] == false && StarPiece >= 3) {
			AitemDATE[5] = true;
		}
	}

	//�߂�
	if (mousePos.x > 548 && mousePos.y > 486 && mousePos.x < 767 && mousePos.y < 513) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			aitem_time = false;
		}
	}
}

void Aitem_render()
{
	sprite_render(AitemPNG2, 340, 160);
	if (AitemDATE[0] == true) {
		sprite_render(AitemCard[money], 942, 230);
	}
}

void AitemBuy()
{
	//�A�C�e������
	//�ق��̏ꏊ�Ɉړ�������
	//�]�����w��
	if (AitemDATE[0] == true && OVERBUY[0] == false) {
		StarPiece -= 8;
		money = rand() % 5;
		OVERBUY[0] = true;
		//AitemDATE[0] == false;
	}
	//�L�����f�B�[
	if (AitemDATE[1] == true && OVERBUY[1] == false) {
		StarPiece -= 8;
		OVERBUY[1] = true;
		//AitemDATE[0] == false;
	}
	//U F O
	if (AitemDATE[2] == true && OVERBUY[2] == false) {
		StarPiece -= 4;
		OVERBUY[2] = true;
		//AitemDATE[0] == false;
	}
	//���v
	if (AitemDATE[3] == true && OVERBUY[3] == false) {
		StarPiece -= 8;
		OVERBUY[3] = true;
		//AitemDATE[0] == false;
	}
	//�x��
	if (AitemDATE[4] == true && OVERBUY[4] == false) {
		StarPiece -= 8;
		OVERBUY[4] = true;
		//AitemDATE[0] == false;
	}
	//�`�P�b�g
	if (AitemDATE[5] == true && OVERBUY[5] == false) {
		StarPiece -= 3;
		OVERBUY[5] = true;
		//AitemDATE[0] == false;
	}
}
