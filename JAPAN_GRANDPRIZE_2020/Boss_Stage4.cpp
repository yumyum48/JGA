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

struct rightningInfo {		// �����̏��
	int x = 419;				// X���W
	int y = 180;				// Y���W
	int cnt;	// �{�X�S�̗���������܂ł̃J�E���g
	float exRate;		// �g�嗦

};

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
rightningInfo g_rightning;	// �����̏��
/*********************************************

* �X�e�[�W�R�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage4() {
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
	//g_boss4_Cloud.x = g_mouseInfo.mouseX;
	//g_boss4_Cloud.y = g_mouseInfo.mouseY;
	//g_boss4_Cloud.w = g_boss4_Cloud.x + bw;
	//g_boss4_Cloud.h = g_boss4_Cloud.y + bh;
	

	g_rightning.exRate = (float)g_rightning.cnt / 500.0F;
	
	// �_�̕\��
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	// �����̏[�d
	DrawRotaGraph(g_boss4_Cloud.x + ((g_boss4_Cloud.w - g_boss4_Cloud.x )/ 2), g_boss4_Cloud.y + ((g_boss4_Cloud.h - g_boss4_Cloud.y) / 2), g_rightning.exRate, 0.0, g_pic.enemy_walk[0], TRUE);
	// ���̕\��
	DrawBox(g_boss4_Thread.x, g_boss4_Thread.y, g_boss4_Thread.w, g_boss4_Thread.h, 0xFFFFFF, TRUE);
	// �w偂̕\��
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

	//Poison_Trap_Disp();	// �ł̃g���b�v�̕\��

	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����
		BossAttackDisp();	// �{�X�̍U��
	}
	DrawFormatString(600, 200, 0xFFFFFF, "cnt = %d", g_rightning.cnt);
}


// ����(����N���X�̂��悭�ˁH?�ˁH)�����F�u���b�V���A�b�v�Ń{�X���~��`���悤�ɃW�����v������
void BossMove_Stage4() {
	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	static int attackSelect = 0;							// �{�X�̍U���I��
	static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������

	if ((coolTime++ > 60)												// �d������
		&& (g_boss[BOSS_STAGE4].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
		&& (moveFlg == BOSSMOVE_NOMOTION)) {							// �{�X���ړ����Ă��Ȃ����


		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// �{�X���U�����Ȃ��Ƃ��ɏ�������G���G�̏�����
			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	
		}
						
		int enumSet = BOSSATTACK_MINICLOUD_DROP;
		if (g_rightning.cnt >= 1800)									// �����̃J�E���g��30�b�ȏ�Ȃ痋���𗎂Ƃ����鏀��������
			enumSet = BOSSATTACK_LIGHTNING;

		attackSelect = InputRand(BOSSATTACK_MINISPIDER_DROP, enumSet, 0);			//�����ōU�����邩�ړ������邩������

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;												// �N�[���^�C��������
		}
		else {	// �U�������Ȃ��Ƃ�
			g_trap.dispFlg = TRUE;	// �g���b�v���o��

		}
	}
	// �g���b�v�𐶐����鎞�Ƀg���b�v��������
	if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
		g_trap.WaveInit(g_boss[BOSS_STAGE4].x);
	}
	//// �o�b�t�@�[�Ɣ�ׂĎG���G�������ĂȂ��Ƃ��͎G���G��������
	//if (BossNoAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// �o�b�t�@�[�Ɣ�ׂĎG���G�������鎞�G���G��������
	//if (BossDropAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// �U�������ōs��
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	//	BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	//}

	// �U��
	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����

		BossAttackMove();	// �{�X�̍U��
	}

	//Poison_Trap_Move();	// �ł̃g���b�v�̓���
	//if (g_boss4_Rightning_Cnt >= 1800) {		// �J�E���g���P�̍���Disp�̕����𐧌�
	//	g_boss4_Rightning_Cnt = 1799;
	//}

	// �����𗎂Ƃ��J�E���g�{�X�������𗎂Ƃ��Ă��Ȃ���΃J�E���g
	if(g_boss[BOSS_STAGE4].attackFlg != BOSSATTACK_LIGHTNING)
		g_rightning.cnt++;
	if (g_rightning.cnt > 1800 && g_boss[BOSS_STAGE4].attackFlg != BOSSATTACK_LIGHTNING) {
		g_rightning.cnt = 1800;
	}
	Boss_Knock_Down();	// �{�X���|����Ă鏈��
}

void Boss_Lightning_Disp() {
	
	static int stopCnt = 0;	// ������\�������鎞��


	if (g_rightning.cnt <= 0) {
		DrawBox(g_rightning.x, g_rightning.y, g_rightning.x + 526, g_rightning.y + 488, 0x00FFFF, TRUE);
		g_rightning.cnt = 0;
		stopCnt++;
	}
	
	if (stopCnt >= 90) {
		g_rightning.cnt = 0;					 // �����܂ł̃J�E���g��������
		g_boss[g_select_Stage].attackFlg = 0;    // attack�t���O��������
		stopCnt = 0;							 // �����̕\���J�E���g��������
	}
}
void Boss_Lightning_Move() {

	g_rightning.cnt-= 50;


}
// �{�X�S�̕K�v�ȏ��̏�����
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
	g_boss4_Thread.ThreadInit();
}