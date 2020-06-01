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


/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////

/*********************************************

* �X�e�[�W�T�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage5() {
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


	DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// �{�X���U�����Ă����
	//	BossAttackDisp();	// �{�X�̍U��
	//}
	
}

// ����(����N���X�̂��悭�ˁH?�ˁH)�����F�u���b�V���A�b�v�Ń{�X���~��`���悤�ɃW�����v������
void BossMove_Stage5() {
	//static int coolTime = 0;								// �d������
	//static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	//static int attackSelect = 0;							// �{�X�̍U���I��
	//static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������

	//if ((coolTime++ > 60)												// �d������
	//	&& (g_boss[BOSS_STAGE4].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
	//	&& (moveFlg == BOSSMOVE_NOMOTION)) {							// �{�X���ړ����Ă��Ȃ����


	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// �{�X���U�����Ȃ��Ƃ��ɏ�������G���G�̏�����
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}

	//	attackSelect = InputRand(0, 0, 0);			//�����ōU�����邩�ړ������邩������

	//	if (attackSelect != 0) {
	//		g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
	//		coolTime = 0;												// �N�[���^�C��������
	//	}
	//	else {	// �U�������Ȃ��Ƃ�
	//		g_trap.dispFlg = TRUE;	// �g���b�v���o��

	//	}
	//}
	//// �g���b�v�𐶐����鎞�Ƀg���b�v��������
	//if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
	//	g_trap.WaveInit(g_boss[BOSS_STAGE4].x);
	//}
	////// �o�b�t�@�[�Ɣ�ׂĎG���G�������ĂȂ��Ƃ��͎G���G��������
	////if (BossNoAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	////	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	////		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////	}
	////}
	////// �o�b�t�@�[�Ɣ�ׂĎG���G�������鎞�G���G��������
	////if (BossDropAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	////	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	////		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////	}
	////}
	////// �U�������ōs��
	////if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	////	BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	////}

	//// �U��
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// �{�X���U�����Ă����

	//	BossAttackMove();	// �{�X�̍U��
	//}

	////Poison_Trap_Move();	// �ł̃g���b�v�̓���
	////if (g_boss4_Rightning_Cnt >= 1800) {		// �J�E���g���P�̍���Disp�̕����𐧌�
	////	g_boss4_Rightning_Cnt = 1799;
	////}

	//
	//Boss_Knock_Down();	// �{�X���|����Ă鏈��
}
