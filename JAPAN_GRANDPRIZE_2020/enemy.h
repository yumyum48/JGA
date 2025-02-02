#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// エネミーの横幅
#define ENEMY_HEIGHT	 (545 * 0.2)// エネミーの縦幅
extern enemyType g_enemy[ENEMY_MAX];	// 敵の情報
extern enemyInfo g_enemyBuffer[ENEMY_MAX];	// 撃破した敵の情報を格納する変数

extern const int ENEMY_BEAT_MAX[MAP_MAX];	//各ステージの雑魚敵を倒す数です

extern int g_enemybeat;	// エネミーを倒した数をカウントするグローバル変数

//extern int g_killCount;
void MonsterDisp();		// 弱い敵、ボスの表示
void MonsterMove();		// 弱い敵、ボスの動き
void EnemyDisp_stage1();		// 敵の描画
void EnemyDisp_stage2();		// 敵の描画
void EnemyDisp_stage3();		// 敵の描画
void EnemyDisp_stage4();		// 敵の描画
void EnemyDisp_stage5();		// 敵の描画
void EnemyDisp_stage6();		// 敵の描画
void EnemyDisp_stage7();		// 敵の描画
void EnemyDisp_stage8();		// 敵の描画
void EnemyMove();		// 敵の動き
void EnemyInit();		// 敵の初期化
int EnemyEvaporation();	// 敵の撃破時のアニメーション



void (* const EnemyDisp[MAP_MAX])() = {
		EnemyDisp_stage1,
		EnemyDisp_stage2,
		EnemyDisp_stage3,
		EnemyDisp_stage4,
		EnemyDisp_stage5,
		EnemyDisp_stage6,
		EnemyDisp_stage7,
		EnemyDisp_stage8,
};		// 敵の描画

