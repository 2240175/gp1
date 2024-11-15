#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  シーンのラベル
#define SCENE_NONE      (-1)
#define SCENE_TITLE     (0)
#define SCENE_HOME      (1)
#define SCENE_GAME      (2)

#define SELECT3X  (840)//選択１
#define SELECT3Y  (153)

#define SELECT4X  (875)//選択２
#define SELECT4Y  (258)

#define SELECT5X  (911)//選択３
#define SELECT5Y  (363)

#define SELECT6X  (960)//選択４
#define SELECT6Y  (464)

//  定数
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;

//  関数ポインタ
extern float(* const ToRadian)(float);// 角度をラジアンに
extern float(* const ToDegree)(float);// ラジアンを角度に

//  変数
extern int curScene;
extern int nextScene;

#endif // !COMMON_H
