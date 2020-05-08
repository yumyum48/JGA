#include "DxLib.h"
#include "Struct.h"
#include "StageClear.h"
#include "GameScene.h"
#include "control.h"

void StageClear() {
	StageClearMove();
	StageClearDisp();
}

void StageClearDisp() {
	MapDisp();
	DrawFormatString(500, 500, 0xFF00FF, "ZƒL[‚ğ‰Ÿ‚µ‚Ä‚ËI");
}

void StageClearMove() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		g_gameScene = GAME_SELECT;
	}
}