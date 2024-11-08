#include "all.h"
#include<string>

int zatsudan_state;
int zatsudan_timer;

Sprite* sproshina;

//--------------------------------------
//  �����ݒ�
//--------------------------------------
void zatsudan_init()
{
    zatsudan_state = 0;
}

//--------------------------------------
//  �I������
//--------------------------------------
void zatsudan_deinit()
{
    music::stop(0);

    safe_delete(sproshina);
}

//--------------------------------------
//  �^�C�g���̍X�V����
//--------------------------------------
void zatsudan_update()
{
    switch (zatsudan_state)
    {
    case 0:
        //////// �����ݒ� ////////

        sproshina = sprite_load(L"./Data/Images/plays.png");


        zatsudan_state++;
        

    case 1:
        //////// �p�����[�^�̐ݒ� ////////

        GameLib::setBlendMode(Blender::BS_ALPHA);

        music::play(0);
        music::setVolume(0, 0.1f);

        zatsudan_state++;
        /*fallthrough*/

    case 2:
        //////// �ʏ펞 ////////

        if (TRG(0) & PAD_TRG1)//�X�y�[�X�L�[�Ŕ���
        {
            sound::play(XWB_SYSTEM, XWB_SYSTEM_START);



            nextScene = SCENE_SETUMEI1;
            break;
        }



        break;
    }


}

//--------------------------------------
//  �^�C�g���̕`�揈��
//--------------------------------------
void zatsu_render()
{
    sprite_render(spr, 0, 0);

}