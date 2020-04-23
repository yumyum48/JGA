#include "Struct.h"
#include "DxLib.h"
#include "Picture.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "Boss.h"
#include "Select.h"
// ゲームプレイのメイン関数
void GamePlay() {
	// デバッグ用で一旦入れ替えGamePlayMove();
	GamePlayDisp();
	GamePlayMove();
	MapMove();						// マップの動き
	MapDisp();						// マップの描画
	
}
// ゲームプレイの描画
void GamePlayDisp() {
	
	
	EnemyDisp();					// エネミーの描画
	
	PlayerDisp();					// プレイヤーの描画
	RainDisp();						// 雨の描画
	
}

// ゲームプレイの動き
void GamePlayMove() {
	
	EnemyMove();					// エネミーの動き
	PlayerMove();					// プレイヤーの動き
	
	RainMove();						// 雨の動き
}



