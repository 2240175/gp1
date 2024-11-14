#include "all.h"
#include "player.h"
#include "Mausu.h"

int home_state;
int home_timer;

Sprite* sprBack;
Sprite* sprSelect[2];
MouseManager mouseHome;

void home_init()
{
    home_state = 0;
    home_timer = 0;
    player_init();
}

void home_deinit()
{    //TODO_11
    player_deinit();

    safe_delete(sprBack);

    safe_delete(sprSelect[0]);
    safe_delete(sprSelect[1]);
}

void home_update()
{
    switch (home_state)
    {
    case 0:
        //////// 初期設定 ////////

        sprBack = sprite_load(L"./Data/Images/m.png");
        sprSelect[0] = sprite_load(L"./Data/Images/select1.png");
        sprSelect[1] = sprite_load(L"./Data/Images/select2.png");

        //TODO_10
        home_state++;
        /*fallthrough*/

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        home_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        debug::setString("");
        debug::setString("Left Click：selectS");
        debug::setString("");

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_GAME;
            break;
        }

        player_update();

        //TODO_12


        break;
    }
    home_timer++;
}

void home_render()
{
    // マウスの座標を更新し、取得する
    mouseHome.Update();
    POINT pos = mouseHome.GetPosition();

    debug::setString("X:%d", pos.x);
    debug::setString("Y:%d", pos.y);

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprBack, 0, 0);
    if (pos.x > 600 && pos.y > 400 && pos.x < 700 && pos.y < 427) {
        sprite_render(sprSelect[0], 600, 400);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            nextScene=SCENE_GAME;
        }
    }
    else {
        sprite_render(sprSelect[1], 600, 400);
    }
    player_render();
}