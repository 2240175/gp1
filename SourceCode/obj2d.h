#ifndef OBJ2D_H
#define OBJ2D_H

#include "../GameLib/vector.h"
#include "../GameLib/game_lib.h"


//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//�萔
#define     SCREEN_LIMIT    (256)

//------< �\���� >--------------------------------------------------------------
class OBJ2D
{
public:
    //����͂��܂�g��Ȃ��łق���
    //��������
    typedef void (__cdecl*FUNC_PTR)(OBJ2D*);
    FUNC_PTR            moveAlg;    // �ړ��A���S���Y��

    //�J�[�h�̐����i���ƂȂ񂩂Ɏg���j
    int                 num;
    //�����܂�

    int                 timer;
    
    //�A�j���\�V�����A�\���ʒu�傫��
    //�����R��
    GameLib::Sprite* spr;
    int     state;
    VECTOR2             pos;
    VECTOR2             scale;
    VECTOR2             texPos;
    VECTOR2             texSize;
    VECTOR2             pivot;
    VECTOR4             color;
    VECTOR2             speed;
  



    //�~�̓����蔻��
    //�J�[�h����
    float               radius;
    VECTOR2             offset;
};

//OBJ2D* searchSet0(OBJ2D[], int, OBJ2D::FUNC_PTR, VECTOR2);
OBJ2D* searchSet0(OBJ2D arr[], int dataNum, OBJ2D::FUNC_PTR moveAlg, VECTOR2 pos);
OBJ2D* searchSet(OBJ2D*, OBJ2D*, OBJ2D::FUNC_PTR, VECTOR2);
void sprite_render(OBJ2D*);

#endif//OBJ2D_H