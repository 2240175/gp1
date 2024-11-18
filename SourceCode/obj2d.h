#ifndef OBJ2D_H
#define OBJ2D_H

#include "../GameLib/vector.h"
#include "../GameLib/game_lib.h"


//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//定数
#define     SCREEN_LIMIT    (256)

//------< 構造体 >--------------------------------------------------------------
class OBJ2D
{
public:
    //これはあまり使わないでほしい
    //ここから
    typedef void (__cdecl*FUNC_PTR)(OBJ2D*);
    FUNC_PTR            moveAlg;    // 移動アルゴリズム

    //カードの数字（あとなんかに使う）
    int                 num;
    //ここまで

    int                 timer;
    
    //アニメ―ション、表示位置大きさ
    //ご自由に
    GameLib::Sprite* spr;
    int     state;
    VECTOR2             pos;
    VECTOR2             scale;
    VECTOR2             texPos;
    VECTOR2             texSize;
    VECTOR2             pivot;
    VECTOR4             color;
    VECTOR2             speed;
  



    //円の当たり判定
    //カード限定
    float               radius;
    VECTOR2             offset;
};

//OBJ2D* searchSet0(OBJ2D[], int, OBJ2D::FUNC_PTR, VECTOR2);
OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos);
OBJ2D* searchSet(OBJ2D*, OBJ2D*, OBJ2D::FUNC_PTR, VECTOR2);
void sprite_render(OBJ2D*);

#endif//OBJ2D_H