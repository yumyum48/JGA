#pragma once

void StageSelect();
void SelectDisp();
void SpeedSelect();

extern int g_game_stage;		//ステージをセレクト
extern int g_speedLevel;		//スクロール速度の選択

enum { // スクロール速度
	SPEED_EASY = 8,
	SPEED_NORMAL = 10,
	SPEED_HARD = 13,
};