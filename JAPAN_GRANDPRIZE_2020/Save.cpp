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
void SaveModeDisp() {
	int  buf[SAVE_MAX][DETA_MAX];	// セーブすべきデータを保存する変数
	int save_MenuX = g_mouseInfo.mouseX;
	int save_MenuY[3] = { g_mouseInfo.mouseY, g_mouseInfo.mouseY, g_mouseInfo.mouseY };
	// セーブ画面の背景の表示
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, TRUE);
	// ファイルを読み取って、情報をbufに保存
	for (int i = 0; i < SAVE_MAX; i++) {
		if (SaveData_Open(buf[i]) == 1) {	// もし保存ファイルが存在していないなら
			// ファイルが存在していませんをここで表示
		}
	}

	// デバッグ用で保存しているデータを表示
	for (int j = 0; j < SAVE_MAX; j++) {
		for (int i = 0; i < DETA_MAX; i++) {
			DrawFormatString(200 * (i + 1), 200 * (j + 1), 0x00FF00, "%d", buf[j][i]);
		}
	}
	//DrawBox(save_MenuX, save_MenuY, save_MenuX +  )
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
//

int SaveData_Open(int buf[]) {
	FILE* fp[SAVE_MAX];
	//int  buf[DETA_MAX];	// セーブすべきデータを保存する変数

	//buf[DETA_MAPSELECT] = g_select_MAX;			// 今の段階でいけるマップを保存
	//buf[DETA_SKILL_MAX] = g_player.skill_MAX;		// 今の段階で使えるスキルを保存
	//buf[DETA_PLAYTIME] = g_playTime;				// 今のプレイタイムを保存

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
	//for (int i = 0; i < DETA_MAX; i++) {
	//	fwrite(&buf[i], sizeof(int), 1, fp[SAVE_1]);
	//}

	//読み込み
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
//	//	fp = fopen("Save/SaveFile1.txt", "w");	// ファイルオープン
//	//	break;
//
//	//case 2:
//	//	fp = fopen("Save/SaveFile2.txt", "w");	// ファイルオープン
//	//	break;
//
//	//case 3:
//	//	fp = fopen("Save/SaveFile3.txt", "w");	// ファイルオープン
//	//	break;
//	//}
//
//	////fprintf(fp, "%9d %10s %10d\n", &g_stagelock(仮）, g_name, g_score);
//
//	//fclose(fp);			//ファイルクローズ
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
