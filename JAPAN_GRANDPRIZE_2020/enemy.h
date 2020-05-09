#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// エネミーの横幅
#define ENEMY_HEIGHT	 (545 * 0.2)// エネミーの縦幅
extern enemyType g_enemy[ENEMY_MAX];	// 敵の情報

extern const int ENEMY_BEAT_MAX[MAP_MAX];	//各ステージの雑魚敵を倒す数です

extern int g_enemybeat;	// エネミーを倒した数をカウントするグローバル変数

//extern int g_killCount;
void MonsterDisp();		// 弱い敵、ボスの表示
void MonsterMove();		// 弱い敵、ボスの動き
void EnemyDisp();		// 敵の描画
void EnemyMove();		// 敵の動き
void EnemyInit();		// 敵の初期化
