#include "all.h"
#include "Mausu.h"
#include "Card.h"

extern bool AitemDATE[7] ;
extern bool restart ;


int title_state;
int title_timer;
int clear_timer;




Sprite* sprCar;
Sprite* sprTUI;


//�}�E�X�����i���j
void mousePressed() {
    if (GetAsyncKeyState(VK_LBUTTON) & 0x8000&&title_timer>30) {
        nextScene++;
    }
}

//--------------------------------------
//  �����ݒ�
//--------------------------------------
void title_init()
{
    title_state = 0;
    title_timer = 0;
    player_init();
//<<<<<<< HEAD
//    clear_timer = 0;
//=======
//    for (int i = 0; i < MUSIC_MAX; i++) {
//        music::stop(i);
//    }
//    for (int i = 0; i < 7; i++) {
//        AitemDATE[i] = false;
//    }
//>>>>>>> 4f009ebd16182f629001db293b76020f7f696bca
    game_deinit();
    score_deinit();
    end_deinit();
    //info_deinit();
    enemy_deinit();
    //�}�E�X�J�[�\���\��
    ShowCursor(false);
}

//--------------------------------------
//  �I������
//--------------------------------------
void title_deinit()
{
    music::stop(0);

    safe_delete(sprCar);
    player_deinit();
}

//--------------------------------------
//  �^�C�g���̍X�V����
//--------------------------------------
void title_update()
{
    switch (title_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sprCar = sprite_load(L"./Data/Images/title.png");
        sprTUI = sprite_load(L"./Data/Images/titleui.png");



        title_state++;
        /*fallthrough*/

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.1f);

        title_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        if (TRG(0) & PAD_START)
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);

            nextScene = SCENE_HOME;
            break;
        }
        mousePressed();
        break;
    }

    if (title_timer > 243600) {
        music::stop(0);
        title_timer = 0;
        music::play(0);
    }
    
    player_update();

    MouseManager mouseManager;

    // �}�E�X�̍��W���X�V���A�擾����
    mouseManager.Update();
    POINT pos = mouseManager.GetPosition();

    title_timer++;
}

//--------------------------------------
//  �^�C�g���̕`�揈��
//--------------------------------------
void title_render()
{

    // ��ʂ�œh��Ԃ�
    GameLib::clear(0.3f, 0.5f, 1.0f);
    sprite_render(sprCar, 0, 0);

    // "Push Enter Key" �_��<-������摜�ɒu��������
    if ((title_timer / 32) % 2 == 0) // 32�Ŋ������l�ŏ�����ύX
    {
        sprite_render(sprTUI, 0, 0);
    }

    player_render();

}
