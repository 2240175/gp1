//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< インクルード >-----------------------------------------------------------
#include "all.h"
#include "player.h"
#include "Mausu.h"

//------< 定数 >----------------------------------------------------------------


//------< 構造体 >---------------------------------------------------------------


//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;

Sprite* sprBack;
Sprite* sprSelect[2];
MouseManager mouseManager;
//--------------------------------------
//  ゲームの初期設定
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
    player_init();
}

//--------------------------------------
//  ゲームの終了処理
//--------------------------------------
void game_deinit()
{    //TODO_11
    player_deinit();

    safe_delete(sprBack);

    safe_delete(sprSelect[0]);
    safe_delete(sprSelect[1]);
    
}

//--------------------------------------
//  ゲームの更新処理
//--------------------------------------
void game_update()
{
    switch (game_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprBack = sprite_load(L"./Data/Images/m.png");
        sprSelect[0] = sprite_load(L"./Data/Images/select1.png");
        sprSelect[1] = sprite_load(L"./Data/Images/select2.png");


#if 10
//******************************************************************************
// TODO:10 プレイヤーの初期設定関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_init関数を呼びましょう。

解説）
    ここから、player関連の関数を呼び出していきます。どこで何の関数を呼び出して
    いるのかを把握しておきましょう。
*/
//******************************************************************************
#endif
        //TODO_10
        game_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        game_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        debug::setString("");
        debug::setString("Left Click：selectS");
        debug::setString("");

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }

        player_update();

#if 12
//******************************************************************************
// TODO:12 プレイヤーの更新関数を呼び出す
//------------------------------------------------------------------------------
/*
課題）
    下記でplayer_update関数を呼びましょう。
*/
//******************************************************************************
#endif
        //TODO_12


        break;
    }
    game_timer++;
}

//--------------------------------------
//  ゲームの描画処理
//--------------------------------------
void game_render()
{
    // マウスの座標を更新し、取得する
    mouseManager.Update();
    POINT pos = mouseManager.GetPosition();

    debug::setString("X:%d", pos.x);
    debug::setString("Y:%d", pos.y);

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprBack, 0, 0);
    if (pos.x > 300 && pos.y > 100 && pos.x < 400 && pos.y < 127) {
        sprite_render(sprSelect[0], 300, 100);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            nextScene--;
        }
    }
    else {
        sprite_render(sprSelect[1], 300, 100);
    }
    player_render();    
}
