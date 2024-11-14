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

Sprite* sprBack;
Sprite* sprSelect[2];
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

    safe_delete(sprBack);

    safe_delete(sprSelect[0]);
    safe_delete(sprSelect[1]);
    
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

        sprBack = sprite_load(L"./Data/Images/m.png");
        sprSelect[0] = sprite_load(L"./Data/Images/select1.png");
        sprSelect[1] = sprite_load(L"./Data/Images/select2.png");


#if 10
//******************************************************************************
// TODO:10 �v���C���[�̏����ݒ�֐����Ăяo��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player_init�֐����Ăт܂��傤�B

����j
    ��������Aplayer�֘A�̊֐����Ăяo���Ă����܂��B�ǂ��ŉ��̊֐����Ăяo����
    ����̂���c�����Ă����܂��傤�B
*/
//******************************************************************************
#endif
        //TODO_10
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

#if 12
//******************************************************************************
// TODO:12 �v���C���[�̍X�V�֐����Ăяo��
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player_update�֐����Ăт܂��傤�B
*/
//******************************************************************************
#endif
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
    POINT pos = mouseManager.GetPosition();

    debug::setString("X:%d", pos.x);
    debug::setString("Y:%d", pos.y);

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprBack, 0, 0);
    if (pos.x > 300 && pos.y > 100 && pos.x < 400 && pos.y < 127) {
        sprite_render(sprSelect[0], 300, 100);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            nextScene--;
        }
    }
    else {
        sprite_render(sprSelect[1], 300, 100);
    }
    player_render();    
}
