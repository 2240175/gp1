#include "all.h"
#include "Mausu.h"

int title_state;
int title_timer;
int clear_timer;

bool next_state = false; //���Z�b�g������������


float velocity1 = 0.0f;//�������x
float accelerator1 = -0.3f;//���������x
int posX1 = 640;
int posY1 = 1000;//���P�̍��W
int star_state1 = 0;//��Ԃ��Ǘ�
bool star1_active = false;


float velocity2 = 0.0f;//�������x
float accelerator2 = -0.4f;//���������x
int posX2 = 370;
int posY2 = 1000;//���Q
int star_state2 = 0;//��Ԃ��Ǘ�
bool star2_active = false;

float velocity3 = 0.0f;//�������x
float accelerator3 = -0.4f;//���������x
int posX3 = 910;
int posY3 = 1000;//���R
int star_state3 = 0;//��Ԃ��Ǘ�
bool star3_active = false;

float velocity4 = 0.0f;//�������x
float accelerator4 = -0.4f;//���������x
int posX4 = 100;
int posY4 = 1000;//���R
int star_state4 = 0;//��Ԃ��Ǘ�
bool star4_active = false;

float velocity5 = 0.0f;//�������x
float accelerator5 = -0.4f;//���������x
int posX5 = 1180;
int posY5 = 1000;//���R
int star_state5 = 0;//��Ԃ��Ǘ�
bool star5_active = false;


Sprite* sprCar;
Sprite* sprStar1;
Sprite* sprStar2;
Sprite* sprStar3;
Sprite* sprStar4;
Sprite* sprStar5;


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
    clear_timer = 0;
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
    font::textOut(1, "1234", VECTOR2(80, 180), VECTOR2(2.0f, 2.0f), VECTOR4(1, 1, 1, 1));

    // "Push Enter Key" �_��
    if (title_timer >> 5 & 0x01)
    {
        font::textOut(1, "Push Click", VECTOR2(120, 560), VECTOR2(1.4f, 1.4f));
    }

}
