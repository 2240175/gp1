#pragma once

#include "all.h"
#include "obj2d.h"
#include <algorithm>
using namespace std;


#define CARD_MAX (5)


//カードの情報
class Card_INFO {
public:
    Sprite*         spr;
    const wchar_t*  filePath;
    VECTOR2         texPos;
    VECTOR2         texSize;
    VECTOR2         pivot;
    float           offset;
    float           radius;
    OBJ2D::FUNC_PTR moveAlg;
};

//カードの配置
class Card_SET
{
public:
    int         cardType;
    VECTOR2     pos;
};


class CardDate
{
private:
    int SterCard[5] = { 1,2,3,4,5 };
public:
    CardDate();
    ~CardDate();

    void CardShuffle();
};

void Card_init();
void Card_deinit();
void Card_update();
void Card_render();

void moveCard1(OBJ2D* obj);
void moveCard2(OBJ2D* obj);
void moveCard3(OBJ2D* obj);
void moveCard4(OBJ2D* obj);
void moveCard5(OBJ2D* obj);