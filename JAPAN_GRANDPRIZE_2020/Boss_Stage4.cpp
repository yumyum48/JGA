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
/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
picInfo g_boss4_Cloud;	// �{�X�S�̉_�̏��
picInfo g_boss4_Thread;	// �{�X�S�̎��̏��
/*********************************************

* �X�e�[�W�R�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage4() {
	// �{�X�̑傫�����郁�[�^�[
	static int bw = 0;
	static int bh = 0;
	if (g_keyInfo.nowKey & PAD_INPUT_UP) {
		bh--;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
		bw++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
		bh++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
		bw--;
	}

	DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);
	//g_boss4_Cloud.x = g_mouseInfo.mouseX;
	//g_boss4_Cloud.y = g_mouseInfo.mouseY;
	//g_boss4_Cloud.w = g_boss4_Cloud.x + bw;
	//g_boss4_Cloud.h = g_boss4_Cloud.y + bh;
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

	//if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����
	//	BossAttackDisp();	// �{�X�̍U��
	//}
}


// ����(����N���X�̂��悭�ˁH?�ˁH)�����F�u���b�V���A�b�v�Ń{�X���~��`���悤�ɃW�����v������
void BossMove_Stage4() {
	////static int coolTime = 0;								// �d������
	////static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	////static int attackSelect = 0;							// �{�X�̍U���I��
	////static int attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������

	//static int coolTime = 0;						// �d������
	//int boss_MaxDown = 290;							// �{�X�R�̗��������ۂ�Y�n�_
	//static int boss_JumpFlg = BOSS_3_JUMPOFF;		// �{�X�̃W�����v������t���O0: ���~����n�ʂȂ���W�ς�炸���̂܂܁@1:�W�����v���� 2: ���~����
	//int boss_startX = 822;							// �{�X�R��X���W�̏����l


	//int num = GetRand(2);
	//if (BossAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE)	// �{�X���O�t���[���ōU�������Ă��������m�F
	//	num = 1;	// ���Ă���΁A���W�����̂��ߋ����W�����v

	////	�{�X���W�����v������̂��U��������̂��𔻒f����(�����Ō���)
	//if ((g_boss[BOSS_STAGE4].y >= boss_MaxDown)
	//	&& (coolTime++ >= 15)
	//	&& (boss_JumpFlg == BOSS_3_JUMPOFF)
	//	&& (g_boss[BOSS_STAGE4].attackFlg == 0)) {	// �n�ʂɂ���Ƃ� �N�[���^�C������莞�Ԃ����Ă���Ƃ� �{�X���W�����v���Ă��鎞�@�{�X���U�����Ă��Ȃ��Ƃ�

	//	if (num == 0) {
	//		g_boss[BOSS_STAGE4].attackFlg = BOSSATTACK_LONGTON;	// ���L�΂��U��
	//	}
	//	else {
	//		boss_JumpFlg = BOSS_3_JUMPON;
	//	}

	//}
	////coolTime = 0;
	//int jumpTypeflg = 0;	// 0�Ȃ�^�� 1�Ȃ�X���W���C�����Ȃ���߂�
	//if (g_boss[BOSS_STAGE4].x < boss_startX) {
	//	jumpTypeflg = 1;
	//}
	//else {
	//	g_boss[BOSS_STAGE4].x = boss_startX;
	//	jumpTypeflg = 0;
	//}
	//Boss_3_Jump(&coolTime, &boss_JumpFlg, jumpTypeflg);

	//if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����
	//	BossAttackMove();	// �{�X�̍U��

	//}

	//Boss_Knock_Down();
}
// �{�X�S�̕K�v�ȏ��̏�����
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
}