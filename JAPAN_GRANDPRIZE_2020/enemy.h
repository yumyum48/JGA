#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// �G�l�~�[�̉���
#define ENEMY_HEIGHT	 (545 * 0.2)// �G�l�~�[�̏c��
extern enemyType g_enemy[ENEMY_MAX];	// �G�̏��

extern const int ENEMY_BEAT_MAX[MAP_MAX];	//�e�X�e�[�W�̎G���G��|�����ł�

extern int g_enemybeat;	// �G�l�~�[��|���������J�E���g����O���[�o���ϐ�

//extern int g_killCount;
void MonsterDisp();		// �ア�G�A�{�X�̕\��
void MonsterMove();		// �ア�G�A�{�X�̓���
void EnemyDisp();		// �G�̕`��
void EnemyMove();		// �G�̓���
void EnemyInit();		// �G�̏�����
