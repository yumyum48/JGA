#pragma once

void StageSelect();
void SelectDisp();
void SpeedSelect();

extern int g_game_stage;		//�X�e�[�W���Z���N�g
extern int g_speedLevel;		//�X�N���[�����x�̑I��

enum { // �X�N���[�����x
	SPEED_EASY = 8,
	SPEED_NORMAL = 10,
	SPEED_HARD = 13,
};