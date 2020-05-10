#pragma once

void StageSelect();				// ステージのセレクト処理
void SelectDisp();				// ステージのセレクトの表示処理
void SelectMove();				// ステージのセレクトの動きの処理
void SpeedSelect();				// ステージのセレクトの動きの処理
void SelectInit();				// セレクト画面の初期化
extern int g_select_Stage;		//ステージをセレクト
extern int g_speedLevel;		//スクロール速度の選択

enum { // スクロール速度
	SPEED_EASY = 10,
	SPEED_NORMAL = 12,
	SPEED_HARD = 15,
};