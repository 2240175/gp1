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

//------< �摜�ǂݍ��ݗp >---------------------------------------------------------------
Sprite* sprB;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;

//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;

//���̂������ǂ��ł���������
int checkmouse=0;
bool onoff = false;

//���E���h�����s�k���Z�p
int winner;
int raund;
int winraund;
int lossraund;


//�J�[�h�f�[�^
//�v���C���[�p
int numCard[5];
//�f�B�[���[�p
int npcCard[5];


//���݂̃��E���h
int nowraund;

//�K�W�F�b�g���ʗp
int getnum;

//���̂�����
int StarPiece;
int NPCPiece;

//--------------------------------------
//  �Q�[���̏����ݒ�
//--------------------------------------
void game_init()
{
    winner = DRAW;
    raund = 0;
    winraund = 0;
    lossraund = 0;

    for (int i = 0; i < CARD_MAX; i++) {
        //�J�[�h�̏�����
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    //���݂̃��E���h
    //�����͕K���O�ɂ���
    nowraund=0;

    //�K�W�F�b�g���ʗp
    //�������̂��߂ǂ̃J�[�h�������ĂȂ��悤�ɂ��邽�߂O
    getnum = 0;

    //���̂�����i�K�W�F�b�g����m�F�̂��ߍ������P�O�O�j
    //��o�O�ɕK���O�ɂ��鎖
    StarPiece = 100;
    //����p�i�K�W�F�b�g�g�p�f�B�[���[�ǉ�����ꍇ�g���j
    NPCPiece = 0;

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

    //�摜
    safe_delete(sprB);
    safe_delete(sprSel[0]);
    safe_delete(sprSel[1]);

    //�J�[�h�摜
    safe_delete(sprCard1);
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
        
        //�J�[�h�摜�ǂݍ���
        sprCard1 = sprite_load(L"./Data/Images/one.png");

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
        debug::setString("MOUCE CHECK:%d",checkmouse);

        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            if (onoff == false) {
                checkmouse++;
                onoff = true;
            }
        }
        else if (!GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            onoff = false;
        }

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

    //�̂��ɃJ�[�h��p�̊֐������
    //�����ɃJ�[�h�̃A�j���[�V����������
    //���݈ꎞ�I�ɓK���ɂ����Ă���
    sprite_render(sprCard1, 0, 350);
    sprite_render(sprCard1, 250, 250);
    sprite_render(sprCard1, 510, 200);
    sprite_render(sprCard1, 765, 250);
    sprite_render(sprCard1, 1005, 350);

    player_render();    
}
