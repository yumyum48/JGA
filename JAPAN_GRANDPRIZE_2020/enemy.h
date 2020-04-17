#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"

extern enemyType g_enemy[ENEMY_MAX];	// “G‚Ìî•ñ

extern bossType g_boss[MAP_MAX];

extern int g_killCount;

void EnemyDisp();		// “G‚Ì•`‰æ
void EnemyMove();		// “G‚Ì“®‚«
void EnemyInit();		// “G‚Ì‰Šú‰»
