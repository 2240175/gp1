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

//アイテムを買う時間
bool aitem_time;

extern bool restart;
//------< 変数 >----------------------------------------------------------------
int game_state;
int game_timer;

//どうでもいいもの
int checkmouse=0;
bool onoff = false;
int count_;

//ラウンド勝利敗北換算用
int winner = DRAW;
int raund;
int winraund;
int lossraund;

//現在のラウンド
int nowraund;

//最高ラウンド
int MAXRAUND;

//先に最高ラウンドに到達したやつの勝者判定
int Game_Winner;

int timer;

extern int PLAYERNUM;
extern int NPCNUM;

extern bool AitemDATE[7];

//カードデータ
//プレイヤー用
int numCard[5];
//ディーラー用
int npcCard[5];

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
    count_ = 0;
    Select = false;
    stop = false;
    aitem_time = false;

    for (int i = 0; i < CARD_MAX; i++) {
        //カードの初期化
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    if (restart == false) {
        //2回目の星のかけら継続防止
        StarPiece=100;
        NPCPiece=0;
        //カードリセット
        PLAYERNUM = 0;
        NPCNUM = 0;
        //ラウンドの初期化防止
        raund = 0;
        winraund = 0;
        lossraund = 0;
        winner = DRAW;

        //現在のラウンド
        nowraund = 1;
        //最高ラウンド
        MAXRAUND = 8;

        //タイトルに戻るとリセット
        restart = true;
    }

    Game_Winner = 0;

    //ガジェット効果用
    //初期化のためどのカードも持ってないようにするため０
    getnum = 0;

    game_state      = 0;
    game_timer      = 0;
    Card_init();
    player_init();
    enemy_init();

    Aitem_init();
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

    Aitem_deinit();
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
        sprC = sprite_load(L"./Data/Images/ui.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");
        
        //カード画像読み込み
        sprCard1 = sprite_load(L"./Data/Images/Card/one.png");

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
        debug::setString("StarPiece:%d", StarPiece);

        debug::setString("");

        debug::setString("RAUND:%d", raund);
        debug::setString("NOW:%d", nowraund);
        debug::setString("");
        debug::setString("WIN:%d", winraund);
        debug::setString("LOSS:%d", lossraund);

        if (raund != nowraund) {
            raund = nowraund;
        }

        if (raund == 1) {
            switch (winner) {
            case WIN:
                break;
            case DRAW:
                winraund = 0;
                break;
            case LOSS:
                winraund = 0;
                break;
            }
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece=0;
            NPCPiece=0;
            break;
        }

        Card_update();

        if (aitem_time == true) {
            Aitem_update();
            AitemBuy();
        }

        player_update();

        if (game_timer > 20&&aitem_time==false) {
            //あたり判定
            judge();
        }

        if (Select == false) { break; }
        else if (Select == true)
        {
            nextScene = SCENE_JUDGE;
        }


        break;
    }
    game_timer++;
    timer++;
    count_++;
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

    if (aitem_time == false) {
        sprite_render(sprA, 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, ToRadian(0),
            1, 1, 1, 1);
    }

    //これは画像の位置に合ったときに反応するようにしている
    //ガジェット購入
    sprite_render(sprB, 0, 0);

    if (aitem_time == false) {
        if (mousePos.x > 301 && mousePos.y > 544 && mousePos.x < 980 && mousePos.y < 649) {
            sprite_render(sprC, 0, 0);
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                aitem_time = true;
            }
        }
    }


    Card_render();

    if (aitem_time == true) {
        Aitem_render();
    }
    player_render();

}


