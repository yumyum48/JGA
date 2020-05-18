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

#define BOSS_STAGE2_WIDTH (271)		// �{�X�̉���
#define BOSS_STAGE2_HEIGHT (271)	// �{�X�̏c��
/*********************************************

* �X�e�[�W�Q�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage2() {
	// �{�X�̑傫�����郁�[�^�[
	/*static int bw = 0;
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
	}*/
	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.monseY, g_mouseInfo.mouseX + bw, g_mouseInfo.monseY + bh, 0x00FF00, TRUE);

	//DrawRotaGraph(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, 0.9f, 0.0, g_pic.enemy_walk[0], FALSE, TRUE);
	DrawBox(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, g_boss[BOSS_STAGE2].x + BOSS_STAGE2_WIDTH, g_boss[BOSS_STAGE2].y + BOSS_STAGE2_HEIGHT, 0x00FF00, TRUE);
	
}

// ����
void BossMove_Stage2() {
	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	static int attackSelect = 0;							// �{�X�̍U���I��


	if ((coolTime++ > 120)									// �d������
		&& (g_boss[BOSS_STAGE2].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// �{�X���ړ����Ă��Ȃ����

		attackSelect = InputRand(0, 2, 3);								//�����ōU�����邩�ړ������邩������

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE2].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;
		}
		else {	// �U�������Ȃ��Ƃ�
			//moveFlg = BOSSMOVE_SPEEDDOWN;

		}
	}

	//if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	//	BossMoveMotion(&coolTime, &moveFlg);
	//}


	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// �{�X���U�����Ă����
		g_boss[BOSS_STAGE2].x = 700;
		g_boss[BOSS_STAGE2].y = 160;
		BossAttackMove();	// �{�X�̍U��
	}

	Boss_Knock_Down();
}


