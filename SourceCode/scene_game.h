#ifndef SCENE_GAME_H
#define SCENE_GAME_H

//******************************************************************************
//
//
//      scene_game.h
//
//
//******************************************************************************

//難易度選択用（現段階未使用）
#define NOMAL	(8)
#define YUUSYA	(12)
#define HARD	(20)

//勝敗判定
#define DRAW	(0)
#define WIN		(1)
#define LOSS	(2)

//最大・最小カード枚数（最小は未使用）
#define CARD_MAX	(5)
#define CARD_MIN	(1)



// 関数のプロトタイプ宣言
void game_init();
void game_deinit();
void game_update();
void game_render();

#endif//SCENE_GAME_H
