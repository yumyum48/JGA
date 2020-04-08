#include "DxLib.h"
#include "Struct.h"
#include <math.h>
#include "GamePlay.h"
#include "Select.h"
#include "control.h"

#define STAGE_NUMBER 7

int stageX = 455;		//ステージセレクトX座標
int stageY = 285;		//ステージセレクトY座標
int stageW = 305;		//ステージセレクト幅
int stageH = 298;		//ステージセレクト高さ

float x;
float y;

int Game_Stage = 0;		//ステージをセレクト

void StageSelect() {

	//メニューカーソル移動処理
	if (g_keyInfo.keyFlg & PAD_INPUT_RIGHT) {
		if (++Game_Stage > 7) Game_Stage = 0;
	}

	if (g_keyInfo.keyFlg & PAD_INPUT_LEFT) {
		if (--Game_Stage < 0) Game_Stage = 7;
	}

	//ｚで選択（デバック）
	if (g_keyInfo.keyFlg & PAD_INPUT_A) 
		GamePlay();

	SelectDisp();
}

void SelectDisp(void) {
	for (int i = 0; i < STAGE_NUMBER; i++) {
		float bb = i % STAGE_NUMBER;
		float angle = (DX_TWO_PI / STAGE_NUMBER * bb) + 6.0675;
		x = stageX + cos(angle) * stageW;
		y = stageY + sin(angle) * stageH;

		//ステージ表示
		DrawBox( x , y ,x + 180,y + 180, 0x008000, TRUE);

	}

	DrawBox(420, 235, 655, 470,0x008000, TRUE);

	switch (Game_Stage)
	{
	case 0:	DrawBox(x-265, y-3, x - 85, y + 178, 0xFF0000, FALSE);break;
	case 1: DrawBox(x, y, x + 180, y + 180, 0xFF0000, FALSE); break;
	case 2: DrawBox(x+163, y+205, x + 345, y + 385, 0xFF0000, FALSE); break;
	case 3: DrawBox(x+103, y+455, x + 282, y + 637, 0xFF0000, FALSE); break;
	case 4: DrawBox(x-138, y+565, x + 44, y + 745, 0xFF0000, FALSE); break;
	case 5: DrawBox(x- 375, y+450, x - 195, y +631, 0xFF0000, FALSE); break;
	case 6: DrawBox(x-432.5, y+198.5, x - 250, y + 380, 0xFF0000, FALSE); break;
	case 7: DrawBox(420,235,655,470, 0xFF0000, FALSE); break;
	default: break;
	}
}