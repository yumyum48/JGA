#pragma once

//void NameDebug(); //�f�o�b�O�p


enum {	// �Z�[�u�f�[�^�t�@�C��
	SAVE_1,
	SAVE_2,
	SAVE_3,
	SAVE_MAX,
};


enum {	// �ۑ�����f�[�^�̓Y����
	DETA_MAPSELECT,
	DETA_SKILL_MAX,
	DETA_PLAYTIME,
	DETA_MAX,
};
//int Save();
//int Read();
void SaveModeDisp();					// �Z�[�u�f�[�^���j���[��ʂ̕\��
int SaveData_Open(int buf[]);			// �Z�[�u�f�[�^��ǂݍ���ŕ\�����邽�߂ɁA�\��������e���L��������֐�
//extern char g_name;					//�f�o�b�O�p
