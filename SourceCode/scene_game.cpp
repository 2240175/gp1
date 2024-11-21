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
#include "scene_enemy.h"
#include "Card.h"
#include "Mausu.h"
#include "judge.h"

//------< �萔 >----------------------------------------------------------------

//------< �\���� >---------------------------------------------------------------

//------< �摜�ǂݍ��ݗp >---------------------------------------------------------------
Sprite* sprB;
Sprite* sprA;
Sprite* sprC;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;


//�g�p�֎~(�I������)
bool Select;
bool stop;

//�A�C�e���𔃂�����
bool aitem_time;

extern bool restart;
//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;

//�ǂ��ł���������
int checkmouse=0;
bool onoff = false;

//���E���h�����s�k���Z�p
int winner = DRAW;
int raund;
int winraund;
int lossraund;

//���݂̃��E���h
int nowraund;

//�ō����E���h
int MAXRAUND;

//��ɍō����E���h�ɓ��B������̏��Ҕ���
int Game_Winner;

int timer;

extern int PLAYERNUM;
extern int NPCNUM;

extern bool AitemDATE[7];

//�J�[�h�f�[�^
//�v���C���[�p
int numCard[5];
//�f�B�[���[�p
int npcCard[5];

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

    Select = false;
    stop = false;
    aitem_time = false;

    for (int i = 0; i < CARD_MAX; i++) {
        //�J�[�h�̏�����
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    if (restart == false) {
        //2��ڂ̐��̂�����p���h�~
        StarPiece=100;
        NPCPiece=0;
        //�J�[�h���Z�b�g
        PLAYERNUM = 0;
        NPCNUM = 0;
        //���E���h�̏������h�~
        raund = 1;
        winraund = 0;
        lossraund = 0;


        //���݂̃��E���h
        nowraund = 1;
        //�ō����E���h
        MAXRAUND = 8;

        //�^�C�g���ɖ߂�ƃ��Z�b�g
        restart = true;
    }

    Game_Winner = 0;

    //�K�W�F�b�g���ʗp
    //�������̂��߂ǂ̃J�[�h�������ĂȂ��悤�ɂ��邽�߂O
    getnum = 0;

    game_state      = 0;
    game_timer      = 0;
    Card_init();
    player_init();
    enemy_init();

    Aitem_init();
    //�}�E�X�J�[�\����\��
    ShowCursor(false);
}

//--------------------------------------
//  �Q�[���̏I������
//--------------------------------------
void game_deinit()
{    //TODO_11
    player_deinit();

    //�摜
    safe_delete(sprB);
    safe_delete(sprA);
    safe_delete(sprC);
    safe_delete(sprSel[0]);
    safe_delete(sprSel[1]);

    //�J�[�h�摜
    safe_delete(sprCard1);
    //�J�[�h���낢��
    Card_deinit();

    stop = false;

    Aitem_deinit();
    nowraund++;

    //�}�E�X�J�[�\���\��
    ShowCursor(true);
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

        sprB = sprite_load(L"./Data/Images/maingame.png");
        sprA = sprite_load(L"./Data/Images/maingame2.png");
        sprC = sprite_load(L"./Data/Images/ui2.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");
        
        //�J�[�h�摜�ǂݍ���
        sprCard1 = sprite_load(L"./Data/Images/Card/one.png");

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

        debug::setString("NPC:%d", NPCPiece);
        debug::setString("StarPiece:%d", StarPiece);

        debug::setString("");

        debug::setString("RAUND:%d", raund);
        debug::setString("NOW:%d", nowraund);
        debug::setString("");
        debug::setString("WIN:%d", winraund);
        debug::setString("LOSS:%d", lossraund);

        if (raund != nowraund) {
            raund = nowraund;
        }



        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece=0;
            NPCPiece=0;
            break;
        }

        Card_update();

        if (aitem_time == true) {
            Aitem_update();
            AitemBuy();
        }

        player_update();

        if (game_timer > 20&&aitem_time==false) {
            //�����蔻��
            judge();
        }

        if (Select == false) { break; }
        else if (Select == true)
        {
            nextScene = SCENE_JUDGE;
        }


        break;
    }
    game_timer++;
    timer++;
    if (timer > 10) {
        timer = 0;
    }
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

    GameLib::clear(0.0f, 0.0f, 0.0f);

    sprite_render(sprA, 0, 0);

    //����͉摜�̈ʒu�ɍ������Ƃ��ɔ�������悤�ɂ��Ă���
    //�K�W�F�b�g�w��
    sprite_render(sprB, 0, 0);

    if (mousePos.x > 301 && mousePos.y > 544 && mousePos.x < 980 && mousePos.y < 649) {
        sprite_render(sprC, 0, 0);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            aitem_time = true;
        }
    }
    else {
        sprite_render(sprSel[1], 300, 100);
    }

    Card_render();

    if (aitem_time == true) {
        Aitem_render();
    }
    player_render();

}


