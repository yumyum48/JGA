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
void SaveModeDisp() {
	int  buf[SAVE_MAX][DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�
	int save_MenuX = g_mouseInfo.mouseX;
	int save_MenuY[3] = { g_mouseInfo.mouseY, g_mouseInfo.mouseY, g_mouseInfo.mouseY };
	// �Z�[�u��ʂ̔w�i�̕\��
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, TRUE);
	// �t�@�C����ǂݎ���āA����buf�ɕۑ�
	for (int i = 0; i < SAVE_MAX; i++) {
		if (SaveData_Open(buf[i]) == 1) {	// �����ۑ��t�@�C�������݂��Ă��Ȃ��Ȃ�
			// �t�@�C�������݂��Ă��܂���������ŕ\��
		}
	}

	// �f�o�b�O�p�ŕۑ����Ă���f�[�^��\��
	for (int j = 0; j < SAVE_MAX; j++) {
		for (int i = 0; i < DETA_MAX; i++) {
			DrawFormatString(200 * (i + 1), 200 * (j + 1), 0x00FF00, "%d", buf[j][i]);
		}
	}
	//DrawBox(save_MenuX, save_MenuY, save_MenuX +  )
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
//

int SaveData_Open(int buf[]) {
	FILE* fp[SAVE_MAX];
	//int  buf[DETA_MAX];	// �Z�[�u���ׂ��f�[�^��ۑ�����ϐ�

	//buf[DETA_MAPSELECT] = g_select_MAX;			// ���̒i�K�ł�����}�b�v��ۑ�
	//buf[DETA_SKILL_MAX] = g_player.skill_MAX;		// ���̒i�K�Ŏg����X�L����ۑ�
	//buf[DETA_PLAYTIME] = g_playTime;				// ���̃v���C�^�C����ۑ�

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
	//for (int i = 0; i < DETA_MAX; i++) {
	//	fwrite(&buf[i], sizeof(int), 1, fp[SAVE_1]);
	//}

	//�ǂݍ���
	for (int i = 0; i < DETA_MAX; i++) {
		fread(&buf[i], sizeof(int), 1, fp[SAVE_1]);
	}

	for (int i = 0; i < SAVE_MAX; i++) {
		fclose(fp[i]);
	}

	
	return 0;

}
//int Save(int savefile) {
//	FILE* fp = 0;
//#pragma warning(disable:4996)
//
//	//switch (savefile)
//	//{
//	//case 1:
//	//	fp = fopen("Save/SaveFile1.txt", "w");	// �t�@�C���I�[�v��
//	//	break;
//
//	//case 2:
//	//	fp = fopen("Save/SaveFile2.txt", "w");	// �t�@�C���I�[�v��
//	//	break;
//
//	//case 3:
//	//	fp = fopen("Save/SaveFile3.txt", "w");	// �t�@�C���I�[�v��
//	//	break;
//	//}
//
//	////fprintf(fp, "%9d %10s %10d\n", &g_stagelock(���j, g_name, g_score);
//
//	//fclose(fp);			//�t�@�C���N���[�Y
//
//	return 0;
//
//}

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
