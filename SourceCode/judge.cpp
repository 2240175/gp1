#include "scene_game.h"
#include "judge.h"
#include "player.h"
#include "Card.h"

extern OBJ2D player;
extern OBJ2D AnyCard[CARD_MAX];

extern int PLAYERNUM;

extern bool UseCard[10];
extern bool Select;

bool isLeftButtonPressed = false; // 左ボタンが押されたかどうかを追跡するフラグ
bool isClickHandled = false;       // 押されたクリックが処理済みかどうかを追跡

bool hitCheckCircle(VECTOR2 pos1, float r1, VECTOR2 pos2, float r2)
{
	float dx = pos2.x - pos1.x;
	float dy = pos2.y - pos1.y;
	float r = r1 + r2;

	//重なったとき
	if (dx * dx + dy * dy <= r * r) {
		//クリックされたとき
		if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
			// 初めて押されたときにのみ処理
			if (!isLeftButtonPressed) {
				//押されたことを記録
				isLeftButtonPressed = true; 
				 //初回クリック時のみ処理
				return true;	
			}
		}
		else {
			// 左クリックが離されたらフラグをリセット
			isLeftButtonPressed = false;
		}
	}

	return false;
}


//  OBJ2D同士のあたり判定
bool hitCheck(OBJ2D* obj1, OBJ2D* obj2)
{
	return hitCheckCircle(
		obj1->pos, obj1->radius,
		obj2->pos, obj2->radius
	);
}

//  あたり判定
void judge()
{
	// プレイヤーとカードのあたり判定
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