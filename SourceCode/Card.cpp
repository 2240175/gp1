#include "Card.h"

float card_timer;
float card_time;
int card_state;
int card_num[5];


OBJ2D AnyCard[CARD_MAX] = {};

//カードの情報
Card_INFO cardInfo[] = {
	{ NULL,L"./Data/Images/one.png",{ 0, 0 }, { 127, 127 }, { 255,  255 }, 10, 20},//1のカード
	{ NULL,L"./Data/Images/two.png",{ 0, 0 }, { 127, 127 }, { 255,  255 }, 10, 20},//2のカード
	{ NULL,L"./Data/Images/one.png",{ 0, 0 }, { 127, 127 }, { 255,  255 }, 10, 20},//3のカード
	{ NULL,L"./Data/Images/one.png",{ 0, 0 }, { 127, 127 }, { 255,  255 }, 10, 20},//4のカード
	{ NULL,L"./Data/Images/one.png",{ 0, 0 }, { 127, 127 }, { 255,  255 }, 10, 20},//5のカード
};

//カードの配置
//今は雑に配置
//アニメーションするとき注意
Card_SET	cardSet[]=
{
	{0,{200,300}},
	{0,{400,100}},
	{0,{600,500}},
	{0,{800,100}},
	{0,{1000,300}},
};

CardDate::CardDate()
{
}

CardDate::~CardDate()
{
}

void CardDate::CardShuffle()
{
	for (int i = 0; i < 5; i++) {
		SterCard[i] = i++;
	}
	//シャッフル
	random_shuffle(begin(SterCard), end(SterCard));
}


//いつもの初期化更新のやつ
void Card_init()
{
	card_state = 0;
	card_timer = 0;
}


//カードの終了処理
void Card_deinit()
{
	int dateNum = ARRAYSIZE(cardInfo);
	for (int i = 0; i < dateNum; ++i) {
		safe_delete(cardInfo[i].spr);
	}
}

//カードの更新
void Card_update()
{
	switch (card_state) {
	case 0:
	{
		//初期設定
		//カード枚数の計算
		int dataNum = sizeof(cardInfo) / sizeof(Card_INFO);
		//画像読み込み
		for (int i = 0; i < dataNum; ++i) {
			cardInfo[i].spr = sprite_load(cardInfo[i].filePath);
		}

		++card_state;
		/*fallthrough*/
	}

	case 1:
		//パラメーターの設定
		//カードデータのクリア
		for (int i = 0; i < CARD_MAX; ++i) {
			AnyCard[i] = {};
		}

		//カードの出現
		for (int i = 0; i < CARD_MAX; ++i) {
			if (cardSet[i].cardType >= 0) {
				OBJ2D* p = searchSet0(
					AnyCard, CARD_MAX,
					cardInfo[cardSet[i].cardType].moveAlg,
					cardSet[i].pos
				);
			}
		}
		card_timer++;
		++card_state;
		/*fallthrough*/

	case 2:
		//通常時
		for (int i = 0; i < CARD_MAX; ++i) {
			//カードの動き
			if (AnyCard[i].moveAlg == moveCard1) {
				moveCard1(&AnyCard[i]);
			}
			else if (AnyCard[i].moveAlg == moveCard2) {
				moveCard2(&AnyCard[i]);
			}
			else if (AnyCard[i].moveAlg == moveCard3) {
				moveCard3(&AnyCard[i]);
			}
			else if (AnyCard[i].moveAlg == moveCard4) {
				moveCard4(&AnyCard[i]);
			}
			else if (AnyCard[i].moveAlg == moveCard5) {
				moveCard5(&AnyCard[i]);
			}
			AnyCard[i].timer++;
		}
		debug::setString("Card_timer:%f", card_timer);
		break;
	}
	card_timer++;
	card_time++;
}

void Card_render()
{
	for (int i = 0; i < CARD_MAX; ++i) {
		if (!AnyCard[i].moveAlg)		continue;

		sprite_render(
			AnyCard[i].spr,
			AnyCard[i].pos.x, AnyCard[i].pos.y,
			AnyCard[i].scale.x, AnyCard[i].scale.y,
			AnyCard[i].texPos.x, AnyCard[i].texPos.y,
			AnyCard[i].texSize.x, AnyCard[i].texSize.y,
			AnyCard[i].pivot.x, AnyCard[i].pivot.y,
			ToRadian(0),
			AnyCard[i].color.x, AnyCard[i].color.y,
			AnyCard[i].color.z, AnyCard[i].color.w
		);


		// カードのあたり領域の描画
		primitive::circle(
			AnyCard[i].pos + AnyCard[i].offset, AnyCard[i].radius,
			{ 1, 1 }, ToRadian(0),
			{ 0, 0,1, 0.0f }
		);
	}
}


//カードの動き（アニメーション）
void moveCard1(OBJ2D* obj) 
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->scale = { 1.0f,1.0f };
		obj->color = { 1,1,1,1 };
		obj->spr = cardInfo[0].spr;
		obj->texPos = cardInfo[0].texPos;
		obj->texSize = cardInfo[0].texSize;
		obj->pivot = cardInfo[0].pivot;

		obj->offset = { 0,50 };
		++obj->state;
		/*fallthrough*/
	case 1:
		//通常時
		obj->pos.y += obj->speed.y;
		break;
	}
}

void moveCard2(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->scale = { 1.0f,1.0f };
		obj->color = { 1,1,1,1 };
		obj->spr = cardInfo[1].spr;
		obj->texPos = cardInfo[1].texPos;
		obj->texSize = cardInfo[1].texSize;
		obj->pivot = cardInfo[1].pivot;

		obj->offset = { 0,50 };
		++obj->state;
		/*fallthrough*/
	case 1:
		//通常時
		obj->pos.y += obj->speed.y;
		break;
	}
}

void moveCard3(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->scale = { 1.0f,1.0f };
		obj->color = { 1,1,1,1 };
		obj->spr = cardInfo[2].spr;
		obj->texPos = cardInfo[2].texPos;
		obj->texSize = cardInfo[2].texSize;
		obj->pivot = cardInfo[2].pivot;

		obj->offset = { 0,50 };
		++obj->state;
		/*fallthrough*/
	case 1:
		//通常時
		obj->pos.y += obj->speed.y;
		break;
	}
}

void moveCard4(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->scale = { 1.0f,1.0f };
		obj->color = { 1,1,1,1 };
		obj->spr = cardInfo[3].spr;
		obj->texPos = cardInfo[3].texPos;
		obj->texSize = cardInfo[3].texSize;
		obj->pivot = cardInfo[3].pivot;

		obj->offset = { 0,50 };
		++obj->state;
		/*fallthrough*/
	case 1:
		//通常時
		obj->pos.y += obj->speed.y;
		break;
	}
}

void moveCard5(OBJ2D* obj)
{
	switch (obj->state)
	{
	case 0:
		//初期設定
		obj->scale = { 1.0f,1.0f };
		obj->color = { 1,1,1,1 };
		obj->spr = cardInfo[4].spr;
		obj->texPos = cardInfo[4].texPos;
		obj->texSize = cardInfo[4].texSize;
		obj->pivot = cardInfo[4].pivot;

		obj->offset = { 0,50 };
		++obj->state;
		/*fallthrough*/
	case 1:
		//通常時
		obj->pos.y += obj->speed.y;
		break;
	}
}