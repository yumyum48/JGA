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
	EnemyDisp();
	PlayerDisp();	// プレイヤーの描画
	RainDisp();
	
}

// ゲームプレイの動き
void GamePlayMove() {
	MapMove();		// マップの動き
	EnemyMove();
	PlayerMove();
	RainMove();
}



