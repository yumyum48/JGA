#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Player.h"
#include "control.h"
#include "Controler.h"
#include "Select.h"
#include "GameScene.h"
#include "Init.h"
#define _USE_MATH_DEFINES
#include <math.h>

struct bossAttackInfo {	// �{�X�̍U���̍ۂɎg���\������
	int x, y;

};
/*********************************************

* �X�e�[�W�P�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage1() {
	//	���ʂ��x��
	// �񎟌��z���0�Ԗڂ͓G�{��
	// �P�Ԗڂ͐���
	int bossAnime_MAX[2] = { 3, 7};		// �A�j���[�V�����̍ŏI��
	int bossAnime_Start[2] = { 0, 5 };	// �A�j���[�V�����̍ŏ�
	static int anime[2] = { 0, 0 };		// �摜�̐؂�ւ�
	static int time = 0;				// �t���[���P�ʂ̃J�E���g

	if (time++ % 4 == 0) anime[0]++;
	if (time % 6 == 0) anime[1]++;
	for (int i = 0; i < 2; i++) {
		if (anime[i] > bossAnime_MAX[i]) {
			anime[i] = bossAnime_Start[i];
		}
	}
		
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[1]], TRUE);
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[0]], TRUE);

	if (g_boss[0].attackFlg != 0) {
		BossAttackDisp();	// �{�X�̍U��
	}

}

// ����
void BossMove_Stage1() {

	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���


	if( (coolTime++ > 120 )									// �d������
	&&  (g_boss[0].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
	&&  ( moveFlg == BOSSMOVE_NOMOTION) ){					// �{�X���ړ����Ă��Ȃ����

		if (GetRand(2) == 1) {								//�����ōU�����邩�ړ������邩������
			g_boss[0].attackFlg = ENEMY_DROP;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;
		}
		else {	// �U�������Ȃ��Ƃ�
			moveFlg = BOSSMOVE_SPEEDDOWN;
			
		}
	}

	if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

		BossMoveMotion(&coolTime, &moveFlg);
	}


	if (g_boss[0].attackFlg != 0) {						// �{�X���U�����Ă����
		g_boss[0].x = 700;
		g_boss[0].y = 160;
		BossAttackMove();	// �{�X�̍U��
	}

}

void Boss_Neutral_Motion() {

}
/*********************************************

* �{�X�̓����B

*/////////////////////////////////////////////
// �{�X�̓����p�^�[��
void BossMoveMotion(int *coolTime, int *moveFlg){

	switch (*moveFlg)
	{
	case BOSSMOVE_SPEEDDOWN:
		BossMoveMotion_Pattern1(coolTime, moveFlg);
		break;
	default:
		break;
	}

}

void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg) {
	if (g_boss[g_select_Stage].x > 0) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// �c�̐U�ꕝ
		g_boss[g_select_Stage].x -= 5;						// �{�X�̈ړ���
	}
	else {
		g_boss[g_select_Stage].x = 700;
		g_boss[g_select_Stage].y = 160;
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
	}
}
/*********************************************

* �{�X�̓����蔻��	// ������ƃv���C���[hp����

*/////////////////////////////////////////////
void BossHit() {
	
	if (PlayerHitCheck(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == TRUE) {
		g_player.hp--;
	}
	
}
/*********************************************

* �{�X�̍U���֌W

*/////////////////////////////////////////////
// �{�X�̍U���̑S�̊Ǘ�(�\��)
void BossAttackDisp() {
	
	
	switch (g_boss[0].attackFlg) {
		case ENEMY_DROP:
		
			BossEnemyDropDisp();	// �ア�G���o��
			DrawFormatString(100, 600, 0xFF00FF, "�{�X���U�����Ă܂���I");
			break;

		default:
			break;
	}
	

	
}
// �{�X�̍U���̑S�̊Ǘ�(����)
void BossAttackMove() {

	DrawFormatString(100, 700, 0xFF00FF, "�{�X���U�����Ă܂���I");

	if (g_keyInfo.keyFlg & PAD_INPUT_4) g_boss[0].attackFlg = 0;

	switch (g_boss[0].attackFlg) {
		case ENEMY_DROP:
			BossEnemyDropMove();	// �ア�G���o��
			break;

		default:
			break;
	}
	
}
/*********************************************

* �{�X���ア�G���o���U��������֐�

*/////////////////////////////////////////////
// �ア�G���o��(�\��)
void BossEnemyDropDisp() {

	static int enemypop_MAX = 0;
		
	for (int i = 0; i < enemypop_MAX; i++) {
		DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
		
		
	}
}
// �ア�G���o��(����(�����蔻��Ȃ�))
void BossEnemyDropMove() {

}



/*********************************************

* �X�e�[�W�R�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage3() {
	if (g_enemybeat >= 10) {
		DrawBox(600, 0, 1280, 768, 0x0FF000, TRUE);
	}
}
// ����
void BossMove_Stage3() {

}

// �{�X�̏�����
void BossInit() {
	g_boss[BOSS_STAGE1].Init_Stage1();
	g_boss[BOSS_STAGE2].Init_Stage2();
	g_boss[BOSS_STAGE3].Init_Stage3();
	g_boss[BOSS_STAGE4].Init_Stage4();
	g_boss[BOSS_STAGE5].Init_Stage5();
	g_boss[BOSS_STAGE6].Init_Stage6();
	g_boss[BOSS_STAGE7].Init_Stage7();
	g_boss[BOSS_STAGE8].Init_Stage8();
}