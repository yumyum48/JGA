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
	DETA_PLAYTIME,
	DETA_SKILL_CUSTOM_1,
	DETA_SKILL_CUSTOM_2,
	DETA_SKILL_CUSTOM_3,
	DETA_MAX,
};
int Save(int savefile);
//int Read();
void SaveModeDisp(int saveX, int saveY[]);		// �Z�[�u�f�[�^���j���[��ʂ̕\��
int SaveData_Open(int buf[], int i);			// �Z�[�u�f�[�^��ǂݍ���ŕ\�����邽�߂ɁA�\��������e���L��������֐�
//extern char g_name;							//�f�o�b�O�p
int SaveData_CL();								// �f�o�b�O�p
