#include "all.h"
#include "player.h"
#include "Mausu.h"
#include "Info.h"

int home_state;
int home_timer;
int game_mode;

bool restart;
extern bool rule_date;
extern int rule_state;

Sprite* sprBack;
//Sprite* sprSelect1;//�I���P
//Sprite* sprSelect2;//�I���Q
//Sprite* sprSelect3;//�I���R
//Sprite* sprSelect4;//�I���S

MouseManager mouseHome;

//�w�i�̃X�P�[��
float select1X, select1Y;//�I���P
float select2X, select2Y;//�I���Q
float select3X, select3Y;//�I���R
float select4X, select4Y;//�I���S

extern bool rule_time;

extern int rule_pos_x;
extern int rule_pos_y;

bool hitPointAndBlock(POINT pos, float left, float top, float right, float bottom)
{
    if (pos.x > left && pos.x < right)
    {
        if (pos.y > top && pos.y < bottom)
        {

            return true;

        }

    }
    return false;
}

void home_init()
{
    home_state = 0;
    home_timer = 0;
    restart = false;
    player_init();
    info_init();
}

void home_deinit()
{    //TODO_11
    player_deinit();
    info_deinit();

    music::stop(1);

    safe_delete(sprBack);

    //safe_delete(sprSelect1);
    //safe_delete(sprSelect2);
    //safe_delete(sprSelect3);
    //safe_delete(sprSelect4);
}

void home_update()
{
    switch (home_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprBack = sprite_load(L"./Data/Images/home.png");
        //sprSelect1 = sprite_load(L"./Data/Images/kari.png");
        //sprSelect2 = sprite_load(L"./Data/Images/kari.png");
        //sprSelect3 = sprite_load(L"./Data/Images/kari.png");
        //sprSelect4 = sprite_load(L"./Data/Images/kari.png");
        music::play(1);
        //TODO_10
        home_state++;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        home_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        //debug::setString("");
        //debug::setString("Left Click�FselectS");
        //debug::setString("");

        if (TRG(0) & PAD_SELECT)
        {
            nextScene = SCENE_GAME;
            break;
        }

        player_update();

        POINT point = mouseHome.GetPosition();                                            // �ʒu�p�̕ϐ���錾����
        GetCursorPos(&point);                                   // �X�N���[�����W���擾����
        ScreenToClient(window::getHwnd(), &point);

        if (home_timer > 324060) {
            music::stop(1);
            home_timer = 0;
            music::play(1);
        }

        //�������̉�ʂɈڂ�̂�h�~���邽�߁A����𐔕b�i��0.3�b�j���������Ă���
        //���̂��߈�u��ʂɕ\������Ȃ�(�ǋL�@�v�Z�̂��߉��f�ނ̉摜�̓R�����g�A�E�g���܂���)
        /*if (home_timer > 20) {

            if (hitPointAndBlock(point, SELECT1X - 200, SELECT1Y - 35, SELECT1X + 200, SELECT1Y + 35))
            {
                select1X = select1Y = 1.3f;
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 8;
                    nextScene = SCENE_GAME;
                }

            }
            else
            {
                select1X = select1Y = 1.0f;
            }

            if (hitPointAndBlock(point, SELECT2X - 200, SELECT2Y - 35, SELECT2X + 200, SELECT2Y + 35))
            {
                select2X = select2Y = 1.3f;
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 12;
                    nextScene = SCENE_GAME;
                }
            }
            else
            {
                select2X = select2Y = 1.0f;

            }

            if (hitPointAndBlock(point, SELECT3X - 200, SELECT3Y - 35, SELECT3X + 200, SELECT3Y + 35))
            {
                select3X = select3Y = 1.3f;
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 20;
                    nextScene = SCENE_GAME;
                }
            }
            else
            {
                select3X = select3Y = 1.0f;

            }

            if (hitPointAndBlock(point, SELECT4X - 200, SELECT4Y - 35, SELECT4X + 200, SELECT4Y + 35))
            {
                select4X = select4Y = 1.3f;
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 30;
                    nextScene = SCENE_GAME;
                }
            }
            else
            {
                select4X = select4Y = 1.0f;

            }

            break;

        }*/

        if (rule_date == true) {
            rule_pos_x = point.x;
            rule_pos_y = point.y;
        }
        if (home_timer > 20 && rule_time == false) {
            if (point.x > 648 && point.y > 136 && point.x < 1128 && point.y < 220) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 8;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 696 && point.y > 282 && point.x < 1179 && point.y < 365) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 12;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 741 && point.y > 422 && point.x < 1226 && point.y < 506) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    game_mode = 20;
                    nextScene = SCENE_GAME;
                }
            }
            else if (point.x > 782 && point.y > 564 && point.x < 1265 && point.y < 646) {
                if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
                    rule_time = true;
                    rule_date = true;
                }
            }
        }
    }

    if (rule_time == true) {
        info_update();
    }
    else if (rule_time == false) {
        rule_state = 0;
    }

    home_timer++;
}

void home_render()
{
    // �}�E�X�̍��W���X�V���A�擾����
    mouseHome.Update();
    POINT pos = mouseHome.GetPosition();

    //debug::setString("X:%d", pos.x);
    //debug::setString("Y:%d", pos.y);

    GameLib::clear(0.2f, 0.2f, 0.4f);

    sprite_render(sprBack, 0, 0);


    /*if (pos.x > 600 && pos.y > 400 && pos.x < 700 && pos.y < 427) {
        sprite_render(sprSelect[0], 600, 400);
        if (GetAsyncKeyState(VK_LBUTTON) & 0x8000) {
            nextScene=SCENE_GAME;
        }
    }
    else {
        sprite_render(sprSelect[1], 600, 400);
    }*/

    if (rule_time == true) {
        info_render();
    }
    //sprite_render(sprSelect1, // �X�v���C�g�|�C���^ �I���P
    //    SELECT1X, SELECT1Y,
    //    select1X, select1Y,
    //    0, 0,
    //    400, 70,
    //    200, 35,
    //    0,
    //    1, 1, 1, 1


    //);

    //sprite_render(sprSelect2, // �X�v���C�g�|�C���^�@�I���Q
    //    SELECT2X, SELECT2Y,
    //    select2X, select2Y,
    //    0, 0,
    //    400, 70,
    //    200, 35,
    //    0,
    //    1, 1, 1, 1


    //);

    //sprite_render(sprSelect3, // �X�v���C�g�|�C���^�@�I��3
    //    SELECT3X, SELECT3Y,
    //    select3X, select3Y,
    //    0, 0,
    //    400, 70,
    //    200, 35,
    //    0,
    //    1, 1, 1, 1


    //);

    //sprite_render(sprSelect4, // �X�v���C�g�|�C���^�@�I��4
    //    SELECT4X, SELECT4Y,
    //    select4X, select4Y,
    //    0, 0,
    //    400, 70,
    //    200, 35,
    //    0,
    //    1, 1, 1, 1


    //);

    player_render();
}