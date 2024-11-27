#include "all.h"
#include "Mausu.h"
#include "Card.h"

extern bool AitemDATE[7] ;


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
}

//--------------------------------------
//  �I������
//--------------------------------------
void title_deinit()
{
    music::stop(0);

    safe_delete(sprCar);
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
    
    debug::setString("");
    debug::setString("title_state:%d", title_state);
    debug::setString("title_timer:%d", title_timer);

    MouseManager mouseManager;

    // �}�E�X�̍��W���X�V���A�擾����
    mouseManager.Update();
    POINT pos = mouseManager.GetPosition();
    
    debug::setString("X:%d", pos.x);
    debug::setString("Y:%d", pos.y);

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

    // �^�C�g���̕���
    font::textOut(6, "Bet And Get", VECTOR2(100, 80), VECTOR2(2.4f, 2.4f), VECTOR4(1, 0.8f, 0, 1));
    font::textOut(1, "1234", VECTOR2(80, 180), VECTOR2(2.0f, 2.0f), VECTOR4(1, 1, 1, 1));

    // "Push Enter Key" �_��<-������摜�ɒu��������
    if ((title_timer / 32) % 2 == 0) // 32�Ŋ������l�ŏ�����ύX
    {
        sprite_render(sprTUI, 0, 0);
    }

}
