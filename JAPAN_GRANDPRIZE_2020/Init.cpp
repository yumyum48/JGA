#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"
#include "GamePlay.h"
#include "Boss.h"
#include "GameScene.h"
#include "Trap.h"
#include "Select.h"

// それぞれの初期化処理
void GameInit() {
	MapInit();			// マップデータの初期化処理
	PlayerInit();		// プレイヤーの初期化処理
	EnemyInit();		// エネミーの初期化処理
	RainInit();			// 雨のアニメーションの初期化処理
	BossInit();			// ボスの情報を初期化
	TrapInit();			// トラップの情報初期化
	SelectInit();		// セレクト画面の初期化
	g_enemybeat = 0;	// エネミーを倒した数をカウントする変数の初期化

	g_gameScene = GAME_TITLE;	// タイトルへ戻る

}


void Reset(){
	g_player.skill_MAX = 1;
}