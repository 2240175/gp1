#ifndef OBJ2D_H
#define OBJ2D_H

//******************************************************************************
//
//
//      obj2d.h
//
//
//******************************************************************************

//------< �\���� >--------------------------------------------------------------
struct OBJ2D
{
#if 2
//******************************************************************************
// TODO:02 OBJ2D���쐬
//------------------------------------------------------------------------------
/*
�ۑ�j
    �\����OBJ2D�ɕK�v�ȃ����o�ϐ���ݒ肵�܂��傤�B

�菇�j
    ���L�̃����o�ϐ���ǉ����Ȃ����B
    int�^        timer
    VECTOR2�^    pos     �i�ʒu�j
    VECTOR2�^    scale   �i�X�P�[���j
    VECTOR2�^    texPos  �i�摜�ʒu�j
    VECTOR2�^    texSize �i�摜�T�C�Y�j
    VECTOR2�^    pivot   �i��_�j
    VECTOR4�^    color   �i�F�j
*/
//******************************************************************************
#endif
    //TODO_02


#if 15
//******************************************************************************
// TODO:15 OBJ2D�ɑ��x�̃����o�ϐ���ǉ�
//------------------------------------------------------------------------------
/*
�ۑ�j
    ���L�̃����o�ϐ���ǉ����Ȃ����B

        VECTOR2�^    speed   �i���x�j

����j
    ���̃v���O�����ł́A���b60�t���[���ōX�V�����ƕ`�揈�����s���Ă��܂����A1�t���[��
    �i�܂�1/60�b�j������̈ړ��ʂ�\���܂��B
    ���t���[���A�ʒu�ipos�j�ɑ��x�ispeed�j�𑫂����Ƃňړ���\�����܂��B
*/
//******************************************************************************
#endif
    //TODO_15


    //�\���ۑ�F�W�����v�p�ϐ�

};

#endif//OBJ2D_H