#include "DxLib.h"
#include "Struct.h"
#include "GameClear.h"
#include "control.h"
#include "GameScene.h"
#include "GameScene.h"
void GameClear() {
	GameClearDisp();
	GameClearMove();
}

void GameClearDisp() {
	DrawFormatString(500, 500, 0xFF00FF, "ZƒL[‚ğ‰Ÿ‚µ‚Ä‚ËI");
}

void GameClearMove() {
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		g_gameScene = GAME_TITLE;
	}
}