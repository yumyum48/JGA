#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"
#include "GameScene.h"
#include "Controler.h"
#include "Picture.h"
#define STAGE_NUMBER 7

void StageSelect() {
	
	

	SpeedSelect();
	SelectMove();
	SelectDisp();
}

void SelectDisp(void) {
	picInfo stage[8];
	


	

	DrawGraph(0, 0, g_pic.selectBack, TRUE);
	for (int i = 0; i < MAP_MAX; i++) {
		stage[i].SelectStageInit(i);
		DrawBox(stage[i].x, stage[i].y, stage[i].x + 100, stage[i].y + 100, 0x00FF00, TRUE);
		if (i == 7) {
			DrawBox(stage[i].x, stage[i].y, stage[i].x + 200, stage[i].y + 200, 0x00FF00, TRUE);
		}
	}

	DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 100, stage[g_select_Stage].y + 100, 0xFF0000, FALSE);
	if (g_select_Stage == 7) {
		DrawBox(stage[g_select_Stage].x, stage[g_select_Stage].y, stage[g_select_Stage].x + 200, stage[g_select_Stage].y + 200, 0xFF0000, FALSE);
	}
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + 100, g_mouseInfo.mouseY + 100, 0x00FF00, TRUE);
	//int stageX = 455;		//ステージセレクトX座標
	//int stageY = 285;		//ステージセレクトY座標
	//int stageW = 305;		//ステージセレクト幅
	//int stageH = 298;		//ステージセレクト高さ

	//float g_x;	// 
	//float g_y;	// 

	//for (int i = 0; i < STAGE_NUMBER; i++) {
	//	float bb = i % STAGE_NUMBER;
	//	float angle = (DX_TWO_PI / STAGE_NUMBER * bb) + 6.0675;
	//	g_x = stageX + cos(angle) * stageW;
	//	g_y = stageY + sin(angle) * stageH;

	//	//ステージ表示
	//	DrawBox( g_x , g_y ,g_x + 180,g_y + 180, 0x00ff00, TRUE);

	//}

	//DrawBox(420, 235, 655, 470,0x008000, TRUE);

	//switch (g_select_Stage)
	//{
	//case 0:	DrawBox(g_x-265, g_y-3, g_x - 85, g_y + 178, 0xFF0000, FALSE);break;
	//case 1: DrawBox(g_x, g_y, g_x + 180, g_y + 180, 0xFF0000, FALSE); break;
	//case 2: DrawBox(g_x+163, g_y+205, g_x + 345, g_y + 385, 0xFF0000, FALSE); break;
	//case 3: DrawBox(g_x+103, g_y+455, g_x + 282, g_y + 637, 0xFF0000, FALSE); break;
	//case 4: DrawBox(g_x-138, g_y+565, g_x + 44, g_y + 745, 0xFF0000, FALSE); break;
	//case 5: DrawBox(g_x- 375, g_y+450, g_x - 195, g_y +631, 0xFF0000, FALSE); break;
	//case 6: DrawBox(g_x-432.5, g_y+198.5, g_x - 250, g_y + 380, 0xFF0000, FALSE); break;
	//case 7: DrawBox(420,235,655,470, 0xFF0000, FALSE); break;
	//default: break;
	//}
}
void SelectMove() {
	//メニューカーソル移動処理
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++g_select_Stage > 7) g_select_Stage = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--g_select_Stage < 0) g_select_Stage = 7;
	}

	//ｚで選択（デバック）
	if (g_keyInfo.keyFlg & PAD_INPUT_3)
		g_gameScene = GAME_PLAY;
}
// スクロール速度の選択
void SpeedSelect() {
	static int speedSelect = 0;
	static bool StickFlg = FALSE;

	DrawFormatString(100, 10, 0xffff00, "%d", speedSelect);

	// プレイヤーの操作
	if (g_keyInfo.keyFlg & PAD_INPUT_UP) {
		if (++speedSelect > 2) speedSelect = 0;
	}
	if (g_keyInfo.keyFlg & PAD_INPUT_DOWN) {
		if (--speedSelect < 0) speedSelect = 2;
	}
	// スクロール速度の決定
	if (speedSelect == 0) {
		g_speedLevel = SPEED_EASY;
	}
	if (speedSelect == 1) {
		g_speedLevel = SPEED_NORMAL;
	}
	if (speedSelect == 2) {
		g_speedLevel = SPEED_HARD;
	}
	//// スクロール速度の決定
	//if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 0)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_EASY;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0) */
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 1)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_NORMAL;
	//}
	//else if (/*(g_button.circleButton == TRUE && g_button.conFlg == 0)*/
	//	(g_keyInfo.keyFlg & PAD_INPUT_A)
	//	&& (speedSelect == 2)) {
	//	//g_button.conFlg = 1;
	//	g_speedLevel = SPEED_HARD;
	//}
}

