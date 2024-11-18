#include "all.h"

int     player_state;

int     Xpos;

OBJ2D   player;

Sprite* sprPlayer;

//--------------------------------------
//  プレイヤーの初期設定
//--------------------------------------
void player_init()
{
    player_state = 0;
    Xpos = 100;
}

//--------------------------------------
//  プレイヤーの終了処理
//--------------------------------------
void player_deinit()
{
    safe_delete(sprPlayer);
}

//--------------------------------------
//  プレイヤーの更新処理
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// 初期設定 ////////
        sprPlayer = sprite_load(L"./Data/Images/R.png");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

#if 8
//******************************************************************************
// TODO:08 プレイヤーのパラメータの設定
//------------------------------------------------------------------------------
/*
課題）
    下記でplayerの初期設定をしていきましょう。[プリント参照]

手順）
    player = {};と記述して、全て0でクリアする
    プレイヤーのタイマー 0（一応）
    位置　　　           画面の中央
    スケール　           等倍
    画像位置　           今回は0, 0固定（一応）
    画像サイズ           TODO_04で定義したサイズ
    基準点　　           TODO_04で定義した基準点
    色　　　　           好きな色（自分で決めよう）
*/
//******************************************************************************
#endif
        //TODO_08
        player = {};
        player.timer = 0;
        player.pos = { 0,0 };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 0,0 };
        player.texSize = { 50, 50 };
        player.pivot = { 25,25 };
        player.color = { 1,1,1,1 };

        player.radius = 10;
        player.offset = { 0,0 };

        ++player_state;
        /*fallthrough*/

    case 2:

        break;
    }
}

void player_render()
{
    POINT cursorPos;
    GetCursorPos(&cursorPos);  // マウスカーソルの位置を取得

    player.pos.x = cursorPos.x;
    player.pos.y = cursorPos.y;

    sprite_render(
        sprPlayer,
        player.pos.x,player.pos.y,
        player.scale.x,player.scale.y,
        player.texPos.x,player.texPos.y,
        player.texSize.x,player.texSize.y,
        player.pivot.x,player.pivot.y,
        ToRadian(0),
        player.color.x,player.color.y,
        player.color.z,player.color.w
        );

    // プレイヤーのあたり領域の表示
    primitive::circle(
        player.pos,
        player.radius,
        { 1, 1 },
        ToRadian(0),
        { 0.5f, 0.0f, 1.0f, 0.5f }
    );
}
