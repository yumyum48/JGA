#include "DxLib.h"
#include "Save.h"
#include "GameScene.h"
#include "control.h"
#include "Macro.h"
#include <iostream>
#include <fstream>
#include "Player.h"
#include <stdio.h>
#include "GamePlay.h"
#include "Select.h"
// �t�@�C�����ƃt�H���_
//fp[SAVE_1] = fopen("SaveData/SaveFile_1.bin", "wb");
//fp[SAVE_2] = fopen("SaveData/SaveFile_2.bin", "wb");
//fp[SAVE_3] = fopen("SaveData/SaveFile_3.bin", "wb");
/***************************************************************

* �O���[�o���ϐ��̐錾

****************************************************************/
int g_savefile;	// ���I�����Ă���t�@�C��

/***************************************************************

* �֐��̒�`

****************************************************************/
//void SaveMode() {
//	SaveModeMove();
//	SaveModeDisp();
//}
void SaveModeDisp(int saveX, int saveY[]) {
	int  buf[SAVE_MAX][DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�
	
	int no_FileFlg[3] = { 0, 0, 0 };
	// �t�@�C����ǂݎ���āA����buf�ɕۑ�
	for (int i = 0; i < SAVE_MAX; i++) {
		if (SaveData_Open(buf[i], i) == 1) {	// �����ۑ��t�@�C�������݂��Ă��Ȃ��Ȃ�
			// �t�@�C�������݂��Ă��܂���������ŕ\��
			no_FileFlg[i] = 1;
		}
	}
	for (int i = 0; i < SAVE_MAX; i++) {
		SetFontSize(30);
		if (no_FileFlg[i] == 0) {
			DrawFormatString(saveX, saveY[i], 0x000000, "�N���A�����X�e�[�W��: %d\n�v���C�^�C��: %d�b\n", buf[i][0], buf[i][1]);
		}
		else {
			DrawFormatString(saveX, saveY[i] + 50, 0x000000, "�t�H���_�����݂��Ă��܂���");
		}
	}
	//// �f�o�b�O�p�ŕۑ����Ă���f�[�^��\��
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	for (int j = 0; j < DETA_MAX; j++) {
	//		DrawFormatString(200 * (j + 1), 200 * (i + 1), 0x00FF00, "%d", buf[i][j]);
	//	}
	//}
	
}

void SaveModeMove() {
	// �Z�[�u��ʑ���
	{
		
		if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
			if (++g_savefile > 2) g_savefile = 0;
		}

		if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
			if (--g_savefile < 0) g_savefile = 2;
		}

		//Save(g_savefile);
	}
}


int SaveData_Open(int buf[], int i) {
	FILE* fp = 0;	// �t�@�C���|�C���^��p��
	//int  buf[DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�

	//buf[DETA_MAPSELECT] = g_select_MAX;			// ���̒i�K�ł�����}�b�v��ۑ�
	//buf[DETA_SKILL_MAX] = g_player.skill_MAX;		// ���̒i�K�Ŏg����X�L����ۑ�
	//buf[DETA_PLAYTIME] = g_playTime;				// ���̃v���C�^�C����ۑ�

#pragma warning(disable:4996)
	switch (i) {	// i�Ԗڂ����āA�J���ׂ��t�@�C���𔻒f
	case 0:
		fp = fopen("SaveData/SaveFile_1.bin", "rb");
		break;

	case 1:
		fp = fopen("SaveData/SaveFile_2.bin", "rb");
		break;

	case 2:
		fp = fopen("SaveData/SaveFile_3.bin", "rb");
		break;

	default:
		break;
	}
	
	
	

	for (int i = 0; i < SAVE_MAX; i++) {
		if (fp == NULL) {
			printf("�t�@�C�����I�[�v���ł��܂���ł����B\n");
			return 1;
		}
	}

	//// ��������
	//for (int i = 0; i < DETA_MAX; i++) {
	//	fwrite(&buf[i], sizeof(int), 1, fp[SAVE_1]);
	//}

	//�ǂݍ���
	for (int i = 0; i < DETA_MAX; i++) {
		fread(&buf[i], sizeof(int), 1, fp);
	}

	for (int i = 0; i < SAVE_MAX; i++) {
		fclose(fp);
	}

	
	return 0;

}

int Save(int savefile) {
#pragma warning(disable:4996)
	int  buf[DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�
	FILE* fp = 0;
	
	buf[DETA_MAPSELECT] = g_select_MAX;			// ���̒i�K�ł�����}�b�v��ۑ�
	buf[DETA_PLAYTIME] = g_playTime;				// ���̃v���C�^�C����ۑ�
	buf[DETA_SKILL_CUSTOM_1] = g_player.skillcustom[0];		// ���ݑ������Ă���X�L���P
	buf[DETA_SKILL_CUSTOM_2] = g_player.skillcustom[1];		// ���ݑ������Ă���X�L���Q
	buf[DETA_SKILL_CUSTOM_3] = g_player.skillcustom[2];		// ���ݑ������Ă���X�L���R

	switch (savefile)
	{
	case 0:
		fp = fopen("SaveData/SaveFile_1.bin", "wb");	// �t�@�C���I�[�v��
		break;

	case 1:
		fp = fopen("SaveData/SaveFile_2.bin", "wb");	// �t�@�C���I�[�v��
		break;

	case 2:
		fp = fopen("SaveData/SaveFile_3.bin", "wb");	// �t�@�C���I�[�v��
		break;
	}

	// ��������
	for (int i = 0; i < DETA_MAX; i++) {
		fwrite(&buf[i], sizeof(int), 1, fp);
	}

	fclose(fp);			//�t�@�C���N���[�Y

	return 0;

}

//int Read(void){
//	FILE* fp = 0;
//#pragma warning(disable:4996)
//
//	switch (g_savefile)
//	{
//	case 1:
//		fp = fopen("Save/SaveFile1.txt", "r");	//�t�@�C���I�[�v��
//		break;
//
//	case 2:
//		fp = fopen("Save/SaveFile2.txt", "r");	//�t�@�C���I�[�v��
//		break;
//
//	case 3:
//		fp = fopen("Save/SaveFile3.txt", "r");	//�t�@�C���I�[�v��
//		break;
//	}
//
//	fp = fopen("Save/SaveFile1.txt", "r");	//�t�@�C���I�[�v��
//
//	//fscanf(fp, "%9d %10s %10d\n", &g_stagelock(���j, g_name, &g_score);
//
//	fclose(fp);			//�t�@�C���N���[�Y
//
//	return 0;
//}
//
//void NameDebug() {
//	DrawString(150, 270, "���O���p���œ��͂��Ă�������", 0x000000);
//
//	// ���O�̓���
//	DrawString(150, 310, "> ", 0xFFFFFF);
//	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, &g_name, FALSE) == 1) {
//		g_gameScene = GAME_SELECT;
//	}
//
//}
//
//
// �t�H���_���쐬������A������ƁA�f�o�b�O�p�̊֐�
int SaveData_CL() {
	int  buf[SAVE_MAX][DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�
	FILE* fp[SAVE_MAX];
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	buf[i][DETA_MAPSELECT] = 10;			// ���̒i�K�ł�����}�b�v��ۑ�
	//	buf[i][DETA_PLAYTIME] = 20;				// ���̃v���C�^�C����ۑ�
	//	buf[i][DETA_SKILL_CUSTOM_1] = 30;		// ���ݑ������Ă���X�L���P
	//	buf[i][DETA_SKILL_CUSTOM_2] = 40;		// ���ݑ������Ă���X�L���Q
	//	buf[i][DETA_SKILL_CUSTOM_3] = 50;		// ���ݑ������Ă���X�L���R
	//}
#pragma warning(disable:4996)
	fp[SAVE_1] = fopen("SaveData/SaveFile_1.bin", "rb");
	fp[SAVE_2] = fopen("SaveData/SaveFile_2.bin", "rb");
	fp[SAVE_3] = fopen("SaveData/SaveFile_3.bin", "rb");

	for (int i = 0; i < SAVE_MAX; i++) {
		if (fp[i] == NULL) {
			printf("�t�@�C�����I�[�v���ł��܂���ł����B\n");
			return 1;
		}
	}

	//// ��������
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	for (int j = 0; j < DETA_MAX; j++) {
	//		fwrite(&buf[i][j], sizeof(int), 1, fp[i]);
	//	}
	//}

	//�ǂݍ���
	for (int i = 0; i < SAVE_MAX; i++) {
		for (int j = 0; j < DETA_MAX; j++) {
			fread(&buf[i][j], sizeof(int), 1, fp[i]);
		}
	}
	// �f�o�b�O�p�ŕۑ����Ă���f�[�^��\��
	for (int i = 0; i < SAVE_MAX; i++) {
		for (int j = 0; j < DETA_MAX; j++) {
			DrawFormatString(200 * (j + 1), 200 * (i + 1), 0x00FF00, "%d", buf[i][j]);
		}
	}
	for (int i = 0; i < SAVE_MAX; i++) {
		fclose(fp[i]);
	}


	return 0;

}