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

extern bool restart;
//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;

//�ǂ��ł���������
int checkmouse=0;
bool onoff = false;

//���E���h�����s�k���Z�p
int winner;
int raund;
int winraund;
int lossraund;

int timer;

extern int PLAYERNUM;
extern int NPCNUM;

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

    Select = false;
    stop = false;

    for (int i = 0; i < CARD_MAX; i++) {
        //�J�[�h�̏�����
        numCard[i] = i+1;
        npcCard[i] = i+1;
    }

    if (restart == false) {
        StarPiece=100;
        NPCPiece=0;
        //2��ڂ̐��̂�����p���h�~
        PLAYERNUM = 0;
        NPCNUM = 0;
        //���E���h�̏������h�~
        raund = 1;
        winraund = 0;
        lossraund = 0;

        //���݂̃��E���h
        nowraund = 0;

        //�^�C�g���ɖ߂�ƃ��Z�b�g
        restart = true;
    }



    //�K�W�F�b�g���ʗp
    //�������̂��߂ǂ̃J�[�h�������ĂȂ��悤�ɂ��邽�߂O
    getnum = 0;



    game_state      = 0;
    game_timer      = 0;
    Card_init();
    player_init();
    enemy_init();


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
        sprC = sprite_load(L"./Data/Images/one.png");
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

        debug::setString("NPC:%d", NPCPiece);
        debug::setString("PLAYER:%d", StarPiece);


        debug::setString("RAUND:%d", raund);
        debug::setString("NOW:%d", nowraund);
        debug::setString("WIN:%d", winraund);
        debug::setString("LOSS:%d", lossraund);

        if (raund != nowraund) {
            raund = nowraund;
        }

        if (raund <= winraund) {
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece=100;
            NPCPiece=0;
            break;
        }

        if (stop == false) {
            StarPiece += PLAYERNUM;
            NPCPiece += NPCNUM;
            stop = true;
        }

        Card_update();

        player_update();

        //�����蔻��
        judge();

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

    //����͉摜�̈ʒu�ɍ������Ƃ��ɔ�������悤�ɂ��Ă���
    //�K�W�F�b�g�ɒu�������Ďg����
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
    //sprite_render(sprCard1, 0, 350);
    //sprite_render(sprCard1, 250, 250);
    //sprite_render(sprCard1, 510, 200);
    //sprite_render(sprCard1, 765, 250);
    //sprite_render(sprCard1, 1005, 350);

    Card_render();
    player_render();    
}


