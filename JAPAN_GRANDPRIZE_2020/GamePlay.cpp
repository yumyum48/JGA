#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"

extern image g_pic;
mouse g_mouseInfo;
key g_keyInfo;

// ゲームプレイのメイン関数
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
	
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	MapDisp();		// マップの描画
	//PlayerDisp();	// プレイヤーの描画
	
}

// ゲームプレイの動き
void GamePlayMove() {
	MapMove();		// マップの動き
	//PlayerMove();
}



