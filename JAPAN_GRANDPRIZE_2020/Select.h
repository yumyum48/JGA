#pragma once

void StageSelect();				// �X�e�[�W�̃Z���N�g����
void SelectDisp();				// �X�e�[�W�̃Z���N�g�̕\������
void SpeedSelect();				// �X�e�[�W�̃Z���N�g�̓����̏���

extern int g_game_stage;		//�X�e�[�W���Z���N�g
extern int g_speedLevel;		//�X�N���[�����x�̑I��

enum { // �X�N���[�����x
	SPEED_EASY = 10,
	SPEED_NORMAL = 12,
	SPEED_HARD = 15,
};