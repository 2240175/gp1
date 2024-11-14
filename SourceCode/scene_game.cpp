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

//------< 画像読み込み用 >---------------------------------------------------------------
Sprite* sprB;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;

//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;

//ものすごくどうでもいいもの
int checkmouse=0;
bool onoff = false;

//ラウンド勝利敗北換算用
int winner;
int raund;
int winraund;
int lossraund;


//カードデータ
//プレイヤー用
int numCard[5];
//ディーラー用
int npcCard[5];


//現在のラウンド
int nowraund;

//ガジェット効果用
int getnum;

//星のかけら
int StarPiece;
int NPCPiece;

//--------------------------------------
//  ゲームの初期設定
//--------------------------------------
void game_init()
{
    winner = DRAW;
    raund = 0;
    winraund = 0;
    lossraund = 0;

    for (int i = 0; i < CARD_MAX; i++) {
        //カードの初期化
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    //現在のラウンド
    //ここは必ず０にする
    nowraund=0;

    //ガジェット効果用
    //初期化のためどのカードも持ってないようにするため０
    getnum = 0;

    //星のかけら（ガジェット動作確認のため今だけ１００）
    //提出前に必ず０にする事
    StarPiece = 100;
    //相手用（ガジェット使用ディーラー追加する場合使う）
    NPCPiece = 0;

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

    //画像
    safe_delete(sprB);
    safe_delete(sprSel[0]);
    safe_delete(sprSel[1]);

    //カード画像
    safe_delete(sprCard1);
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

        sprB = sprite_load(L"./Data/Images/m.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");
        
        //カード画像読み込み
        sprCard1 = sprite_load(L"./Data/Images/one.png");

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

        //TODO_12
        debug::setString("MOUCE CHECK:%d",checkmouse);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (onoff == false) {
                checkmouse++;
                onoff = true;
            }
        }
        else if (!GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            onoff = false;
        }

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
    POINT mousePos = mouseManager.GetPosition();

    debug::setString("X:%d", mousePos.x);
    debug::setString("Y:%d", mousePos.y);

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprB, 0, 0);
    if (mousePos.x > 300 && mousePos.y > 100 && mousePos.x < 400 && mousePos.y < 127) {
        sprite_render(sprSel[0], 300, 100);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            nextScene=SCENE_TITLE;
        }
    }
    else {
        sprite_render(sprSel[1], 300, 100);
    }

    //のちにカード専用の関数を作る
    //そこにカードのアニメーションを入れる
    //現在一時的に適当においてある
    sprite_render(sprCard1, 0, 350);
    sprite_render(sprCard1, 250, 250);
    sprite_render(sprCard1, 510, 200);
    sprite_render(sprCard1, 765, 250);
    sprite_render(sprCard1, 1005, 350);

    player_render();    
}
