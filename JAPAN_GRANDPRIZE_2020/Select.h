#pragma once

void StageSelect();				// �X�e�[�W�̃Z���N�g����
void SelectDisp();				// �X�e�[�W�̃Z���N�g�̕\������
void SelectMove();				// �X�e�[�W�̃Z���N�g�̓����̏���
void SpeedSelect();				// �X�e�[�W�̃Z���N�g�̓����̏���
void SelectInit();				// �Z���N�g��ʂ̏�����
extern int g_select_Stage;		//�X�e�[�W���Z���N�g
extern int g_speedLevel;		//�X�N���[�����x�̑I��
extern int select_MAX;			// ���v���C���[��������X�e�[�W�𐧌䂷��(���̐�����0�Ȃ�1�X�e�[�W���w���Ă��܂��B(�Y�������ꂵ�Ă܂��B))

enum { // �X�N���[�����x
	SPEED_EASY = 10,
	SPEED_NORMAL = 12,
	SPEED_HARD = 15,
};