#pragma once
#include "DxLib.h"
#include "Struct.h"

//extern playerInfo g_player;				// プレイヤーの情報
//extern enemyType g_enemy[ENEMY_MAX];		// 敵の情報

extern int g_noDamageCnt;						// プレイヤーの無敵時間

void ManagementHP();		// HP管理
void HpMove();				// HP計算処理
void HpDisp();				// HP表示処理
void HpInit();				// Hp関係の初期化