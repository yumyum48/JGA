#pragma once

void StageSelect();				// �X�e�[�W�̃Z���N�g����
void SelectDisp();				// �X�e�[�W�̃Z���N�g�̕\������
void SelectMove();				// �X�e�[�W�̃Z���N�g�̓����̏���
void SpeedSelect();				// �X�e�[�W�̃Z���N�g�̓����̏���
void SelectInit();				// �Z���N�g��ʂ̏�����
void MenuSelectOper();			// ���j���[�ꗗ�̃J�[�\�����ړ�������
void SaveSelectOper();			// �Z�[�u���j���[�̃J�[�\�����ړ�������
void MenuScrollOut();			// ���j���[��ʂ���ʒ[�t�߂ɑ��삳����
void StageSelectOper();			// �X�e�[�W�̌���̂��߂̃J�[�\���𑀍삳����
void MenuScrollIn();			// ���j���[��ʂ�������悤�ɉ�ʒ����t�߂܂ňړ�������
void MenuSelect();				// ���j���[��ʂŌ�����������ƂŃZ�[�u��ʁA�X�L���J�X�^�}�C�Y��ʁA�^�C�g����ʂֈړ��ł���悤�ɂ���
bool SaveMenu_MenuScrollOut(bool saveFlg);		// ���j���[��ʂ���ʊO�܂ŃX�N���[���A�E�g�����A������������Z�[�u��ʂ�\��������t���O���I���ɂ���
void SaveMenu_ScrollIn();		// �Z�[�u��ʂ���ʒ����t�߂܂œ�����
void SaveMenu_Save();			// �I�����ꂽ�t�@�C���ɃZ�[�u�����s����
extern int g_select_Stage;		//�X�e�[�W���Z���N�g
extern int g_speedLevel;		//�X�N���[�����x�̑I��
extern int g_select_MAX;			// ���v���C���[��������X�e�[�W�𐧌䂷��(���̐�����0�Ȃ�1�X�e�[�W���w���Ă��܂��B(�Y�������ꂵ�Ă܂��B))
extern bool g_stageClearFlg[MAP_MAX];		// �N���A�����X�e�[�W��g_select_MAX�����Z���Ȃ��悤�ɐ��䂷��t���O

enum { // �X�N���[�����x
	SPEED_EASY = 10,
	SPEED_NORMAL = 12,
	SPEED_HARD = 15,
};