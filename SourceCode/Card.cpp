#include "Card.h"

#define CARD_MAX (5)

OBJ2D	AnyCard[5];

Card_INFO date;

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
	//�V���b�t��
	random_shuffle(begin(SterCard), end(SterCard));
}

//�����̏������X�V�̂��
void Card_init()
{
}

void Card_deinit()
{
}

void Card_update()
{
}

void Card_render()
{
}
