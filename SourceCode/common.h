#ifndef COMMON_H
#define COMMON_H

#include "../GameLib/game_lib.h"
using namespace GameLib;

//  �V�[���̃��x��
#define SCENE_NONE      (-1)
#define SCENE_TITLE     (0)
#define SCENE_HOME      (1)
#define SCENE_GAME      (2)
#define SCENE_JUDGE     (3)
#define SCENE_SCORE     (4)

//�I������z
#define SELECT1X  (840)//�I���P
#define SELECT1Y  (153)

#define SELECT2X  (875)//�I���Q
#define SELECT2Y  (258)

#define SELECT3X  (911)//�I���R
#define SELECT3Y  (363)

#define SELECT4X  (960)//�I���S
#define SELECT4Y  (464)


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
