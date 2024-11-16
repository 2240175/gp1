#pragma once

#include "all.h"
#include "obj2d.h"
#include <algorithm>
using namespace std;

class Card_INFO {
    Sprite* spr;
    const wchar_t* filePath;
    VECTOR2         texPos;
    VECTOR2         texSize;
    VECTOR2         pivot;
    float           offset;
    float           radius;
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
