#include "Card.h"

#define CARD_MAX (5)

OBJ2D	AnyCard[5];

Card_INFO date;

CardDate::CardDate()
//ï¿½Jï¿½[ï¿½hï¿½Ìï¿½ï¿½
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
	//ƒVƒƒƒbƒtƒ‹
	random_shuffle(begin(SterCard), end(SterCard));
}

//‚¢‚Â‚à‚Ì‰Šú‰»XV‚Ì‚â‚Â
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
