#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// �G�l�~�[�̉���
#define ENEMY_HEIGHT	 (545 * 0.2)// �G�l�~�[�̏c��
extern enemyType g_enemy[ENEMY_MAX];	// �G�̏��



//extern int g_killCount;

void EnemyDisp();		// �G�̕`��
void EnemyMove();		// �G�̓���
void EnemyInit();		// �G�̏�����
