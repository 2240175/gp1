#include "Aitem.h"

bool AitemNum[10] = { false };

Sprite* AitemPNG;
Sprite* BLACK;

Sprite* AitemCard[5];
Sprite* AitemInfo[6];
MouseManager mouse;

int Aitem_timer;

extern int winner;
extern int raund;
extern int lossraund;

extern int StarPiece;
extern int game_timer;

extern bool aitem_time;
extern bool npc[5];

bool AitemDATE[7] = { false };
bool OVERBUY[7] = { false };

bool Info_state[6];

int money;


void Aitem_init()
{
	for (int i = 0; i < 6; i++) {
		Info_state[i] = { false };
	}

	AitemPNG = sprite_load(L"./Data/Images/Aitem/Aitem.png");

	BLACK = sprite_load(L"./Data/Images/Aitem/black.png");

	AitemCard[0] = sprite_load(L"./Data/Images/Card/one.png");
	AitemCard[1] = sprite_load(L"./Data/Images/Card/two.png");
	AitemCard[2] = sprite_load(L"./Data/Images/Card/three.png");
	AitemCard[3] = sprite_load(L"./Data/Images/Card/four.png");
	AitemCard[4] = sprite_load(L"./Data/Images/Card/five.png");

	AitemInfo[0]= sprite_load(L"./Data/Images/Aitem/telescope.png");
	AitemInfo[1]= sprite_load(L"./Data/Images/Aitem/candy.png");
	AitemInfo[2]= sprite_load(L"./Data/Images/Aitem/UFO.png");
	AitemInfo[3]= sprite_load(L"./Data/Images/Aitem/clock.png");
	AitemInfo[4]= sprite_load(L"./Data/Images/Aitem/bell.png");
	AitemInfo[5]= sprite_load(L"./Data/Images/Aitem/ticket.png");
}

void Aitem_deinit()
{
	safe_delete(AitemPNG);
	safe_delete(BLACK);
	for (int i = 0; i < 5; i++) {
		safe_delete(AitemCard[i]);
	}
	Aitem_timer = 0;
}

void Aitem_update()
{
	//�A�C�e���ɐG��ĉ������炻�̐��l�𑗂�
	// �}�E�X�̍��W���X�V���A�擾����
	mouse.Update();
	POINT mousePos = mouse.GetPosition();
	//�]����
	if (mousePos.x > 399 && mousePos.y > 196 && mousePos.x < 520 && mousePos.y < 313) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
			Info_state[0] = true;
		sprite_render(AitemInfo[0], 0, 0);
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&& AitemDATE[0] == false&&StarPiece>=8) {
			Aitem_timer = 0;
			AitemDATE[0] = true;
		}
	}
	//�L�����f�B�[
	if (mousePos.x > 596 && mousePos.y > 196 && mousePos.x < 724 && mousePos.y < 313) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
		Info_state[1] = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[1] == false && StarPiece >= 8) {
			AitemDATE[1] = true;
		}
	}
	//UFO
	if (mousePos.x > 770 && mousePos.y > 196 && mousePos.x < 900 && mousePos.y < 313) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
		Info_state[2] = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[2] == false && StarPiece >= 4) {
			AitemDATE[2] = true;
		}
	}
	//���v
	if (mousePos.x > 399 && mousePos.y > 324 && mousePos.x < 520 && mousePos.y < 450) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
		Info_state[3] = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[3] == false && StarPiece >= 8) {
			AitemDATE[3] = true;
		}
	}
	//�x��
	if (mousePos.x > 596 && mousePos.y > 324 && mousePos.x < 724 && mousePos.y < 450) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
		Info_state[4] = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[4] == false && StarPiece >= 8) {
			AitemDATE[4] = true;
		}
	}
	//�`�P�b�g
	if (mousePos.x > 770 && mousePos.y > 324 && mousePos.x < 900 && mousePos.y < 450) {
		for (int i = 0; i < 6; i++) {
			Info_state[i] = false;
		}
		Info_state[5] = true;
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000 && AitemDATE[5] == false && StarPiece >= 3) {
			AitemDATE[5] = true;
		}
	}

	//�߂�
	if (mousePos.x > 548 && mousePos.y > 456 && mousePos.x < 767 && mousePos.y < 483) {
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			aitem_time = false;
			for (int i = 0; i < 6; i++) {
				Info_state[i] = false;
				game_timer = 0;
			}
		}
	}

	Aitem_timer++;
}

void Aitem_render()
{
	sprite_render(
		BLACK,
		0, 0,
		1, 1, 
		0, 0, 
		1280, 720, 
		0, 0, 
		ToRadian(0),
		1, 1, 1, 0.6f);


	sprite_render(AitemPNG, 340, 130);
	if (AitemDATE[0] == true) {
		if (Aitem_timer < 21) {
			sprite_render(AitemCard[money], (1280-(Aitem_timer*16.0f)), 230);
		}
		else {
			sprite_render(AitemCard[money], 942, 230);
		}
	}

	//�A�C�e������
	if (Info_state[0] == true) {
		if (Aitem_timer < 50) {
			sprite_render(AitemInfo[0], 0, -(Aitem_timer*5.0f) + 500);
		}
		else {
			sprite_render(AitemInfo[0], 0, 0);
		}
	}
	if (Info_state[1] == true) {
		sprite_render(AitemInfo[1], 0, 0);
	}
	if (Info_state[2] == true) {
		sprite_render(AitemInfo[2], 0, 0);
	}
	if (Info_state[3] == true) {
		sprite_render(AitemInfo[3], 0, 0);
	}
	if (Info_state[4] == true) {
		sprite_render(AitemInfo[4], 0, 0);
	}
	if (Info_state[5] == true) {
		sprite_render(AitemInfo[5], 0, 0);
	}
}

void AitemBuy()
{
	//�A�C�e������
	//�ق��̏ꏊ�Ɉړ�������
	//�]�����w��
	if (AitemDATE[0] == true && OVERBUY[0] == false) {
		StarPiece -= 8;
		while (1) {
			money = rand() % 5;
			if (npc[money] == false) break;
		}
		npc[money] = true;
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
