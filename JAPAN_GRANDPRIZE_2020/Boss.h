#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"

extern bossInfo g_boss[MAP_MAX];		// �{�X�̏��

#define BOSS_WIDTH	(280)				// �{�X�̉���
#define BOSS_HEIGHT	(200)				// �{�X�̏c��

void BossDisp_Stage1();					// �X�e�[�W�P�̃{�X�̕\��
void BossMove_Stage1();					// �X�e�[�W�P�̃{�X�̓���

void BossHit();							// �{�X�̓����蔻��

void BossInit();						// �{�X�̏�����

void BossAttackDisp();						// �{�X�̍U��
void BossAttackMove();						// �{�X�̍U��

// �{�X�̃X�L���̕\��
void BossEnemyDropDisp();	// �ア�G���o���{�X��p�̋Z�̊֐�
// �{�X�̃X�L���̓���
void BossEnemyDropMove();	// �ア�G���o���{�X��p�̋Z�̊֐�
void (* const BossDisp[1])() = {		// �{�X�̕\��
	BossDisp_Stage1,
};

void (* const BossMove[1])() = {		// �{�X�̓���
	BossMove_Stage1,
};

