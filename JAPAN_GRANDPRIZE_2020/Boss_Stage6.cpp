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
#include "Trap.h"
#include "HP.h"

#include <math.h>
/*********************************************

* �萔�̐錾

*/////////////////////////////////////////////

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
/*********************************************

* �X�e�[�W�U�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage6() {
	const int animations[4] = { 0, 7, 8, 15 };	// �A�j���[�V�����̎n�_�ƏI�_
	static int anime = 0;							// �v���C���[�̉摜��ς���
	static int time = 0;							// �摜��؂�ւ���^�C�~���O����
	static int animeStart = animations[0];			// �A�j���[�V�����̊J�n�ʒu
	static int animeLast = animations[1];			// �A�j���[�V�����̏I���ʒu�i���[�v�ʒu
	static int shadowNoDispCnt = 0;					// �e��\�����Ă��Ȃ�����
	//// �{�X�̑傫�����郁�[�^�[
	//static int bw = 0;
	//static int bh = 0;
	//if (g_keyInfo.nowKey & PAD_INPUT_UP) {
	//	bh--;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
	//	bw++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
	//	bh++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
	//	bw--;
	//}

	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);

	// �A�j���[�V�����̐i�s
	if (++time % 4 == 0) anime++;
	if (anime > animeLast)anime = animeStart;

	// �Ԃ������ă{�X��\��
	if (g_boss_shadow.shadowDispFlg == FALSE
		&& ++shadowNoDispCnt > 60) {
		g_boss_shadow.shadowDispFlg = TRUE;
		shadowNoDispCnt = 0;
	}

#ifdef DEBUG_MODE_ON
	// �e�̎˒�
	DrawBox(g_boss_shadow.x - g_boss_shadow.w / 2, g_boss_shadow.y + 70 + 40, g_boss_shadow.x, g_boss_shadow.y + g_boss_shadow.h + 70, 0x0000FF, FALSE);
	// �e�̓����蔻��
	DrawBox(g_boss_shadow.x, g_boss_shadow.y + 70 + 40, g_boss_shadow.x + g_boss_shadow.w, g_boss_shadow.y + g_boss_shadow.h + 0, 0xFFFFFF, TRUE);
	if (g_boss_shadow.shadowDispFlg == TRUE) {
		// �e�̕\��
		DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[0], TRUE, TRUE, FALSE);
	}
#endif // DEBUG_MODE_ON


#ifdef DEBUG_MODE_ON
	// �{�X�̓����蔻��
	//DrawBox(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y, g_boss[BOSS_STAGE6].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE6].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	DrawBox(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y + 70, g_boss[BOSS_STAGE6].x + PLAYER_WIDTH, GROUND, 0xFF0000, FALSE);
#endif // DEBUG_MODE_ON
	// �{�X�̕\��
	DrawRotaGraph2(g_boss[BOSS_STAGE6].x, g_boss[BOSS_STAGE6].y + 70, 0, 0, PLAYER_REDUCTION, 0, g_pic.boss_6_1[anime], TRUE, FALSE);


	// �U���\��
	if (g_boss[BOSS_STAGE6].attackFlg != 0) {						// �{�X���U�����Ă����
		BossAttackDisp();	// �{�X�̍U��
	}

}

// ����
void BossMove_Stage6() {
	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	static int attackSelect = 0;							// �{�X�̍U���I��
	//static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������

	if ((coolTime++ > 60)												// �d������
		&& (g_boss[BOSS_STAGE6].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
		&& (moveFlg == BOSSMOVE_NOMOTION)) {							// �{�X���ړ����Ă��Ȃ���
		attackSelect = InputRand(0, 0, BOSSATTACK_LONG_RANGE);//�����ōU�����邩�ړ������邩������


		if (attackSelect != 0) {
			g_boss[BOSS_STAGE6].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;												// �N�[���^�C��������
		}
		else {	// �U�������Ȃ��Ƃ� 

		}
	}
	//// �U�������ōs��
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	//	BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	//}

	// �U��
	if (g_boss[BOSS_STAGE6].attackFlg != 0) {						// �{�X���U�����Ă����

		BossAttackMove();	// �{�X�̍U��
	}

	
	Boss_Knock_Down();	// �{�X���|����Ă鏈��

}

// �{�X�̏�����
void Boss6_Init() {

	g_boss_shadow.ShadowInit(g_boss[BOSS_STAGE6].x);	// �e�{�̂̏�����
	g_boss_shadow.LongRangeInit(g_boss[BOSS_STAGE6].x);	// �������U���̏�����
}