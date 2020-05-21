#pragma once
#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#define ENEMY_WIDTH		 (574 * 0.2)// �G�l�~�[�̉���
#define ENEMY_HEIGHT	 (545 * 0.2)// �G�l�~�[�̏c��
extern enemyType g_enemy[ENEMY_MAX];	// �G�̏��
extern enemyInfo g_enemyBuffer[ENEMY_MAX];	// ���j�����G�̏����i�[����ϐ�

extern const int ENEMY_BEAT_MAX[MAP_MAX];	//�e�X�e�[�W�̎G���G��|�����ł�

extern int g_enemybeat;	// �G�l�~�[��|���������J�E���g����O���[�o���ϐ�

//extern int g_killCount;
void MonsterDisp();		// �ア�G�A�{�X�̕\��
void MonsterMove();		// �ア�G�A�{�X�̓���
void EnemyDisp_stage1();		// �G�̕`��
void EnemyDisp_stage2();		// �G�̕`��
void EnemyDisp_stage3();		// �G�̕`��
void EnemyDisp_stage4();		// �G�̕`��
void EnemyDisp_stage5();		// �G�̕`��
void EnemyDisp_stage6();		// �G�̕`��
void EnemyDisp_stage7();		// �G�̕`��
void EnemyDisp_stage8();		// �G�̕`��
void EnemyMove();		// �G�̓���
void EnemyInit();		// �G�̏�����
int EnemyEvaporation();	// �G�̌��j���̃A�j���[�V����



void (* const EnemyDisp[MAP_MAX])() = {
		EnemyDisp_stage1,
		EnemyDisp_stage2,
		EnemyDisp_stage3,
		EnemyDisp_stage4,
		EnemyDisp_stage5,
		EnemyDisp_stage6,
		EnemyDisp_stage7,
		EnemyDisp_stage8,
};		// �G�̕`��

