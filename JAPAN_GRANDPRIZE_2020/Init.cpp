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
#include "Change_ScReen_Animation.h"
#include "StageClear.h"
#include "GameOver.h"
#include "HP.h"
// それぞれの初期化処理
void GameInit() {
	MapInit();			// マップデータの初期化処理
	PlayerInit();		// プレイヤーの初期化処理
	HpInit();			// HP関係の初期化
	EnemyInit();		// エネミーの初期化処理
	RainInit();			// 雨のアニメーションの初期化処理
	BossInit();			// ボスの情報を初期化
	TrapInit();			// トラップの情報初期化
	SelectInit();		// セレクト画面の初期化
	g_enemybeat = 0;	// エネミーを倒した数をカウントする変数の初期化
	ChangeScreen_Animation_Init();	// シーンチェンジアニメーションの初期化
	StageClearInit();	// ステージクリア画面の初期化
	GameOverInit();		// ゲームオーバー画面の初期化
	//g_gameScene = GAME_TITLE;	// タイトルへ戻る

}

// 保存すべきデータを削除
void Reset(){
	g_select_MAX = 0;			// プレイヤーが行けるステージを１のみにする
	g_player.skill_MAX = 1;	// プレイヤーの取得しているスキルをゲーム開始状態に戻す
	g_playTime = 0;	// プレイ時間を初期化
	g_player.skillcustom[0] = 1;
	g_player.skillcustom[1] = 0;
	g_player.skillcustom[2] = 0;
	GameInit();
}