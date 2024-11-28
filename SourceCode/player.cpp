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

        player = {};
        player.timer = 0;
        player.pos = { 0,0 };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 0,0 };
        player.texSize = { 38, 36 };
        player.pivot = { 19,18 };
        player.color = { 1,1,1,1 };

        player.radius = 12;
        player.offset = { 0,0 };

        ++player_state;
        /*fallthrough*/

    case 2:
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            sound::play(XWB_SE, XWB_SE_TAP);
        }
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
        { 0.5f, 0.0f, 1.0f, 0.0f }
    );
}
