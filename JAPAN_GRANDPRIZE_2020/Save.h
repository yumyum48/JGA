#pragma once

//void NameDebug(); //デバッグ用


enum {	// セーブデータファイル
	SAVE_1,
	SAVE_2,
	SAVE_3,
	SAVE_MAX,
};


enum {	// 保存するデータの添え字
	DETA_MAPSELECT,
	DETA_PLAYTIME,
	DETA_SKILL_CUSTOM_1,
	DETA_SKILL_CUSTOM_2,
	DETA_SKILL_CUSTOM_3,
	DETA_MAX,
};
int Save(int savefile);
//int Read();
void SaveModeDisp(int saveX, int saveY[]);		// セーブデータメニュー画面の表示
int SaveData_Open(int buf[], int i);			// セーブデータを読み込んで表示するために、表示する内容を記憶させる関数
//extern char g_name;							//デバッグ用
int SaveData_CL();								// デバッグ用
