#include "scene_game.h"
#include "judge.h"
#include "player.h"
#include "Card.h"

extern OBJ2D player;
extern OBJ2D AnyCard[CARD_MAX];

extern int PLAYERNUM;

extern bool UseCard[10];
extern bool Select;

bool isLeftButtonPressed = false; // ���{�^���������ꂽ���ǂ�����ǐՂ���t���O
bool isClickHandled = false;       // �����ꂽ�N���b�N�������ς݂��ǂ�����ǐ�

bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2)
{
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float r = r1 + r2;

	//�d�Ȃ����Ƃ�
	if (dx * dx + dy * dy <= r * r) {
		//�N���b�N���ꂽ�Ƃ�
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			// ���߂ĉ����ꂽ�Ƃ��ɂ̂ݏ���
			if (!isLeftButtonPressed) {
				//�����ꂽ���Ƃ��L�^
				isLeftButtonPressed = true; 
				 //����N���b�N���̂ݏ���
				return true;	
			}
		}
		else {
			// ���N���b�N�������ꂽ��t���O�����Z�b�g
			isLeftButtonPressed = false;
		}
	}

	return false;
}


//  OBJ2D���m�̂����蔻��
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2)
{
	return hitCheckCircle(
		obj1->pos, obj1->radius,
		obj2->pos, obj2->radius
	);
}

//  �����蔻��
void judge()
{
	// �v���C���[�ƃJ�[�h�̂����蔻��
	for (int i = 0; i < CARD_MAX; ++i)
	{
		if (!AnyCard[i].moveAlg)              continue;
		if (hitCheck(&player, &AnyCard[i]))
		{
			//UseCard[i] = true;
			PLAYERNUM = i + 1;
			Select = true;
		}
	}
}