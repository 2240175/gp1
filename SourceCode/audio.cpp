#include "all.h"

//--------------------------------------
//  オーディオの初期設定
//--------------------------------------
void audio_init()
{
    // 音楽の読み込み
    music::load(0, L"./Data/Musics/title.wav");
    music::load(1, L"./Data/Musics/home.wav");
    music::load(2, L"./Data/Musics/main.wav");
    music::load(3, L"./Data/Musics/sub.wav");
    music::load(4, L"./Data/Musics/matchpoint.wav");
    music::load(5, L"./Data/Musics/ed.wav");

    sound::load(XWB_SYSTEM, L"./Data/Sounds/system.xwb");    // メニューなどのSE
    sound::load(XWB_STAGE1, L"./Data/Sounds/stage1.xwb");    // ステージ用のSE

    sound::setVolume(XWB_STAGE1, XWB_STAGE1_JUMP, 0.1f);
}

//--------------------------------------
//  オーディオの終了処理
//--------------------------------------
void audio_deinit()
{
    // 音楽を全て解放
    music::clear();
}
