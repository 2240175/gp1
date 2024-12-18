#ifndef ALL_H
#define ALL_H

//******************************************************************************
//
//
//      all.h
//
//
//******************************************************************************

// システムやライブラリのヘッダーファイルは上の方へ
#include "../GameLib/game_lib.h"

// 共通で使われるようなヘッダー
#include "common.h"

// 個々のヘッダーファイルは下の方へ
#include "audio.h"
#include "obj2d.h"
#include "Aitem.h"

#include "scene_title.h"
#include "scene_game.h"
#include "scene_home.h"
#include "scene_enemy.h"
#include "scene_judge.h"
#include "scene_score.h"
#include "end.h"

// namespace
using namespace GameLib;
using namespace input;


#endif//ALL_H
