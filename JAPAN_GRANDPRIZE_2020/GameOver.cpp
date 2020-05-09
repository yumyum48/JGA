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

	static int motion = 0;

	MapDisp();
	PlayerDisp();
	RainDisp();
	SetDrawBlendMode(DX_BLENDMODE_ALPHA, ++motion);
	DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x000000, TRUE);
	SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	if (motion > 255) {
		DrawBox(WINDOW_WIDTH - (motion*4)+1000,200, WINDOW_WIDTH - (motion*4)+1500,400,0xFFFFFF,TRUE);
	}
	if (motion > 480) {
		motion = 480;
		if (g_keyInfo.keyFlg & PAD_INPUT_A) {
			GameInit();
			g_gameScene = GAME_SELECT;
			motion = 0;
		}
	}
}