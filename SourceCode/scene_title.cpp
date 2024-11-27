#include "all.h"
#include "Mausu.h"
#include "Card.h"

extern bool AitemDATE[7] ;


int title_state;
int title_timer;
int clear_timer;




Sprite* sprCar;
Sprite* sprTUI;


//マウス処理（仮）
void mousePressed() {
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&&title_timer>30) {
        nextScene++;
    }
}

//--------------------------------------
//  初期設定
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
//<<<<<<< HEAD
//    clear_timer = 0;
//=======
//    for (int i = 0; i < MUSIC_MAX; i++) {
//        music::stop(i);
//    }
//    for (int i = 0; i < 7; i++) {
//        AitemDATE[i] = false;
//    }
//>>>>>>> 4f009ebd16182f629001db293b76020f7f696bca
}

//--------------------------------------
//  終了処理
//--------------------------------------
void title_deinit()
{
    music::stop(0);

    safe_delete(sprCar);
}

//--------------------------------------
//  タイトルの更新処理
//--------------------------------------
void title_update()
{
    switch (title_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprCar = sprite_load(L"./Data/Images/title.png");
        sprTUI = sprite_load(L"./Data/Images/titleui.png");



        title_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.1f);

        title_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        if (TRG(0) & PAD_START)
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);

            nextScene = SCENE_HOME;
            break;
        }
        mousePressed();
        break;
    }

    if (title_timer > 243600) {
        music::stop(0);
        title_timer = 0;
        music::play(0);
    }
    
    debug::setString("");
    debug::setString("title_state:%d", title_state);
    debug::setString("title_timer:%d", title_timer);

    MouseManager mouseManager;

    // マウスの座標を更新し、取得する
    mouseManager.Update();
    POINT pos = mouseManager.GetPosition();
    
    debug::setString("X:%d", pos.x);
    debug::setString("Y:%d", pos.y);

    title_timer++;
}

//--------------------------------------
//  タイトルの描画処理
//--------------------------------------
void title_render()
{

    // 画面を青で塗りつぶす
    GameLib::clear(0.3f, 0.5f, 1.0f);
    sprite_render(sprCar, 0, 0);

    // タイトルの文字
    font::textOut(6, "Bet And Get", VECTOR2(100, 80), VECTOR2(2.4f, 2.4f), VECTOR4(1, 0.8f, 0, 1));
    font::textOut(1, "1234", VECTOR2(80, 180), VECTOR2(2.0f, 2.0f), VECTOR4(1, 1, 1, 1));

    // "Push Enter Key" 点滅<-これを画像に置き換える
    if ((title_timer / 32) % 2 == 0) // 32で割った値で条件を変更
    {
        sprite_render(sprTUI, 0, 0);
    }

}
