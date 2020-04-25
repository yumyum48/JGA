#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"

int LoadPicture() {

	// �v���C���[�摜�̓ǂݍ���
	if (LoadDivGraph("image/player2.png", 56, 8, 7, 280, 200, g_pic.player, 0) == -1) return -1;
	// �G�l�~�[�摜�̓ǂݍ���
	if ((g_pic.enemy = LoadGraph("image/enemy.png")) == -1) return -1;

	/*//�}�b�v�̓ǂݍ���
	if (LoadDivGraph("image/mori8sute.png", 24, 3, 8, 1024, 768, g_pic.map, 0) == -1)
		return -1;*/

	// �}�b�v�ǂݍ���
	if (LoadDivGraph("image/Stage1_main.png", 4, 4, 1, 250, 400, g_pic.map, 0) == -1)
		return -1;
	// �}�b�v�w�i�ǂݍ���
	if ((g_pic.backMap = LoadGraph("image/Stage1_Back.png")) == -1) return -1;
	
	/*
	if (LoadDivGraph("images/Cnt2.png", 10, 10, 1, 57, 80, g_NumImage, 0) == -1)
		return -1;*/

	// �J�̉摜�̓ǂݍ���
	if ((g_pic.rain[0] = LoadGraph("image/RainLarge.png")) == -1) return -1;
	// �J�̉摜�̓ǂݍ���
	if ((g_pic.rain[1] = LoadGraph("image/RainLarge.png")) == -1) return -1;

	// ���e�B�N���摜�̓ǂݍ���
	if ((g_pic.reticle = LoadGraph("image/Reticle.png")) == -1) return -1;
	return 0;
}