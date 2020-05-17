#include "DxLib.h"
#include "GameOver.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Boss.h"
#include "GameScene.h"
#include "control.h"
#include "Init.h"
#include "Rain.h"

picInfo g_gameOverText;	// [ì¢î∞é∏îs]âÊëúÇÃç¿ïW
void GameOver() {
	GameOverMove();
	GameOverDisp();
}

void GameOverMove() {
	//PlayerMove();
	RainMove();
	if (g_player.y < GROUND) g_player.y += 10;
}

void GameOverDisp() {

	static int motion = 255;
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, motion);
	MapDisp();
	PlayerDisp();
	RainDisp();
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);

	DrawRotaGraph2(g_gameOverText.x, g_gameOverText.y, 0, 0, 0.6, 0.0, g_pic.gameOverText, TRUE);
	//if (motion > 255) {
	//	DrawBox(WINDOW_WIDTH - (motion*4)+1000,200, WINDOW_WIDTH - (motion*4)+1500,400,0xFFFFFF,TRUE);
	//}
	motion -= 10;
	if (motion < 100) {
		motion = 100;
		if( (GameOverTextMove() == 1)
		&&  (g_keyInfo.keyFlg & PAD_INPUT_A) ){
			GameInit();
			g_gameScene = GAME_SELECT;
			motion = 0;
		}
	}
	//}
}
int GameOverTextMove() {
	if (g_gameOverText.y < 298) {
		g_gameOverText.y += 25;
	}
	else {
		g_gameOverText.y = 298;
		return 1;
	}

	return 0;
}

void GameOverInit() {
	g_gameOverText.x = 279;
	g_gameOverText.y = -237;

}