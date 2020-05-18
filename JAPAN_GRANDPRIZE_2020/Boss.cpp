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
#include "Macro.h"
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
	int bossAnime_MAX[2] = { 7, 15};	// �A�j���[�V�����̍ŏI��
	int bossAnime_Start[2] = { 0, 8 };	// �A�j���[�V�����̍ŏ�
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
	static bool teleportFlg = FALSE;

	if (g_boss[g_select_Stage].x > -BOSS_WIDTH
		&& teleportFlg == FALSE) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// �c�̐U�ꕝ
		g_boss[g_select_Stage].x -= 5;						// �{�X�̈ړ���
	}
	else if(g_boss[g_select_Stage].x <= -BOSS_WIDTH){
		g_boss[g_select_Stage].x = WINDOW_WIDTH + BOSS_WIDTH;
		g_boss[g_select_Stage].y = 160;
		teleportFlg = TRUE;
	}

	if (teleportFlg == TRUE
		&& g_boss[g_select_Stage].x > 700) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
		g_boss[g_select_Stage].y -= sin(angle) * 10 - 0.8;			// �c�̐U�ꕝ
		g_boss[g_select_Stage].x -= 5;						// �{�X�̈ړ���
	}
	else if (teleportFlg == TRUE) {
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
		teleportFlg = FALSE;
	}
}
/*********************************************

* �{�X�̓����蔻��	// ������ƃv���C���[hp����

*/////////////////////////////////////////////
void Boss_Knock_Down() {
	
	if (g_boss[g_select_Stage].hp <= 0) {
		g_gameScene = GAME_STAGE_CLEAR;
		g_select_MAX++;	// �Z���N�g�ł���}�b�v�𑝂₷
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
			//DrawFormatString(100, 600, 0xFF00FF, "�{�X���U�����Ă܂���I");
			g_boss[BOSS_STAGE1].attackFlg = 0;
			break;

		case WATER_BULLET:
			BossWaterBulletDisp();	// ���e�̔���
			break;

		default:
			break;
	}
	

	
}
// �{�X�̍U���̑S�̊Ǘ�(����)
void BossAttackMove() {

	//DrawFormatString(100, 700, 0xFF00FF, "�{�X���U�����Ă܂���I");

	//if (g_keyInfo.keyFlg & PAD_INPUT_4) g_boss[0].attackFlg = 0;

	switch (g_boss[0].attackFlg) {
		case ENEMY_DROP:
			//BossEnemyDropMove();	// �ア�G���o��
			g_boss[BOSS_STAGE1].attackFlg = 0;
			break;

		case WATER_BULLET:
			BossWaterBulletMove();	// ���e�̔���
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
		DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy_walk[0], TRUE);
		
		
	}
}
// �ア�G���o��(����(�����蔻��Ȃ�))
void BossEnemyDropMove() {

}

/*********************************************

* �{�X�����e�ōU��������֐�

*/////////////////////////////////////////////
// ���e�̕`��
void BossWaterBulletDisp() {
	static int animationMax = 3;			// �A�j���[�V����
	static int anime = 0;				// �A�j������
	static int time = 0;				// �o�ߎ���
	static int startX = g_boss[BOSS_STAGE1].x + 100,
				startY = g_boss[BOSS_STAGE1].y + 200;	// ���e�̏����ʒu
	static float moveX = 0, moveY = 0;	// ���e�̈ړ���
	static int noDamegeCnt = 60;		// �_���[�W���󂯕t���Ȃ�����
	static bool attackFlg = FALSE;		// �U�����f�t���O	 treu:�U����  false:���U��

	// �t���[���P�ʂ̔�e���̒���
	if (noDamegeCnt++ < 60);
	
	DrawBox(startX + moveX - 40, startY + moveY + 0,
		startX + moveX + 40, startY + moveY - 20, 0xFFFFFF, FALSE);
	// �v���C���[�ɐ��e�������������̏���
	if (noDamegeCnt >= 60
		&& (PlayerHitCheck(startX + moveX - 40, startY + moveY + 0,
			startX + moveX + 40, startY + moveY - 20) == TRUE)) {
		g_player.hp--;
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 200) {
			g_boss[BOSS_STAGE1].attackFlg = 0;
		}
	}

	// ���e����ʊO�ɏo���Ƃ��̏���
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}

	// ���e�̃A�j���[�V����
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// ���e�̕\��
	if (attackFlg == FALSE) {
		moveX -= 7.5;
		moveY += 2.5;
		/*moveX -= 3.0;
		moveY += 1.0;*/
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[anime], TRUE, FALSE);
	}
	else if (attackFlg == TRUE) {
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[animationMax], TRUE, FALSE);
	}

	// ���W�ƃt���O�̏�����
	if (attackFlg == TRUE
		&& noDamegeCnt >= 20) {
		moveX = 0;
		moveY = 0;
		anime = 0;
		animationMax = 3;
		attackFlg = FALSE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}



	// �f�o�b�O
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
}
// ���e�̓����I�ȓ���
void BossWaterBulletMove() {

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
	for (int i = BOSS_STAGE1; i < BOSS_MAX; i++) {
		g_boss[i].Init_Stage(i);
	}
	
}