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
#include "Skill.h"



/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////

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
	//DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	DrawRotaGraph(g_boss4_Cloud.x + ((g_boss4_Cloud.w - g_boss4_Cloud.x) / 2), g_boss4_Cloud.y + ((g_boss4_Cloud.h - g_boss4_Cloud.y) / 2), 1.5f, 0.0, g_pic.thundercloud, TRUE);
	
	// �����̏[�d
	int animeMax = 3;
	static int animeRightning = 0;
	static int animeFrameCnt = 0;
	if (animeFrameCnt++ % 10 == 0)animeRightning++;					// �A�j���[�V�����̐i�s
	if (animeRightning > animeMax)animeRightning = 0;				// �A�j���[�V�����̃��[�v
	DrawRotaGraph(g_boss4_Cloud.x + ((g_boss4_Cloud.w - g_boss4_Cloud.x )/ 2) + 10, g_boss4_Cloud.y + ((g_boss4_Cloud.h - g_boss4_Cloud.y) / 2) - 10, g_rightning.exRate, 0.0, g_pic.boss4_Cloud_Rightning[animeRightning], TRUE);
	// ���̕\��
	if (g_boss4_Thread.dispFlg == TRUE) {
		//DrawBox(g_boss4_Thread.x, g_boss4_Thread.y, g_boss4_Thread.w, g_boss4_Thread.h, 0xFFFFFF, TRUE);
		DrawModiGraph(g_boss4_Thread.x, g_boss4_Thread.y,		// ����̒��_
					g_boss4_Thread.w, g_boss4_Thread.y,			// �E��̒��_
					g_boss4_Thread.w, g_boss4_Thread.h + 50,	// �E���̒��_
					g_boss4_Thread.x, g_boss4_Thread.h + 50,	// �����̒��_
					g_pic.spiderThread, TRUE);
		
	}		
#ifdef DEBUG_BOSS_ON
	DrawFormatString(400, 500, 0x0000FF, "%d\n%d",
	/*g_boss4_Thread.hp*/g_boss4_Cloud.x, g_boss[BOSS_STAGE4].x);
#endif // DEBUG_BOSS_ON

	// �w偂̕\��
	//DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);
	//DrawRotaGraph2(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, 32, 32, 5.0f, DX_PI_F / 180 * 330, g_pic.spiderKids[0], TRUE, FALSE, FALSE);
	const int bossAnime[3] = { 0, 3, 5};
	static int animationStart = bossAnime[0];	// �A�j���[�V�����J�n�ʒu�̏�����
	static int animationLast = bossAnime[1];	// �A�j���[�V�������[�v�̏�����
	static int animecnt = 0;					// �A�j���[�V����������ׂ̃J�E���g
	static int animationCnt = 0;				// �A�j���[�V�����̃J�E���g

	if (animecnt++ % 10 == 0)animationCnt++;					// �A�j���[�V�����̐i�s
	if (animationCnt > animationLast)animationCnt = animationStart;	// �A�j���[�V�����̃��[�v
	if (g_boss4_Thread.dispFlg == FALSE) {						// �{�X���_�E�����Ă�����|�ꂽ�摜�ɍ����ւ�
		animationCnt = 5;
	}
	DrawRotaGraph2(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, 0, 0, 0.6f, 0.0, g_pic.boss_4_1[animationCnt], TRUE, FALSE, FALSE);
	if (g_boss[BOSS_STAGE4].damageFlg == TRUE) {
		Boss_Damage_Disp2(&g_boss[BOSS_STAGE4].damageFlg, g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_pic.boss_4_1[animationCnt], 0.6f);	// �_���[�W��H������Ƃ��̃��[�V����
	}
	//Poison_Trap_Disp();	// �ł̃g���b�v�̕\��
	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// �{�X���U�����Ă����
		BossAttackDisp();	// �{�X�̍U��
	}
#ifdef DEBUG_BOSS_ON
	DrawFormatString(600, 200, 0xFFFFFF, "cnt = %d", g_rightning.cnt);
#endif // DEBUG_BOSS_ON

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

	ThreadMove(&moveFlg);			// �����̎� ��������
	SpiderNoThreadMove(&moveFlg);	// �����̎����؂�Ă���ۂ̏���
}

/*********************************************

* �����ɂ��U��

*/////////////////////////////////////////////
void Boss_Lightning_Disp() {
	
	static int stopCnt = 0;	// ������\�������鎞��

	// g_rightning.x + 526, g_rightning.y + 488
	if (g_rightning.cnt <= 0) {
		DrawRotaGraph2(g_rightning.x, g_rightning.y, 0, 0, 1.0, 0.0, g_pic.boss4_RightningSmash, TRUE);
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

// �����̎��̓�������
void ThreadMove(int *moveFlg) {
	static int noDamegeCnt = 60;		// �_���[�W���󂯕t���Ȃ�����
	const int threadHpHull = 5;			// ���̍ő�g�o

	noDamegeCnt++;

	// �w偂̎����v���C���[�̍U�����󂯂鏈��
	if ((g_boss4_Thread.dispFlg == TRUE)){
		if ( /*(g_player.attackFlg == TRUE)*/
			/*&&*/ SkillMove[g_player.skillFlg - 1](g_boss4_Thread.x, g_boss4_Thread.y,
				BOSS_THREAD_WIDTH, g_boss4_Thread.h - g_boss4_Thread.y + 50) == TRUE ) {

			// �{�X���_�E��
			if (g_boss4_Thread.hp <= 0) {
				g_boss4_Thread.dispFlg = FALSE;
				*moveFlg = BOSSMOVE_DOWN;
			}
			// �{�X�͂܂��ς��Ă���
			else if (noDamegeCnt > 30) {
				g_boss4_Thread.hp--;
				noDamegeCnt = 0;
			}
			
		}
	}

	// �{�X��HP �̏�����
	if (g_boss4_Thread.dispFlg == FALSE) {
		g_boss4_Thread.hp = threadHpHull;
	}
}

// �����؂�ꂽ���̒w偂̓���
void SpiderNoThreadMove(int *moveFlg) {
	static bool bossDownFlg = TRUE;		// TRUE:�{�X���_�E�����Ă�����	FALSE:�w偂����������
	static int cloudCnt = 0;

	//if (g_boss4_Thread.dispFlg == FALSE) {
	//	//bossDownFlg = TRUE;
	//}

	// �����؂�Ēw偂������A���_���w偂�ǂ������鏈��
	if (g_boss4_Thread.dispFlg == FALSE
		&& bossDownFlg == TRUE) {

		cloudCnt++;

		// ����
		if (g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT <= GROUND) {
			g_boss[BOSS_STAGE4].y += 2;
		}
		// �w偂�����鏈���Ɨ��_���ǂ������鏈��
		else {
			g_boss[BOSS_STAGE4].x -= g_speedLevel - 6;
			if (cloudCnt > 80) {
				g_boss4_Cloud.x -= g_speedLevel + 2;
				g_boss4_Cloud.w -= g_speedLevel + 2;
				g_boss4_Cloud.y += 2;
				g_boss4_Cloud.h += 2;
			}
			if (g_boss4_Cloud.x   < g_boss[BOSS_STAGE4].x + 28) {
				//g_boss4_Cloud.x = g_boss[BOSS_STAGE4].x;
				g_boss4_Thread.ThreadReSet(g_boss4_Cloud.x, g_boss4_Cloud.y);
				//g_boss4_Thread.h = 0;
				cloudCnt = 0;
				bossDownFlg = FALSE;
				g_boss4_Thread.dispFlg = TRUE;
			}
		}

	}

	// �w偂Ɨ��_
	if (bossDownFlg == FALSE) {
		if (g_boss[BOSS_STAGE4].y  > 331) {
			g_boss[BOSS_STAGE4].y -= 2;
			if (g_boss4_Cloud.y > 36) {
				g_boss4_Cloud.y -= 2;
				g_boss4_Cloud.h -= 2;
			}
		}
		else if (g_boss4_Cloud.x < 868) {
				g_boss4_Cloud.x += 2;
				g_boss4_Cloud.w += 2;
				if(g_boss[BOSS_STAGE4].x < 803) {
					g_boss[BOSS_STAGE4].x += 2;
				}
			g_boss4_Thread.ThreadReSet(g_boss4_Cloud.x, g_boss4_Cloud.y);
		}
		// �{�X�̕��A
		else {
			bossDownFlg = TRUE;
			*moveFlg = BOSSMOVE_NOMOTION;
		}
	}
}

// �{�X�S�̕K�v�ȏ��̏�����
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
	g_boss4_Thread.ThreadInit();
}