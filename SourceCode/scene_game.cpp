//******************************************************************************
//
//
//      scene_game
//
//
//******************************************************************************

//----< �C���N���[�h >-----------------------------------------------------------
#include "all.h"
#include "player.h"
#include "Mausu.h"

//------< �萔 >----------------------------------------------------------------


//------< �\���� >---------------------------------------------------------------


//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;

Sprite* sprB;
Sprite* sprSel[2];
MouseManager mouseManager;
//--------------------------------------
//  �Q�[���̏����ݒ�
//--------------------------------------
void game_init()
{
    game_state      = 0;
    game_timer      = 0;
    player_init();
}

//--------------------------------------
//  �Q�[���̏I������
//--------------------------------------
void game_deinit()
{    //TODO_11
    player_deinit();

    safe_delete(sprB);

    safe_delete(sprSel[0]);
    safe_delete(sprSel[1]);
    
}

//--------------------------------------
//  �Q�[���̍X�V����
//--------------------------------------
void game_update()
{
    switch (game_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprB = sprite_load(L"./Data/Images/m.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");

        game_state++;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        game_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        debug::setString("");
        debug::setString("Left Click�FselectS");
        debug::setString("");

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            break;
        }

        player_update();

        //TODO_12


        break;
    }
    game_timer++;
}

//--------------------------------------
//  �Q�[���̕`�揈��
//--------------------------------------
void game_render()
{
    // �}�E�X�̍��W���X�V���A�擾����
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
    player_render();    
}
