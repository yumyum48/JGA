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

* �X�e�[�W�R�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage3() {
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
	}
	DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);*/

	//DrawRotaGraph(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, 0.9f, 0.0, g_pic.enemy_walk[0], FALSE, TRUE);

	DrawBox(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, g_boss[BOSS_STAGE3].x + BOSS_STAGE3_WIDTH, g_boss[BOSS_STAGE3].y + BOSS_STAGE3_HEIGHT, 0x00FF00, TRUE);

	if (g_boss[BOSS_STAGE3].attackFlg != 0) {						// �{�X���U�����Ă����
		BossAttackDisp();	// �{�X�̍U��
	}
}


enum {	// �{�X�R�̃W�����v�t���O����
	OFF,
	JUMP,
	DOWN,
};

// ����(����N���X�̂��悭�ˁH?�ˁH)�����F�u���b�V���A�b�v�Ń{�X���~��`���悤�ɃW�����v������
void BossMove_Stage3() {
	static int coolTime = 0;						// �d������
	//static int moveFlg = BOSSMOVE_NOMOTION;			// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	//static int attackSelect = 0;					// �{�X�̍U���I��
	int boss_MaxUp = 97;							// �{�X�R���W�����v���Ă�����Y���W�ō��x
	int boss_MaxDown = 290;							// �{�X�R�̗��������ۂ�Y�n�_
	static int boss_JumpFlg = OFF;					// �{�X�̃W�����v������t���O0: ���~����n�ʂȂ���W�ς�炸���̂܂܁@1:�W�����v���� 2: ���~����
	
	//	�{�X���W�����v������̂��U��������̂��𔻒f����(�����Ō���)
	if( (g_boss[BOSS_STAGE3].y >= boss_MaxDown) && (coolTime++ >= 15) && (boss_JumpFlg == OFF) && (g_boss[BOSS_STAGE3].attackFlg == 0) ){	// �n�ʂɂ���Ƃ� �N�[���^�C������莞�Ԃ����Ă���Ƃ� �{�X���W�����v���Ă��鎞�@�{�X���U�����Ă��Ȃ��Ƃ�
			
		int num = GetRand(2);
		if (num == 0) {
			g_boss[BOSS_STAGE3].attackFlg = BOSSATTACK_LONGTON;	// ���L�΂��U��
		}
		else {
			boss_JumpFlg = JUMP;
		}

	}
	//coolTime = 0;
	if (boss_JumpFlg == JUMP) {	// �㏸
		if (g_boss[BOSS_STAGE3].y >= boss_MaxUp) {		// �{�X�����n�_�܂ŏ�ɏグ��
			g_boss[BOSS_STAGE3].y -= 2;
		}
		else if (g_boss[BOSS_STAGE3].y < boss_MaxUp) {	// ����n�_�܂ŗ�������W���Œ�
			g_boss[BOSS_STAGE3].y = boss_MaxUp;
			boss_JumpFlg = DOWN;	// ���~������

		}
	}
	else if (boss_JumpFlg == DOWN) {	// ���~
		if (g_boss[BOSS_STAGE3].y < boss_MaxDown) {		// �{�X�����n�_�܂ŏ�ɏグ��
			g_boss[BOSS_STAGE3].y += 2;
		}
		else if (g_boss[BOSS_STAGE3].y >= boss_MaxDown) {	// ����n�_�܂ŗ�������W���Œ�
			g_boss[BOSS_STAGE3].y = boss_MaxDown;
			boss_JumpFlg = OFF;	// �W�����v�t���O���I�t��
			coolTime = 0;		// �N�[���^�C����������
		}


	}
	if (g_boss[BOSS_STAGE3].attackFlg != 0) {						// �{�X���U�����Ă����
		BossAttackMove();	// �{�X�̍U��
		
		
	}
	
	Boss_Knock_Down();
}