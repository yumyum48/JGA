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
// ファイル名とフォルダ
//fp[SAVE_1] = fopen("SaveData/SaveFile_1.bin", "wb");
//fp[SAVE_2] = fopen("SaveData/SaveFile_2.bin", "wb");
//fp[SAVE_3] = fopen("SaveData/SaveFile_3.bin", "wb");
/***************************************************************

* グローバル変数の宣言

****************************************************************/
int g_savefile;	// 今選択しているファイル

/***************************************************************

* 関数の定義

****************************************************************/
//void SaveMode() {
//	SaveModeMove();
//	SaveModeDisp();
//}
void SaveModeDisp(int saveX, int saveY[]) {
	int  buf[SAVE_MAX][DETA_MAX];	// セーブすべきデータを保存する変数
	
	int no_FileFlg[3] = { 0, 0, 0 };
	// ファイルを読み取って、情報をbufに保存
	for (int i = 0; i < SAVE_MAX; i++) {
		if (SaveData_Open(buf[i], i) == 1) {	// もし保存ファイルが存在していないなら
			// ファイルが存在していませんをここで表示
			no_FileFlg[i] = 1;
		}
	}
	for (int i = 0; i < SAVE_MAX; i++) {
		SetFontSize(30);
		if (no_FileFlg[i] == 0) {
			DrawFormatString(saveX, saveY[i], 0x000000, "クリアしたステージ数: %d\nプレイタイム: %d秒\n", buf[i][0], buf[i][1]);
		}
		else {
			DrawFormatString(saveX, saveY[i] + 50, 0x000000, "フォルダが存在していません");
		}
	}
	//// デバッグ用で保存しているデータを表示
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	for (int j = 0; j < DETA_MAX; j++) {
	//		DrawFormatString(200 * (j + 1), 200 * (i + 1), 0x00FF00, "%d", buf[i][j]);
	//	}
	//}
	
}

void SaveModeMove() {
	// セーブ画面操作
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
	FILE* fp = 0;	// ファイルポインタを用意
	//int  buf[DETA_MAX];	// セーブすべきデータを保存する変数

	//buf[DETA_MAPSELECT] = g_select_MAX;			// 今の段階でいけるマップを保存
	//buf[DETA_SKILL_MAX] = g_player.skill_MAX;		// 今の段階で使えるスキルを保存
	//buf[DETA_PLAYTIME] = g_playTime;				// 今のプレイタイムを保存

#pragma warning(disable:4996)
	switch (i) {	// i番目を見て、開くべきファイルを判断
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
			printf("ファイルをオープンできませんでした。\n");
			return 1;
		}
	}

	//// 書き込み
	//for (int i = 0; i < DETA_MAX; i++) {
	//	fwrite(&buf[i], sizeof(int), 1, fp[SAVE_1]);
	//}

	//読み込み
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
	int  buf[DETA_MAX];	// セーブすべきデータを保存する変数
	FILE* fp = 0;
	
	buf[DETA_MAPSELECT] = g_select_MAX;			// 今の段階でいけるマップを保存
	buf[DETA_PLAYTIME] = g_playTime;				// 今のプレイタイムを保存
	buf[DETA_SKILL_CUSTOM_1] = g_player.skillcustom[0];		// 現在装備しているスキル１
	buf[DETA_SKILL_CUSTOM_2] = g_player.skillcustom[1];		// 現在装備しているスキル２
	buf[DETA_SKILL_CUSTOM_3] = g_player.skillcustom[2];		// 現在装備しているスキル３

	switch (savefile)
	{
	case 0:
		fp = fopen("SaveData/SaveFile_1.bin", "wb");	// ファイルオープン
		break;

	case 1:
		fp = fopen("SaveData/SaveFile_2.bin", "wb");	// ファイルオープン
		break;

	case 2:
		fp = fopen("SaveData/SaveFile_3.bin", "wb");	// ファイルオープン
		break;
	}

	// 書き込み
	for (int i = 0; i < DETA_MAX; i++) {
		fwrite(&buf[i], sizeof(int), 1, fp);
	}

	fclose(fp);			//ファイルクローズ

	return 0;

}

//int Read(void){
//	FILE* fp = 0;
//#pragma warning(disable:4996)
//
//	switch (g_savefile)
//	{
//	case 1:
//		fp = fopen("Save/SaveFile1.txt", "r");	//ファイルオープン
//		break;
//
//	case 2:
//		fp = fopen("Save/SaveFile2.txt", "r");	//ファイルオープン
//		break;
//
//	case 3:
//		fp = fopen("Save/SaveFile3.txt", "r");	//ファイルオープン
//		break;
//	}
//
//	fp = fopen("Save/SaveFile1.txt", "r");	//ファイルオープン
//
//	//fscanf(fp, "%9d %10s %10d\n", &g_stagelock(仮）, g_name, &g_score);
//
//	fclose(fp);			//ファイルクローズ
//
//	return 0;
//}
//
//void NameDebug() {
//	DrawString(150, 270, "名前を英字で入力してください", 0x000000);
//
//	// 名前の入力
//	DrawString(150, 310, "> ", 0xFFFFFF);
//	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
//	if (KeyInputSingleCharString(170, 310, 10, &g_name, FALSE) == 1) {
//		g_gameScene = GAME_SELECT;
//	}
//
//}
//
//
// フォルダを作成したり、見たりと、デバッグ用の関数
int SaveData_CL() {
	int  buf[SAVE_MAX][DETA_MAX];	// セーブすべきデータを保存する変数
	FILE* fp[SAVE_MAX];
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	buf[i][DETA_MAPSELECT] = 10;			// 今の段階でいけるマップを保存
	//	buf[i][DETA_PLAYTIME] = 20;				// 今のプレイタイムを保存
	//	buf[i][DETA_SKILL_CUSTOM_1] = 30;		// 現在装備しているスキル１
	//	buf[i][DETA_SKILL_CUSTOM_2] = 40;		// 現在装備しているスキル２
	//	buf[i][DETA_SKILL_CUSTOM_3] = 50;		// 現在装備しているスキル３
	//}
#pragma warning(disable:4996)
	fp[SAVE_1] = fopen("SaveData/SaveFile_1.bin", "rb");
	fp[SAVE_2] = fopen("SaveData/SaveFile_2.bin", "rb");
	fp[SAVE_3] = fopen("SaveData/SaveFile_3.bin", "rb");

	for (int i = 0; i < SAVE_MAX; i++) {
		if (fp[i] == NULL) {
			printf("ファイルをオープンできませんでした。\n");
			return 1;
		}
	}

	//// 書き込み
	//for (int i = 0; i < SAVE_MAX; i++) {
	//	for (int j = 0; j < DETA_MAX; j++) {
	//		fwrite(&buf[i][j], sizeof(int), 1, fp[i]);
	//	}
	//}

	//読み込み
	for (int i = 0; i < SAVE_MAX; i++) {
		for (int j = 0; j < DETA_MAX; j++) {
			fread(&buf[i][j], sizeof(int), 1, fp[i]);
		}
	}
	// デバッグ用で保存しているデータを表示
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