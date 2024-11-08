#include "all.h"
#include<string>

int zatsudan_state;
int zatsudan_timer;

Sprite* sproshina;

//--------------------------------------
//  初期設定
//--------------------------------------
void zatsudan_init()
{
    zatsudan_state = 0;
}

//--------------------------------------
//  終了処理
//--------------------------------------
void zatsudan_deinit()
{
    music::stop(0);

    safe_delete(sproshina);
}

//--------------------------------------
//  タイトルの更新処理
//--------------------------------------
void zatsudan_update()
{
    switch (zatsudan_state)
    {
    case 0:
        //////// 初期設定 ////////

        sproshina = sprite_load(L"./Data/Images/plays.png");


        zatsudan_state++;
        

    case 1:
        //////// パラメータの設定 ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.1f);

        zatsudan_state++;
        /*fallthrough*/

    case 2:
        //////// 通常時 ////////

        if (TRG(0) & PAD_TRG1)//スペースキーで反応
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);



            nextScene = SCENE_SETUMEI1;
            break;
        }



        break;
    }


}

//--------------------------------------
//  タイトルの描画処理
//--------------------------------------
void zatsu_render()
{
    sprite_render(spr, 0, 0);

}