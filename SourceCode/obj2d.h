#ifndef OBJ2D_H
#define OBJ2D_H

#include "../GameLib/vector.h"

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< �\���� >--------------------------------------------------------------
class OBJ2D
{
public:

    //����͂��܂�g��Ȃ��łق���
    //�J�[�h�̐����i���ƂȂ񂩂Ɏg���j
    int num;

    int timer;
    
    //�A�j���\�V�����A�\���ʒu�傫��
    //�����R��
    VECTOR2 pos;
    VECTOR2 scale;
    VECTOR2 texPos;
    VECTOR2 texSize;
    VECTOR2 pivot;
    VECTOR4 color;
    VECTOR2 speed;
    
    //�~�̓����蔻��
    //�J�[�h����
    float   radius;
    VECTOR2 offset;
};

#endif//OBJ2D_H