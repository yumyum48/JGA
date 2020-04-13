#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"

// それぞれの初期化処理
void GameInit() {
	MapInit();		// マップデータの初期化処理
	PlayerInit();	// プレイヤーの初期化処理
	EnemyInit();	// エネミーの初期化処理
	RainInit();		// 雨のアニメーションの初期化処理
}
