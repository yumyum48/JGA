#include "DxLib.h"
#include "Save.h"
#include "GameScene.h"

int Save(void) {
	FILE* fp = 0;
#pragma warning(disable:4996)

	switch (g_savefile)
	{
	case 1:
		fp = fopen("Save/SaveFile1.txt", "w");	// ファイルオープン
		break;

	case 2:
		fp = fopen("Save/SaveFile2.txt", "w");	// ファイルオープン
		break;

	case 3:
		fp = fopen("Save/SaveFile3.txt", "w");	// ファイルオープン
		break;
	}

	//fprintf(fp, "%9d %10s %10d\n", &g_stagelock(仮）, g_name, g_score);

	fclose(fp);			//ファイルクローズ

	return 0;

}

int Read(void){
	FILE* fp = 0;
#pragma warning(disable:4996)

	switch (g_savefile)
	{
	case 1:
		fp = fopen("Save/SaveFile1.txt", "r");	//ファイルオープン
		break;

	case 2:
		fp = fopen("Save/SaveFile2.txt", "r");	//ファイルオープン
		break;

	case 3:
		fp = fopen("Save/SaveFile3.txt", "r");	//ファイルオープン
		break;
	}

	fp = fopen("Save/SaveFile1.txt", "r");	//ファイルオープン

	//fscanf(fp, "%9d %10s %10d\n", &g_stagelock(仮）, g_name, &g_score);

	fclose(fp);			//ファイルクローズ

	return 0;
}

void NameDebug() {
	DrawString(150, 270, "名前を英字で入力してください", 0x000000);

	// 名前の入力
	DrawString(150, 310, "> ", 0xFFFFFF);
	DrawBox(160, 305, 300, 335, 0x000055, TRUE);
	if (KeyInputSingleCharString(170, 310, 10, &g_name, FALSE) == 1) {
		g_gameScene = GAME_SELECT;
	}

}

