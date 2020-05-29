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
#include "HP.h"

#define BOSS_WAVE_WIDTH		200		// �Ôg�̉���
#define BOSS_WAVE_HEIGHT	150		// �Ôg�̏c��

trapInfo g_wave;
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
	
	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// �{�X���U�����Ă����
		//g_boss[BOSS_STAGE2].x = 700;
		//g_boss[BOSS_STAGE2].y = 160;
		BossAttackDisp();	// �{�X�̍U��
	}


}

// ����
void BossMove_Stage2() {
	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	static int attackSelect = 0;							// �{�X�̍U���I��
	static int attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������

	if ((coolTime++ > 60)									// �d������
		&& (g_boss[BOSS_STAGE2].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// �{�X���ړ����Ă��Ȃ����
		
		attackSelect = InputRand(0, BOSSATTACK_ENEMY_DROP, BOSSATTACK_ENEMY_DROP);								//�����ōU�����邩�ړ������邩������

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE2].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;
		}
		else {	// �U�������Ȃ��Ƃ�
			moveFlg = BOSSMOVE_SPEEDDOWN;

		}
	}

	if (attackFlgBuf == 0 && g_boss[BOSS_STAGE2].attackFlg == BOSSATTACK_ENEMY_DROP) {
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			g_enemy[i].walk.BossAreaWlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
		}
	}
	if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

		BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	}

	
	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// �{�X���U�����Ă����
		//g_boss[BOSS_STAGE2].x = 700;
		//g_boss[BOSS_STAGE2].y = 160;
		BossAttackMove();	// �{�X�̍U��
	}


	// �o�b�t�@�[�Ƀ{�X��attack�t���O���i�[
	attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;
	Boss_Knock_Down();
}

// �{�X���W�����v���ĒÔg�𔭐�
void BossGenerateWave() {
	const float gravity = 1;				// �W�����v�Ɋ|����d��
	const int rise = 3;						// �W�����v���̏㏸��
	static int animationMax[2] = { 0, 0 };	// �A�j���[�V�����Ō��	0:�{�X�W�����v	1:�Ôg
	static int anime[2] = { 0, 0 };			// ���ݕ\�����Ă���摜	0:�W�����v  1:�Ôg
	//static int g_noDamegeCnt = 60;			// �_���[�W���󂯕t���Ȃ�����
	static int time = 0;					// �A�j���[�V�����p���ԕϐ�
	static float moveY = 0;					// �d�͂̉��Z�p�ϐ�
	static bool jumpFlg = FALSE;			// �{�X���W�����v�ς݂��̔��f�p�ϐ�	TRUE:�W�����v�ς� 

	// �{�X���W�����v����A�j���[�V����
	if (g_wave.dispFlg == FALSE) {

		// �A�j���[�V�����̉��Z
		if (time++ % 12 == 11)anime[0]++;
		if (anime[0] > animationMax[0])anime[0] = 0;

		if (anime[0] < 1
			&& jumpFlg == FALSE) {
			g_boss[BOSS_STAGE2].x -= g_speedLevel;
		}
		else {
			jumpFlg = TRUE;
		}

		// �W�����v���̋���
		if (jumpFlg == TRUE) {
			moveY += gravity;

			if (g_boss[BOSS_STAGE2].y <= 397) {
				g_boss[BOSS_STAGE2].x += g_speedLevel;
				g_boss[BOSS_STAGE2].y -= rise + moveY;
			}
			if (g_boss[BOSS_STAGE2].y > 397) {
				g_boss[BOSS_STAGE2].y = 397;
				g_wave.dispFlg = TRUE;			// �Ôg�𔭐�
			}
		}

	}

	// �Ôg�̃A�j���[�V����
	if (g_wave.dispFlg == TRUE) {
		g_wave.x -= g_speedLevel;

		// �Ôg�̕`��
		DrawBox(g_wave.x, g_wave.y,
			g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT, 0x0000FF, TRUE);

		// �Ôg���v���C���[�ɓ��������ۂ̏���
		if (g_noDamageCnt >= 60
			&& PlayerHitCheck(g_wave.x, g_wave.y,
				g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT) == 1) {

			g_noDamageCnt = 0;
			if (g_player.barrierFlg == FALSE) --g_player.hp;
			else g_player.barrierFlg = FALSE;
			g_boss[BOSS_STAGE2].attackFlg = 0;
		}

		// �Ôg����ʊO�ɏo�鏈��
		if (g_wave.x + BOSS_WAVE_WIDTH < 0) {
			jumpFlg = FALSE;
			g_wave.dispFlg = FALSE;
			g_boss[BOSS_STAGE2].attackFlg = 0;
		}
	}

}

