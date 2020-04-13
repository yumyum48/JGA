#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"


// ゲームプレイのメイン関数
void GamePlay() {
	GamePlayMove();
	GamePlayDisp();
	
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	MapDisp();		// マップの描画
	EnemyDisp();	// エネミーの描画
	PlayerDisp();	// プレイヤーの描画
	RainDisp();		// 雨の描画
	
}

// ゲームプレイの動き
void GamePlayMove() {
	MapMove();		// マップの動き
	EnemyMove();	// エネミーの動き
	PlayerMove();	// プレイヤーの動き
	RainMove();		// 雨の動き
}



