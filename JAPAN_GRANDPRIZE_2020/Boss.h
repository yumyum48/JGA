#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"

/***********************************************************

// �}�N���̒�`

***********************************************************/
#define BOSS_WIDTH	(280 * 2)				// �{�X�̉���
#define BOSS_HEIGHT	(200 * 2)				// �{�X�̏c��

/***********************************************************

// �񋓑̂̐錾

***********************************************************/
enum {	// �{�X�̔z��
	BOSS_STAGE1,
	BOSS_STAGE2,
	BOSS_STAGE3,
	BOSS_STAGE4,
	BOSS_STAGE5,
	BOSS_STAGE6,
	BOSS_STAGE7,
	BOSS_STAGE8,
	BOSS_MAX,
};

enum {	// �{�X�̍U�����f
	ENEMY_DROP = 1,			// �G���G�̐���
	WATER_BULLET,			// ���e�ł̍U��
};

enum { // �{�X�̓����p�^�[��
	BOSSMOVE_NOMOTION,		// �m�[���[�V����
	BOSSMOVE_SPEEDDOWN,		// �{�X���ǂ��t����铮��
};
/***********************************************************

// �O���[�o���ϐ��̐錾

***********************************************************/
extern bossInfo g_boss[MAP_MAX];		// �{�X�̏��

/***********************************************************

// �֐��̐錾

***********************************************************/
int InputRand(int rand1, int rand2, int rand3);	// �����������Ƃ��ĎO���A���̒��̈�������_���ŕԂ�
bool BossDamageCheck(int bossHp);				// �{�X���_���[�W���󂯂����ǂ����𒲂ׂ�֐� TRUE: �{�X���_���[�W���󂯂� FALSE: �{�X�̓_���[�W���󂯂Ă��Ȃ�
void BossDisp_Stage1();					// �X�e�[�W�P�̃{�X�̕\��
void BossMove_Stage1();					// �X�e�[�W�P�̃{�X�̓���
void BossDisp_Stage2();					// �X�e�[�W�Q�̃{�X�̕\��
void BossMove_Stage2();					// �X�e�[�W�Q�̃{�X�̓���

void Boss_Knock_Down();					// �{�X�̓����蔻��

void BossInit();						// �{�X�̏�����

void BossAttackDisp();					// �{�X�̍U��
void BossAttackMove();					// �{�X�̍U��

// �{�X�̃X�L���̕\��
void BossEnemyDropDisp();				// �ア�G���o���{�X��p�̋Z�̊֐�
void BossWaterBulletDisp();				// ���e�ōU������{�X��p�̋Z�̊֐�
// �{�X�̃X�L���̓���
void BossEnemyDropMove();				// �ア�G���o���{�X��p�̋Z�̊֐�
void BossMoveMotion(int *coolTime, int *moveFlg);		//
void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg);
void BossWaterBulletMove();				// ���e�ōU������{�X��p�̋Z�̊֐�
void (* const BossDisp[2])() = {		// �{�X�̕\��
	BossDisp_Stage1,
	BossDisp_Stage2,
};

void (* const BossMove[2])() = {		// �{�X�̓���
	BossMove_Stage1,
	BossMove_Stage2,
};

