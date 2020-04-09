#include "DxLib.h"
#include "control.h"
#include "Controler.h"
#include "GameTitle.h"
#include "Picture.h"
#include "Struct.h"
#include "GameScene.h"

// グローバル変数の宣言
const int g_StartY = 300;
const int g_spaceY = 120;

// ゲームタイトルのメイン関数
void GameTitle() {
	TitleDisp();	
	TitleMove();
}

// タイトルの描画
void TitleDisp() {
	const int bottunW = 200;
	const int bottunH = 40;
	DrawBox(412, g_StartY, 412 + bottunW, g_StartY + bottunH, 0x00ff00, FALSE);
	DrawBox(412, g_StartY + g_spaceY, 412 + bottunW, g_StartY + g_spaceY + bottunH, 0x00ff00, FALSE);
	DrawString(460, g_StartY + 10, "game select", 0xff0000, false);
}

// タイトルでの動き
void TitleMove() {
	static int selectMode = 0;
	static bool StickFlg = FALSE;

	// プレイヤーの操作
	if ((g_button.moveStick == 4
		|| g_button.moveStick == 5
		|| g_button.moveStick == 6)
		&& StickFlg == TRUE) {
		if (++selectMode >= 3) selectMode = 0;
	}
	if ((g_button.moveStick == 1
		|| g_button.moveStick == 2
		|| g_button.moveStick == 8)
		&& StickFlg == TRUE) {
		if (--selectMode < 0) selectMode = 2;
	}

	// ゲームモードの決定
	if ((g_button.circleButton == TRUE && g_button.conFlg == 0)
		&& (selectMode == 0)) {
		g_button.conFlg = 1;

		g_gameScene = GAME_SELECT;
	}
	else if ((g_button.circleButton == TRUE && g_button.conFlg == 0)
		&& (selectMode == 0)) {
		g_button.conFlg = 1;

		//g_gameScene = GAME_PLAY;
	}
	else if ((g_button.circleButton == TRUE && g_button.conFlg == 0)
		&& (selectMode == 0)) {
		g_button.conFlg = 1;

		//g_gameScene = GAME_PLAY;
	}
}