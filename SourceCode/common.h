#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  �V�[���̃��x��
#define SCENE_NONE      (-1)
#define SCENE_TITLE     (0)
#define SCENE_HOME      (1)
#define SCENE_GAME      (2)

#define SELECT3X  (840)//�I���P
#define SELECT3Y  (153)

#define SELECT4X  (875)//�I���Q
#define SELECT4Y  (258)

#define SELECT5X  (911)//�I���R
#define SELECT5Y  (363)

#define SELECT6X  (960)//�I���S
#define SELECT6Y  (464)

//  �萔
extern const FLOAT PI;
extern const LONG SCREEN_W;
extern const LONG SCREEN_H;
extern const BOOL FULLSCREEN;
extern const LPCWSTR APPLICATION_NAME;

//  �֐��|�C���^
extern float(* const ToRadian)(float);// �p�x�����W�A����
extern float(* const ToDegree)(float);// ���W�A�����p�x��

//  �ϐ�
extern int curScene;
extern int nextScene;

#endif // !COMMON_H
