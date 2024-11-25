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
Sprite* sprUra;
Sprite* sprB;
Sprite* sprA;
Sprite* sprC;
Sprite* sprK;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;


//使用禁止(選択完了)
bool Select;
bool stop;

//マッチポイント
bool matchpoint;


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
extern int NPCLAST;
extern int game_mode;
extern bool UseCard[5];
extern bool npc[5];

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

bool OverPlay;


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
        StarPiece=1000;
        NPCPiece=0;
        //カードリセット
        PLAYERNUM = -1;
        NPCNUM = 0;
        //ラウンドの初期化防止
        raund = 1;
        winraund = 10;
        lossraund = 10;
        winner = DRAW;

        //現在のラウンド
        nowraund = 1;
        //最高ラウンド
        MAXRAUND = game_mode;
        //マッチポイント関連
        OverPlay = false;
        matchpoint = false;

        //相手のカード枚数
        NPCLAST = 5;
        if (MAXRAUND <= 12 && matchpoint == false) {
            music::play(2, true);
        }
        else if (MAXRAUND > 12 && matchpoint == false) {
            music::play(3, true);
        }

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
    safe_delete(sprUra);
    safe_delete(sprB);
    safe_delete(sprA);
    safe_delete(sprC);
    safe_delete(sprK);
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

        sprUra = sprite_load(L"./Data/Images/Card/ura.png");

        switch (MAXRAUND) {
        case 8:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame8.png");     break;
        case 12:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame12.png");    break;
        case 20:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame20.png");    break;
        }
        sprA = sprite_load(L"./Data/Images/round.png");
        sprC = sprite_load(L"./Data/Images/ui.png");
        sprK = sprite_load(L"./Data/Images/Card/ura.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");

        if ((winraund - MAXRAUND) == -1&&OverPlay==false) {
            music::stop(2);
            music::stop(3);
            music::play(4, true);
            OverPlay = true;
        }
        else if ((lossraund - MAXRAUND) == -1 && OverPlay == false) {
            music::stop(2);
            music::stop(3);
            music::play(4, true);
            OverPlay = true;
        }

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
            //マッチポイント音楽
        music::setVolume(4,0.1f);
        music::setVolume(2,0.5f);
        music::setVolume(3,0.5f);

        if (raund != nowraund) {
            raund = nowraund;
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece = 0;
            NPCPiece = 0;
            break;
        }

        if ((raund - 1) % 5 == 0) {
            for (int i = 0; i < 5; i++) {
                UseCard[i] = false;
                npc[i] = false;
            }
            NPCLAST = 5;
        }

        Card_update();

        if (aitem_time == true) {
            Aitem_update();
            AitemBuy();
        }

        player_update();

        if (game_timer > 20 && aitem_time == false) {
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



    GameLib::clear(0.0f, 0.0f, 0.0f);

    if (aitem_time == false) {
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, ToRadian(0),
            1, 1, 1, 1);
    }



    //これは画像の位置に合ったときに反応するようにしている
    //ガジェット購入
    sprite_render(sprB, 0, 0);

    if (aitem_time == false&& game_timer > 20) {
        if (mousePos.x > 301 && mousePos.y > 544 && mousePos.x < 980 && mousePos.y < 649) {
            sprite_render(sprC, 0, 0);
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                aitem_time = true;
            }
        }
    }


    Card_render();
    switch (int card = 0) {
    case 0:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 21.5f, 268.5f);
        }
        card++;
    case 1:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 257.5f, 105.5f);
        }
        card++;
    case 2:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 512.5f, 223.5f);
        }
        card++;
    case 3:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 768.5f, 105.5f);
        }
        card++;
    case 4:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 1005.5f, 267.5f);
        }
        break;
    }

    if (aitem_time == true) {
        Aitem_render();
    }

    sprite_render(sprA, 0, 0);


    sprite_render(sprK, 1210, 80, 0.25f, 0.25f, 0, 0, 255, 255, 0, 0, ToRadian(0));
    std::to_string(NPCLAST);
    font::textOut(
        1,
        std::to_string(NPCLAST),
        VECTOR2(1220, 95),
        VECTOR2(1.2f, 1.2f),
        VECTOR4(1.0f, 0.9f, 0.9f, 1)
    );

    std::to_string(StarPiece);
    std::to_string(raund);
    std::to_string(lossraund);
    std::to_string(winraund);

    //星のかけら
    if (StarPiece < 10) {
        font::textOut(
            1,
            std::to_string(StarPiece),
            VECTOR2(50, 85),
            VECTOR2(1.0f, 1.0f),
            VECTOR4(1.0f, 0.9f, 0.9f, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(StarPiece),
            VECTOR2(50, 85),
            VECTOR2(1.0f, 1.0f),
            VECTOR4(1.0f, 0.9f, 0.9f, 1)
        );
    }

    //現在のラウンド
    if (raund < 10) {
        font::textOut(
            1,
            std::to_string(raund),
            VECTOR2(619, 60),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(raund),
            VECTOR2(600, 70),
            VECTOR2(1.3f, 1.3f),
            VECTOR4(1, 1, 1, 1)
        );
    }

    //勝利ラウンド
    if (winraund < 10) {
        font::textOut(
            1,
            std::to_string(winraund),
            VECTOR2(125, 15),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(winraund), 
            VECTOR2(111, 25),
            VECTOR2(1.1f, 1.1f),
            VECTOR4(1, 1, 1, 1)
        );
    }

    //負けラウンド
    if (lossraund < 10) {
        font::textOut(
            1,
            std::to_string(lossraund),
            VECTOR2(1108, 15),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(lossraund),
            VECTOR2(1095, 25),
            VECTOR2(1.1f, 1.1f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    player_render();

}


