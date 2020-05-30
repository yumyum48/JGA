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

struct rightningInfo {		// �����̏��
	int x;				// X���W
	int y;				// Y���W
	int cnt;	// �{�X�S�̗���������܂ł̃J�E���g
	float exRate;		// �g�嗦

};
/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
picInfo g_boss4_Cloud;		// �{�X�S�̉_�̏��
picInfo g_boss4_Thread;		// �{�X�S�̎��̏��
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
	
	DrawRotaGraph(g_boss4_Cloud.w / 2, g_boss4_Cloud.h / 2, g_rightning.exRate, 2.0, g_pic.enemy_walk[0], TRUE);
	// �_�̕\��
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	// ���̕\��
	DrawBox(g_boss4_Thread.x, g_boss4_Thread.y, g_boss4_Thread.w, g_boss4_Thread.h, 0xFFFFFF, TRUE);
	// �w偂̕\��
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

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

		int enumSet = BOSSATTACK_MINISPIDER_DROP;
		if (g_rightning.cnt > 1800)
			enumSet = 1;

		attackSelect = InputRand(BOSSATTACK_MINISPIDER_DROP, BOSSATTACK_MINICLOUD_DROP, enumSet);			//�����ōU�����邩�ړ������邩������

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;												// �N�[���^�C��������
		}
		//else {	// �U�������Ȃ��Ƃ�
		//	moveFlg = BOSSMOVE_SPEEDDOWN;

		//}
	}

	// �o�b�t�@�[�Ɣ�ׂĎG���G�������ĂȂ��Ƃ��͎G���G��������
	if (BossNoAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
		}
	}
	// �o�b�t�@�[�Ɣ�ׂĎG���G�������鎞�G���G��������
	if (BossDropAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
		}
	}
	//// �U�������ōs��
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	//	BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	//}

	// �U��
	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����

		BossAttackMove();	// �{�X�̍U��
	}

	
	//if (g_boss4_Rightning_Cnt >= 1800) {		// �J�E���g���P�̍���Disp�̕����𐧌�
	//	g_boss4_Rightning_Cnt = 1799;
	//}
	// �����𗎂Ƃ��J�E���g
	g_rightning.cnt++;

	Boss_Knock_Down();	// �{�X���|����Ă鏈��
}

void Boss_Lightning_Disp() {
	
	


	//if()
	//g_rightning.cnt = 0;				 // �����܂ł̃J�E���g��������
	//g_boss[g_select_Stage].attackFlg = 0;    // attack�t���O��������
}
void Boss_Lightning_Move() {
	


}
// �{�X�S�̕K�v�ȏ��̏�����
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
	g_boss4_Thread.Boss4_Thread();
}