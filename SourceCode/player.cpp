#include "all.h"

int     player_state;

int     Xpos;

OBJ2D   player;

Sprite* sprPlayer;

//--------------------------------------
//  �v���C���[�̏����ݒ�
//--------------------------------------
void player_init()
{
    player_state = 0;
    Xpos = 100;
}

//--------------------------------------
//  �v���C���[�̏I������
//--------------------------------------
void player_deinit()
{
    safe_delete(sprPlayer);
}

//--------------------------------------
//  �v���C���[�̍X�V����
//--------------------------------------
void player_update()
{
    switch (player_state)
    {
    case 0:
        //////// �����ݒ� ////////
        sprPlayer = sprite_load(L"./Data/Images/R.jpg");

        ++player_state;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

#if 8
//******************************************************************************
// TODO:08 �v���C���[�̃p�����[�^�̐ݒ�
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L��player�̏����ݒ�����Ă����܂��傤�B[�v�����g�Q��]

�菇�j
    player = {};�ƋL�q���āA�S��0�ŃN���A����
    �v���C���[�̃^�C�}�[ 0�i�ꉞ�j
    �ʒu�@�@�@           ��ʂ̒���
    �X�P�[���@           ���{
    �摜�ʒu�@           �����0, 0�Œ�i�ꉞ�j
    �摜�T�C�Y           TODO_04�Œ�`�����T�C�Y
    ��_�@�@           TODO_04�Œ�`������_
    �F�@�@�@�@           �D���ȐF�i�����Ō��߂悤�j
*/
//******************************************************************************
#endif
        //TODO_08
        player = {};
        player.timer = 0;
        player.pos = { SCREEN_W * 0.5f,SCREEN_H * 0.5f };
        player.scale = { 1.0f,1.0f };
        player.texPos = { 800,800 };
        player.pivot = {400,400};
        player.color = { 1,1,1,1 };

        player.radius = 200;
        player.offset = { 0,0 };

        ++player_state;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////
        POINT cursorPos;
        GetCursorPos(&cursorPos);  // �}�E�X�J�[�\���̈ʒu���擾

        player.pos.x = cursorPos.x;
        player.pos.y = cursorPos.y;



#

        break;
    }
}

void player_render()
{
    sprite_render(sprPlayer, (float)Xpos, 400);
}

void player_moveY()
{

}

void player_moveX()
{

}
