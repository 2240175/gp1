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
#include "scene_enemy.h"
#include "Card.h"
#include "Mausu.h"
#include "judge.h"

//------< 定数 >----------------------------------------------------------------

//------< 構造体 >---------------------------------------------------------------

//------< 画像読み込み用 >---------------------------------------------------------------
Sprite* sprB;
Sprite* sprA;
Sprite* sprC;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;


//使用禁止(選択完了)
bool Select;
bool stop;

extern bool restart;
//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;

//どうでもいいもの
int checkmouse=0;
bool onoff = false;

//ラウンド勝利敗北換算用
int winner;
int raund;
int winraund;
int lossraund;

int timer;

extern int PLAYERNUM;
extern int NPCNUM;

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

    Select = false;
    stop = false;

    for (int i = 0; i < CARD_MAX; i++) {
        //カードの初期化
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    if (restart == false) {
        StarPiece=100;
        NPCPiece=0;
        //2回目の星のかけら継続防止
        PLAYERNUM = 0;
        NPCNUM = 0;
        //ラウンドの初期化防止
        raund = 1;
        winraund = 0;
        lossraund = 0;

        //現在のラウンド
        nowraund = 0;

        //タイトルに戻るとリセット
        restart = true;
    }



    //ガジェット効果用
    //初期化のためどのカードも持ってないようにするため０
    getnum = 0;



    game_state      = 0;
    game_timer      = 0;
    Card_init();
    player_init();
    enemy_init();


    //マウスカーソル非表示
    ShowCursor(false);
}

//--------------------------------------
//  ゲームの終了処理
//--------------------------------------
void game_deinit()
{    //TODO_11
    player_deinit();

    //画像
    safe_delete(sprB);
    safe_delete(sprA);
    safe_delete(sprC);
    safe_delete(sprSel[0]);
    safe_delete(sprSel[1]);

    //カード画像
    safe_delete(sprCard1);
    //カードいろいろ
    Card_deinit();

    stop = false;

    nowraund++;

    //マウスカーソル表示
    ShowCursor(true);
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

        sprB = sprite_load(L"./Data/Images/maingame.png");
        sprA = sprite_load(L"./Data/Images/maingame2.png");
        sprC = sprite_load(L"./Data/Images/one.png");
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

        debug::setString("NPC:%d", NPCPiece);
        debug::setString("PLAYER:%d", StarPiece);


        debug::setString("RAUND:%d", raund);
        debug::setString("NOW:%d", nowraund);
        debug::setString("WIN:%d", winraund);
        debug::setString("LOSS:%d", lossraund);

        if (raund != nowraund) {
            raund = nowraund;
        }

        if (raund <= winraund) {
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece=100;
            NPCPiece=0;
            break;
        }

        if (stop == false) {
            StarPiece += PLAYERNUM;
            NPCPiece += NPCNUM;
            stop = true;
        }

        Card_update();

        player_update();

        //あたり判定
        judge();

        if (Select == false) { break; }
        else if (Select == true)
        {
            nextScene = SCENE_JUDGE;
        }



        break;
    }
    game_timer++;
    timer++;
    if (timer > 10) {
        timer = 0;
    }
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

    GameLib::clear(0.0f, 0.0f, 0.0f);

    //これは画像の位置に合ったときに反応するようにしている
    //ガジェットに置き換えて使える
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
    //sprite_render(sprCard1, 0, 350);
    //sprite_render(sprCard1, 250, 250);
    //sprite_render(sprCard1, 510, 200);
    //sprite_render(sprCard1, 765, 250);
    //sprite_render(sprCard1, 1005, 350);

    Card_render();
    player_render();    
}


