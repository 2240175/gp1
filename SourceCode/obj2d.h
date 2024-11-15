#ifndef OBJ2D_H
#define OBJ2D_H

#include "../GameLib/vector.h"

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< 構造体 >--------------------------------------------------------------
class OBJ2D
{
public:

    //これはあまり使わないでほしい
    //カードの数字（あとなんかに使う）
    int num;

    int timer;
    
    //アニメ―ション、表示位置大きさ
    //ご自由に
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 texPos;
    VECTOR2 texSize;
    VECTOR2 pivot;
    VECTOR4 color;
    VECTOR2 speed;
    
    //円の当たり判定
    //カード限定
    float   radius;
    VECTOR2 offset;
};

#endif//OBJ2D_H