#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"

extern enemyType g_enemy[ENEMY_MAX];	// �G�̏��

extern bossType g_boss[MAP_MAX];

extern int g_killCount;

void EnemyDisp();		// �G�̕`��
void EnemyMove();		// �G�̓���
void EnemyInit();		// �G�̏�����
