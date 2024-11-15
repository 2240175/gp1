#include "all.h"
#include "Mausu.h"

int title_state;
int title_timer;

Sprite* sprCar;

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
    font::textOut(4, "Game Programming I", VECTOR2(80, 180), VECTOR2(2.0f, 2.0f), VECTOR4(0, 1, 0.6f, 1));

    // "Push Enter Key" �_��
    if (title_timer >> 5 & 0x01)
    {
        font::textOut(1, "Push Click", VECTOR2(120, 560), VECTOR2(1.4f, 1.4f));
    }

}
