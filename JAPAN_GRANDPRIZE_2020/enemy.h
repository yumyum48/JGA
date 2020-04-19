#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// エネミーの横幅
#define ENEMY_HEIGHT	 (545 * 0.2)// エネミーの縦幅
extern enemyType g_enemy[ENEMY_MAX];	// 敵の情報



//extern int g_killCount;

void EnemyDisp();		// 敵の描画
void EnemyMove();		// 敵の動き
void EnemyInit();		// 敵の初期化
