#ifndef SCENE_GAME_H
#define SCENE_GAME_H

//******************************************************************************
//
//
//      scene_game.h
//
//
//******************************************************************************

//��Փx�I��p�i���i�K���g�p�j
#define NOMAL	(8)
#define YUUSYA	(12)
#define HARD	(20)

//���s����
#define DRAW	(0)
#define WIN		(1)
#define LOSS	(2)

//�ő�E�ŏ��J�[�h�����i�ŏ��͖��g�p�j
#define CARD_MAX	(5)
#define CARD_MIN	(1)



// �֐��̃v���g�^�C�v�錾
void game_init();
void game_deinit();
void game_update();
void game_render();

#endif//SCENE_GAME_H
