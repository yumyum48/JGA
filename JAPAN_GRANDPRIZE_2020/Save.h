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
	DETA_SKILL_MAX,
	DETA_PLAYTIME,
	DETA_MAX,
};
//int Save();
//int Read();
void SaveModeDisp();					// セーブデータメニュー画面の表示
int SaveData_Open(int buf[]);			// セーブデータを読み込んで表示するために、表示する内容を記憶させる関数
//extern char g_name;					//デバッグ用
