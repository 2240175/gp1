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
Sprite* sprUra;
Sprite* sprB;
Sprite* sprA;
Sprite* sprC;
Sprite* sprK;
Sprite* sprSel[2];
MouseManager mouseManager;

Sprite* sprCard1;


//�g�p�֎~(�I������)
bool Select;
bool stop;

//�}�b�`�|�C���g
bool matchpoint;


//�A�C�e���𔃂�����
bool aitem_time;

extern bool restart;
//------< �ϐ� >----------------------------------------------------------------
int game_state;
int game_timer;

//�ǂ��ł���������
int checkmouse=0;
bool onoff = false;
int count_;

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
extern int NPCLAST;
extern int game_mode;
extern bool UseCard[5];
extern bool npc[5];

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

bool OverPlay;


//--------------------------------------
//  �Q�[���̏����ݒ�
//--------------------------------------
void game_init()
{
    count_ = 0;
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
        StarPiece=1000;
        NPCPiece=0;
        //�J�[�h���Z�b�g
        PLAYERNUM = -1;
        NPCNUM = 0;
        //���E���h�̏������h�~
        raund = 1;
        winraund = 10;
        lossraund = 10;
        winner = DRAW;

        //���݂̃��E���h
        nowraund = 1;
        //�ō����E���h
        MAXRAUND = game_mode;
        //�}�b�`�|�C���g�֘A
        OverPlay = false;
        matchpoint = false;

        //����̃J�[�h����
        NPCLAST = 5;
        if (MAXRAUND <= 12 && matchpoint == false) {
            music::play(2, true);
        }
        else if (MAXRAUND > 12 && matchpoint == false) {
            music::play(3, true);
        }

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
    safe_delete(sprUra);
    safe_delete(sprB);
    safe_delete(sprA);
    safe_delete(sprC);
    safe_delete(sprK);
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

        sprUra = sprite_load(L"./Data/Images/Card/ura.png");

        switch (MAXRAUND) {
        case 8:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame8.png");     break;
        case 12:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame12.png");    break;
        case 20:
            sprB = sprite_load(L"./Data/Images/scene_game/maingame20.png");    break;
        }
        sprA = sprite_load(L"./Data/Images/round.png");
        sprC = sprite_load(L"./Data/Images/ui.png");
        sprK = sprite_load(L"./Data/Images/Card/ura.png");
        sprSel[0] = sprite_load(L"./Data/Images/select1.png");
        sprSel[1] = sprite_load(L"./Data/Images/select2.png");

        if ((winraund - MAXRAUND) == -1&&OverPlay==false) {
            music::stop(2);
            music::stop(3);
            music::play(4, true);
            OverPlay = true;
        }
        else if ((lossraund - MAXRAUND) == -1 && OverPlay == false) {
            music::stop(2);
            music::stop(3);
            music::play(4, true);
            OverPlay = true;
        }

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
            //�}�b�`�|�C���g���y
        music::setVolume(4,0.1f);
        music::setVolume(2,0.5f);
        music::setVolume(3,0.5f);

        if (raund != nowraund) {
            raund = nowraund;
        }

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_TITLE;
            StarPiece = 0;
            NPCPiece = 0;
            break;
        }

        if ((raund - 1) % 5 == 0) {
            for (int i = 0; i < 5; i++) {
                UseCard[i] = false;
                npc[i] = false;
            }
            NPCLAST = 5;
        }

        Card_update();

        if (aitem_time == true) {
            Aitem_update();
            AitemBuy();
        }

        player_update();

        if (game_timer > 20 && aitem_time == false) {
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
    count_++;
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



    GameLib::clear(0.0f, 0.0f, 0.0f);

    if (aitem_time == false) {
        sprite_render(sprB, 0, 0, 1, 1, 0, 0, 1280, 720, 0, 0, ToRadian(0),
            1, 1, 1, 1);
    }



    //����͉摜�̈ʒu�ɍ������Ƃ��ɔ�������悤�ɂ��Ă���
    //�K�W�F�b�g�w��
    sprite_render(sprB, 0, 0);

    if (aitem_time == false&& game_timer > 20) {
        if (mousePos.x > 301 && mousePos.y > 544 && mousePos.x < 980 && mousePos.y < 649) {
            sprite_render(sprC, 0, 0);
            if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                aitem_time = true;
            }
        }
    }


    Card_render();
    switch (int card = 0) {
    case 0:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 21.5f, 268.5f);
        }
        card++;
    case 1:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 257.5f, 105.5f);
        }
        card++;
    case 2:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 512.5f, 223.5f);
        }
        card++;
    case 3:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 768.5f, 105.5f);
        }
        card++;
    case 4:
        if (UseCard[card] == true) {
            sprite_render(sprUra, 1005.5f, 267.5f);
        }
        break;
    }

    if (aitem_time == true) {
        Aitem_render();
    }

    sprite_render(sprA, 0, 0);


    sprite_render(sprK, 1210, 80, 0.25f, 0.25f, 0, 0, 255, 255, 0, 0, ToRadian(0));
    std::to_string(NPCLAST);
    font::textOut(
        1,
        std::to_string(NPCLAST),
        VECTOR2(1220, 95),
        VECTOR2(1.2f, 1.2f),
        VECTOR4(1.0f, 0.9f, 0.9f, 1)
    );

    std::to_string(StarPiece);
    std::to_string(raund);
    std::to_string(lossraund);
    std::to_string(winraund);

    //���̂�����
    if (StarPiece < 10) {
        font::textOut(
            1,
            std::to_string(StarPiece),
            VECTOR2(50, 85),
            VECTOR2(1.0f, 1.0f),
            VECTOR4(1.0f, 0.9f, 0.9f, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(StarPiece),
            VECTOR2(50, 85),
            VECTOR2(1.0f, 1.0f),
            VECTOR4(1.0f, 0.9f, 0.9f, 1)
        );
    }

    //���݂̃��E���h
    if (raund < 10) {
        font::textOut(
            1,
            std::to_string(raund),
            VECTOR2(619, 60),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(raund),
            VECTOR2(600, 70),
            VECTOR2(1.3f, 1.3f),
            VECTOR4(1, 1, 1, 1)
        );
    }

    //�������E���h
    if (winraund < 10) {
        font::textOut(
            1,
            std::to_string(winraund),
            VECTOR2(125, 15),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(winraund), 
            VECTOR2(111, 25),
            VECTOR2(1.1f, 1.1f),
            VECTOR4(1, 1, 1, 1)
        );
    }

    //�������E���h
    if (lossraund < 10) {
        font::textOut(
            1,
            std::to_string(lossraund),
            VECTOR2(1108, 15),
            VECTOR2(1.6f, 1.6f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    else {
        font::textOut(
            1,
            std::to_string(lossraund),
            VECTOR2(1095, 25),
            VECTOR2(1.1f, 1.1f),
            VECTOR4(1, 1, 1, 1)
        );
    }
    player_render();

}


