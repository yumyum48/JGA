#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"

image g_pic;
mouse g_mouseInfo;
key g_keyInfo;

float moveX;	// プレイヤーの動きに合わせてマップを動かす

// ゲームプレイのメイン関数
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	MapDisp();		// マップの描画
	PlayerDisp();	// プレイヤーの描画
	
}

// ゲームプレイの動き
void GamePlayMove() {

	PlayerMove();

}
void MapDisp() {

	static int map1X = 0;	// 緑マップのX座標
	static int map2X = 1024;// 黄色マップのX座標
	
	// マップを繰り返させる
	if ((int)moveX + 1024 + map1X <= 0) {
		map1X = map2X + 1024;
	}

	if ((int)moveX + 1024 + map2X <= 0) {
		map2X = map1X + 1024;
	}
	// マップの描画
	DrawGraph(map1X + moveX, 0, g_pic.map[0], TRUE);
	DrawGraph(map2X + moveX, 0, g_pic.map[1], TRUE);
}


