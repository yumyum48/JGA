#include "DxLib.h"
#include "Struct.h"
#include "StageClear.h"
#include "GameScene.h"
#include "control.h"
#include "Rain.h"
#include "Player.h"
#include "Macro.h"
#include "Map.h"
#include "Struct.h"
#include "Picture.h"

picInfo clearText;
void StageClear() {
	StageClearMove();		// ステージクリアの動き
	StageClearDisp();		// ステージクリアの表示
}


void StageClearDisp() {
	MapDisp();				// マップの表示
	PlayerDisp();			// プレイヤーの表示
	RainDisp();				// 雨の表示
	DrawModiGraph(-clearText.x + WINDOW_WIDTH, -clearText.y + WINDOW_HEIGHT,
				clearText.x, -clearText.y + WINDOW_HEIGHT,
				clearText.x, clearText.y,
				-clearText.x + WINDOW_WIDTH, clearText.y,
				g_pic.Life[1],TRUE);
	//DrawBox(clearText.x, clearText.y, -clearText.x  + WINDOW_WIDTH, -clearText.y + WINDOW_HEIGHT, 0x00FF00,TRUE);
}

void StageClearMove() {
	RainMove();				// 雨の動き
	if (g_keyInfo.keyFlg & PAD_INPUT_A) {
		g_gameScene = GAME_SELECT;
	}
	if (Player_StageClearMove() == 1) {
		clearText.x += 1;
		clearText.y += 1;


	}
}

int Player_StageClearMove() {
	
	if (g_player.y > GROUND) {	// 主人公が浮いていたら地面に落とす
		g_player.y += 10;
	}
	else {
		g_player.y = GROUND;
	}

	if (g_player.x < 1100) {	// 主人公のX座標を移動させて固定
		g_player.x += 5;
	}
	else {
		g_player.x = 1100;
		return 1;
	}
	
	return 0;
}

void StageClearInit() {
	clearText.x = WINDOW_WIDTH / 2;
	clearText.y = WINDOW_HEIGHT / 2;

}