#include "all.h"
#include "player.h"
#include "Mausu.h"
#include "Info.h"

int home_state;
int home_timer;
int game_mode;

bool restart;
extern bool rule_date;
extern int rule_state;

Sprite* sprBack;

MouseManager mouseHome;

//背景のスケール
float select1X, select1Y;//選択１
float select2X, select2Y;//選択２
float select3X, select3Y;//選択３
float select4X, select4Y;//選択４

extern bool rule_time;

extern int rule_pos_x;
extern int rule_pos_y;

bool hitPointAndBlock(POINT pos, float left, float top, float right, float bottom)
{
    if (pos.x > left && pos.x < right)
    {
        if (pos.y > top && pos.y < bottom)
        {

            return true;

        }

    }
    return false;
}

void home_init()
{
    home_state = 0;
    home_timer = 0;
    rule_time = true;
    restart = false;
    player_init();
    info_init();
}

void home_deinit()
{    //TODO_11
    player_deinit();
    info_deinit();

    music::stop(1);
    rule_time = false;

    safe_delete(sprBack);
}

void home_update()
{
    switch (home_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprBack = sprite_load(L"./Data/Images/home.png");

        music::play(1);
        home_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        home_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////


        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_GAME;
            break;
        }

        player_update();

        POINT point = mouseHome.GetPosition();                  // 位置用の変数を宣言する
        GetCursorPos(&point);                                   // スクリーン座標を取得する
        ScreenToClient(window::getHwnd(), &point);

        if (home_timer > 324060) {
            music::stop(1);
            home_timer = 0;
            music::play(1);
        }

        if (rule_date == true) {
            rule_pos_x = point.x;
            rule_pos_y = point.y;
        }
        if (home_timer > 60 && rule_time == false) {
            if (point.x > 648 && point.y > 136 && point.x < 1128 && point.y < 220) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 8;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 696 && point.y > 282 && point.x < 1179 && point.y < 365) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 12;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 741 && point.y > 422 && point.x < 1226 && point.y < 506) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 20;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 782 && point.y > 564 && point.x < 1265 && point.y < 646) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    rule_time = true;
                }
            }
        }
    }

    if (rule_time == true) {
        info_update();
    }
    else if (rule_time == false) {
        rule_state = 0;
    }

    home_timer++;
}

void home_render()
{
    // マウスの座標を更新し、取得する
    mouseHome.Update();
    POINT pos = mouseHome.GetPosition();

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprBack, 0, 0);

    if (rule_time == true) {
        info_render();
    }

    player_render();
}