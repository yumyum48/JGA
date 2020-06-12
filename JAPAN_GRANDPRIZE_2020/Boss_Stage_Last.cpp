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
#include "Rain.h"
#include <math.h>
#include "Skill.h"

/*********************************************

* �}�N���̐錾

*/////////////////////////////////////////////
#define BOSS_UPMAX		  (183)	// �{�X�̍ő卂�x��Y���W
#define LAST_BOSSDISP_MAX (2)	// �P��ʂɏo�Ă���ւ̍ő吔
/*********************************************

* �񋓑̂̐錾

*/////////////////////////////////////////////

/*********************************************

* �\���̂̐錾

*/////////////////////////////////////////////


/*********************************************

* �萔�̐錾

*/////////////////////////////////////////////

/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////

//bool g_lastBoss_SevenSnakeAttackFlg[YAMATANO_NECK];	// ���X�{�X�O�̂V�̂̎ւ̍U���t���O TRUE: �U���� FALSE:�U�����Ă��Ȃ�
/*********************************************

* ���X�{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage_Last() {
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

	// �{�X�{�̂̕\��
	//DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);

	// �{�X�̖{�̂�������7�̂̕\��
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg != LASTBOOS_OFF && g_boss_Yamatano[i].popflg != LASTBOSS_KILL) {
			DrawBox(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h, 0x00FFFF, TRUE);

		}
	}

	// ���X�{�X�{�̂̕`��
	if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGELAST_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGELAST_HEIGHT, 0x00FFFF, TRUE);
	}
	// ���C���[�I�ȈӖ������Ń}�b�v���ĕ`��
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}

	// ���X�{�X�̖{�̂����Ȃ�������
	if (g_boss[BOSS_LASTBOSS].popflg == FALSE) {
		YmatanoSeven_Disp();
	}
	// ���X�{�X�̖{�̂�������
	else if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		LastBoss_Disp();
	}
																											
	DrawFormatString(300, 500, 0xFF00000, "coolTime = %d\nattackFlg = %d", g_boss[BOSS_LASTBOSS].coolTime, g_boss[BOSS_LASTBOSS].attackFlg);
}

// ����
void BossMove_Stage_Last() {	

	// �{�X�����Ȃ�������
	if (g_boss[BOSS_LASTBOSS].popflg == FALSE) {
		YmatanoSeven_Move();
	}
	// �{�X��������
	else if (g_boss[BOSS_LASTBOSS].popflg == TRUE) {
		LastBoss_Move();
	}

}
/*********************************************

* ���}�^�m�I���`�{��

*/////////////////////////////////////////////
// �\�� // ���C���[�̊֌W�ōU���̂�
void LastBoss_Disp() {
	if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {
		Last_Boss_Attack_Disp[g_boss[BOSS_LASTBOSS].attackFlg](g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, &g_boss[BOSS_LASTBOSS].attackFlg, &g_boss[BOSS_LASTBOSS].coolTime);	// ���X�{�X�O�ւ̍U��}
	}
}

// ����
void LastBoss_Move() {

	if ((g_boss[BOSS_LASTBOSS].coolTime++ > 120)									// �d������
		&& (g_boss[BOSS_LASTBOSS].attackFlg == 0)) {								// �{�X���U�����Ă��Ȃ�

		g_boss[BOSS_LASTBOSS].attackFlg = 1 + InputHyperRand(LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_SHADOW);							//�����ōU�����邩�ړ������邩������@+ �P�͂O���g��Ȃ�����
	

		if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {	// �{�X�̍U�� �Y�����́[�P�͓Y�������킹
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_ENEMY_DROP + 1) {		// �����G���G���������鎞�A����������
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].walk.BossArea_WlakInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}

			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINISPIDER_DROP + 1) {	// �~�j�X�p�C�_�[����������ہA����������
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].spider.BossArea_SpiderInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINICLOUD_DROP + 1) {	// �~�j�X�p�C�_�[����������ہA����������
				for (int j = 0; j < ENEMY_MAX; j++) {
					g_enemy[j].cloud.BossArea_CloudInit(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y);
				}
			}
			if (g_boss[BOSS_LASTBOSS].attackFlg == LAST_BOSSATTACK_MINIKURAGE + 1) {	// �~�j�N���Q����������ہA����������
				for (int i = 0; i < KURAGE_MAX; i++) {
					g_enemy[i].kurage.BossArea_KurageInit(g_boss[BOSS_LASTBOSS].y);
					g_enemy[i].kurage.flg = TRUE;
				}
			}
		}
		
	}
	// �U��
	if (g_boss[BOSS_LASTBOSS].attackFlg != 0) {
		Last_Boss_Attack_Move[g_boss[BOSS_LASTBOSS].attackFlg](g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, &g_boss[BOSS_LASTBOSS].attackFlg, &g_boss[BOSS_LASTBOSS].coolTime);	// ���X�{�X�O�ւ̍U��}

	}

}
/*********************************************

* ���}�^�m�I���`�{�̈ȊO��7��

*/////////////////////////////////////////////
// �\�� // ���C���[�̊֌W�ōU���̕\���̂�
void YmatanoSeven_Disp() {
	// ���X�{�X�O�ւ̍U���̕\��
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].sevenAttackFlg == TRUE) {
			Last_Yamatano_Boss_Attack_Disp[g_boss_Yamatano[i].attackFlg](g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, &g_boss_Yamatano[i].sevenAttackFlg, &g_boss_Yamatano[i].coolTime);	// ���X�{�X�O�ւ̍U��
		}
	}
}
// ����
void YmatanoSeven_Move() {
	//	0 �����E�O�E
		//	1 �G���ψ�
		//	3 �J�G��
		//	4 �w�
		//	5 �_
		//	6 �N���Q
		//	7 ���g
		//	8 ������

		// 7�̂̎֏o���t���O���Ǘ�
	Last_Boss_SnakeDispFlg_Managar();

	// �ւ��|����鏈��
	Boss_Snake_Knockdown();

	// �V�̂̎ւ̍U�����I
	{

		static int attackFlg[YAMATANO_NECK] = { 0, 0, 0, 0, 0, 0, 0 };							// attack�t���O��������
		int bossAttackSet[][3] = { {LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_WATER_BULLET, LAST_BOSSATTACK_WATER_BULLET},	// ��̖ڂ̎�
								   {LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_ENEMY_DROP, LAST_BOSSATTACK_ENEMY_DROP},		// �Q�̖ڂ̎�
								   {LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_LONGTON, LAST_BOSSATTACK_LONGTON},					// �R�̖ڂ̎�
								   {LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINISPIDER_DROP, LAST_BOSSATTACK_MINISPIDER_DROP},	// �S�̖ڂ̎�
								   {LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINICLOUD_DROP, LAST_BOSSATTACK_MINICLOUD_DROP},	// �T�̖ڂ̎�
								   {LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_MINIKURAGE, LAST_BOSSATTACK_MINIKURAGE},				// �U�̖ڂ̎�
								   {LAST_BOSSATTACK_SHADOW, LAST_BOSSATTACK_SHADOW, LAST_BOSSATTACK_SHADOW} };							// �V�̖ڂ̎�
		for (int i = 0; i < YAMATANO_NECK; i++) {
			if ((g_boss_Yamatano[i].popflg == LASTBOSS_ON)
				&& (g_boss_Yamatano[i].sevenAttackFlg == FALSE)) {
				if (g_boss_Yamatano[i].coolTime++ > 360) {	// �d�����Ԉ��ȏ�


					attackFlg[i] = InputRand(bossAttackSet[i][0], bossAttackSet[i][1], bossAttackSet[i][2]);			//�����łǂ̍U�������邩������


					if (attackFlg[i] == LAST_BOSSATTACK_ENEMY_DROP) {		// �����G���G���������鎞�A����������
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].walk.BossArea_WlakInit(g_boss_Yamatano[1].x, g_boss_Yamatano[1].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINISPIDER_DROP) {	// �~�j�X�p�C�_�[����������ہA����������
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].spider.BossArea_SpiderInit(g_boss_Yamatano[3].x, g_boss_Yamatano[3].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINICLOUD_DROP) {	// �~�j�X�p�C�_�[����������ہA����������
						for (int j = 0; j < ENEMY_MAX; j++) {
							g_enemy[j].cloud.BossArea_CloudInit(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y);
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_MINIKURAGE) {	// �~�j�N���Q����������ہA����������
						for (int i = 0; i < KURAGE_MAX; i++) {
							g_enemy[i].kurage.BossArea_KurageInit(g_boss_Yamatano[i].y);
							g_enemy[i].kurage.flg = TRUE;
						}
					}
					if (attackFlg[i] == LAST_BOSSATTACK_SHADOW) {	// �e����������ہA����������
						g_boss_shadow.ShadowInit(g_boss_Yamatano[i].x, (GROUND - g_boss_Yamatano[i].h), TRUE);
					}

					g_boss_Yamatano[i].attackFlg = attackFlg[i];														// �U������ꍇ�A�t���O�ɑΉ���������������
					g_boss_Yamatano[i].sevenAttackFlg = TRUE;															// �Y�����Ŏւ̍U���t���O���Ȃ��ł���U���t���O���I����

				}
			}
		}
	}

	// ���X�{�X�O�̂V�̂̎ւ̍U��
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].sevenAttackFlg == TRUE) {
			Last_Yamatano_Boss_Attack_Move[g_boss_Yamatano[i].attackFlg](g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, &g_boss_Yamatano[i].sevenAttackFlg, &g_boss_Yamatano[i].coolTime);	// ���X�{�X�O�ւ̍U��
		}
	}
	// �֒ǉ��V�[��
	Snake_Add_To_Anime();
	// �{�X���|�����
	Boss_Knock_Down();
}
/*********************************************

* �֒ǉ��V�[��

*/////////////////////////////////////////////
void Snake_Add_To_Anime() {
	for (int i = 0; i < YAMATANO_NECK; i++) {	// �֒ǉ��V�[��
		if (g_boss_Yamatano[i].attackFlg == 0)	// �������Ă��Ȃ�������
			if (g_boss_Yamatano[i].popflg == LASTBOSS_MINION) {
				static bool upFlg[YAMATANO_NECK] = { TRUE, TRUE, TRUE, TRUE, TRUE, TRUE, TRUE };	// ��ɏオ��t���O
				int moveX = 2;					// �{�X��X���h�炵�p
				int moveY = 8;					// �{�X�̎�̗������x
				/*if (cnt++ > 5 && cnt <= 10) {
					moveX = -2;
				}
				else if (cnt > 10) {
					cnt = 0;
				}*/
				if ((g_boss_Yamatano[i].y > (BOSS_UPMAX - 50))
					&& (upFlg[i] == TRUE)) {
					g_boss_Yamatano[i].y -= moveY;			// ��ɏオ���Ă���
				}
				else if (g_boss_Yamatano[i].y <= (BOSS_UPMAX - 50)) {
					upFlg[i] = FALSE;
				}
				if ((g_boss_Yamatano[i].y < BOSS_UPMAX)
					&& (upFlg[i] == FALSE)) {
					g_boss_Yamatano[i].y += moveY / 2;			// ���ɉ������Ă���(�������)

				}
				else if ((upFlg[i] == FALSE)					// ����̈ʒu�܂ŗ�����
					&& (g_boss_Yamatano[i].y >= BOSS_UPMAX))
				{

					for (int i = 0; i < YAMATANO_NECK; i++) {	// �A�b�v�t���O������������
						upFlg[i] = TRUE;
					}
					g_boss_Yamatano[i].popflg = LASTBOSS_ON;	// �o���t���O���X�e���o�C��Ԃ�
				}
			}
	}
}
/*********************************************

* �ւ̏o���t���O�Ǘ�

*/////////////////////////////////////////////
void Last_Boss_SnakeDispFlg_Managar() {
	if (g_lastBoss_StartAnimeFlg != TRUE) {
		int cnt = 0;		// �\������Ă���{�X�̃J�E���g
		int killCnt = 0;	// �|����Ă���{�X�̃J�E���g
		int offCnt = 0;		// �\������Ă��Ȃ��{�X�̃J�E���g
		int tagBuf = 0;		// �\������Ă���ւ̃^�O���m�F
		for (int i = 0; i < YAMATANO_NECK; i++) {
			if( (g_boss_Yamatano[i].popflg == LASTBOSS_ON) 
			|| (g_boss_Yamatano[i].popflg == LASTBOSS_MINION) ){
				cnt++;			// �\������Ă���{�X�̃J�E���g
				tagBuf = g_boss_Yamatano[i].tag;	// �^�O���L��
			}
			if (g_boss_Yamatano[i].popflg == LASTBOSS_KILL) {
				killCnt++;		// �|���ꂽ�{�X�̃J�E���g
			}
			// �\������Ă��Ȃ��{�X�̃J�E���g
			offCnt = YAMATANO_NECK - (cnt + killCnt);
		}

		if (cnt < 2) {
			int disp = LAST_BOSSDISP_MAX - cnt;	// �o��������ւ̐����v�Z

			for (int i = 0; i < disp; i++) {
				int next = YAMATANO_NECK - offCnt;	// ���̃{�X�̓Y����
				if (next >= 7) {
					break;
				}
				if (disp == 1) {
					if (tagBuf == TAG_BOSS_LEFT) {
						g_boss_Yamatano[next].lasbossInit(2);	// �����ɐݒu
					}
					else {
						g_boss_Yamatano[next].lasbossInit(3);	// �E���ɐݒu
					}
					g_boss_Yamatano[next].popflg = LASTBOSS_MINION;
					
				}
				else if (disp == 2) {
					//if()
					g_boss_Yamatano[next].lasbossInit(i + 2);	// ���E�ɐݒu 2�́A�Y�������킹(Y���W��n�ʂƓ������W�ɏ���������̂�)
					g_boss_Yamatano[next].popflg = LASTBOSS_MINION;
					
				}
				offCnt--;
			}

			// �V�̂̎ւ��|����Ă����烉�X�{�X������
			if (killCnt >= YAMATANO_NECK) {
				g_boss[BOSS_LASTBOSS].popflg = TRUE;

			}
		}
	}
}
/*********************************************

* �ւ��|����鏈��

*/////////////////////////////////////////////
void Boss_Snake_Knockdown() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON /*|| g_boss_Yamatano[i].popflg == LASTBOSS_MINIKILL*/) {
			if (g_boss_Yamatano[i].damageFlg == TRUE) {
				// ��e���[�V�����I�������t���O��FALSE
				g_boss_Yamatano[i].damageFlg = FALSE;
			}
			else if (g_boss_Yamatano[i].hp <= 0) {		// hp���O�������ꍇ�A�{�X�̎�𗎂Ƃ��Ď��ɓ���ւ��鏀��������
				
				if (g_boss_Yamatano[i].y < GROUND) {
					//g_boss_Yamatano[i].popflg = LASTBOSS_MINIKILL;	// �|�������ǁA�܂���ʂɂ�����
					static int cnt;					// �h�炵�Ŏg���t���[���p�J�E���g
					int moveX = 2;					// �{�X��X���h�炵�p
					int moveY = 5;					// �{�X�̎�̗������x
					if (cnt++ > 5 && cnt <= 10) {
						moveX = -2;
					}
					else if (cnt > 10) {
						cnt = 0;
					}

					g_boss_Yamatano[i].y += moveY;			// ���ɗ����Ă���
					g_boss_Yamatano[i].x += moveX;	// ���E�ɗh��Ȃ���
				}
				else {
					g_boss_Yamatano[i].popflg = LASTBOSS_KILL;		// �������������{�X�̃t���O���I�t��
				}
			}
		}
	}
}
/*********************************************

* �ւ̏o���A�j���[�V����	// �Q�[���v���C�̍ŏヌ�C���[�Œu���Ă܂��I

*/////////////////////////////////////////////
void LastBossRightNingAnime() {
	if (g_select_Stage == BOSS_LASTBOSS) {

		if (g_lastBoss_StartAnimeFlg == TRUE) {
			//RainDisp();
			static int trans = 0;	// �����̓����x
			static int cnt = 0;		// �A�j���[�V�����̃J�E���g
			SetDrawBlendMode(DX_BLENDMODE_ALPHA, trans);	// �����x��������
			DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0xFFFFFF, true);	// ����
			SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);		// �����x��߂�
			if (cnt < 3) {				// �R�񗋌����������甲����
				if (trans++ == 50) {	// ���񂾂�ƌ����Ă���
					trans = 230;		// ��C�ɂ҂��[��ƌ��点��
				}
				if (trans >= 240) {		// �ҁ[����ƌ��点�ď�����������@
					trans = 0;			// �܂����񂾂�ƌ��点��悤�ɏ�����
					cnt++;				// �������������񐔂��L�^
				}
			}
			else if (cnt != 99) {			// �ł����������������Ă��Ȃ������珈��
				trans = 255;			// �ł����������𗎂Ƃ�
				cnt = 99;				// �J�E���g���X�X�Œ��
			}
			if (cnt == 99) {			// �J�E���g���X�X�Œ�̎�(������ł��I������)
				trans -= 1;				// �����x���グ�Ă���
				for (int i = 0; i < LAST_BOSSDISP_MAX; i++) {	// �{�X�̏o���t���O���I����
					g_boss_Yamatano[i].popflg = LASTBOSS_ON;
				}
				if (trans <= 0) {
					g_lastBoss_StartAnimeFlg = FALSE;	// �{�X���悭������悤�ɂȂ�����A�j���[�V�����I��
				}
			}
		}
	}
}

/*********************************************

* ���X�{�X�O�̂V�̂̎ւ̏��̏�����

*/////////////////////////////////////////////
void lasbossInfo::lasbossInit(int num) {					// ���X�{�X�̖{�̈ȊO(7�̂̏�����)
		hp = 1;						 // Hp�̏�����
		attackFlg = 0;				 // �Ȃ�̍U�������Ă��邩�̃t���O
		popflg = LASTBOOS_OFF;       // ��ʂɂ��邩���Ȃ����A�Ƃǂ߂��h���邩�ǂ����̃t���O
		coolTime = 0;				 // �d������
		damageFlg = FALSE;			 // �_���[�W��H����Ă��邩�ǂ����̃t���O
		sevenAttackFlg = FALSE;
		w = 230;					// ���̏����ʒu
		h = 490;					// �����̏����ʒu
		switch (num)
		{
		case 0:
			x = 998;				// X���W�̏����ʒu
			y = 183;				// Y���W�̏����ʒu
			//y = 0;				// Y���W�̏����ʒu
			tag = TAG_BOSS_RIGHT;	// ���ɂ���
			popflg = LASTBOOS_OFF;		// �o���t���O���I��
			break;					// �u���C�N
		case 1:
			x = 718;				// X���W�̏����ʒu
			y = 183;				// Y���W�̏����ʒu
			//y = 0;				// Y���W�̏����ʒu
			tag = TAG_BOSS_LEFT;	// �E�ɂ���
			popflg = LASTBOOS_OFF;		// �o���t���O���I��
			break;					// �u���C�N
		case 2:
			x = 998;				// X���W�̏����ʒu
			y = GROUND;				// Y���W�̏����ʒu
			//y = 0;				// Y���W�̏����ʒu
			tag = TAG_BOSS_RIGHT;	// ���ɂ���
			popflg = LASTBOOS_OFF;		// �o���t���O���I��
			break;					// �u���C�N
		case 3:
			x = 718;				// X���W�̏����ʒu
			y = GROUND;				// Y���W�̏����ʒu
			//y = 0;				// Y���W�̏����ʒu
			w = 230;				// ���̏����ʒu
			h = 490;				// �����̏����ʒu
			tag = TAG_BOSS_LEFT;	// �E�ɂ���
			popflg = LASTBOOS_OFF;		// �o���t���O���I��
			break;					// �u���C�N
		//case 2:
		//	x = 438;				// X���W�̏����ʒu
		//	y = 183;				// Y���W�̏����ʒu
		//	//y = 0;				// Y���W�̏����ʒu
		//	w = 230;				// ���̏����ʒu
		//	h = 490;				// �����̏����ʒu
		//	//popflg = TRUE;		// �o���t���O���I��
		//	break;					// �u���C�N
		default:

			break;
		}
	
}

/*********************************************

* ���X�{�X�̏�����

*/////////////////////////////////////////////
void LastBossInit() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		g_boss_Yamatano[i].lasbossInit(i);
	}
}
/**************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
**********************************************														   ********************************************
*********************************					���X�{�X�̍U����i!!!!!!�����Â炢����񂩂��������I			*******************************
**********************************************														   ********************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
***************************************************************************************************************************************************
**************************************************************************************************************************************************/


/**************************************************************************************************************************************************

* �{�X�����e�ōU��������֐�

*/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// ���e�̕`��
void Last_Boss_Attack_WaterBullet_Disp(int bx, int by, int*boss_AttackFlg, int* coolTime) {
	static int animationMax = 3;				// �A�j���[�V����
	static int anime = 0;						// �A�j������
	static int time = 0;						// �o�ߎ���
	static int startX = bx,
		startY = by + 100;	// ���e�̏����ʒu
	static int moveX = 0, moveY = 0;			// ���e�̈ړ���
	static int noDamegeCnt = 60;				// �_���[�W���󂯕t���Ȃ�����
	static bool attackFlg = FALSE;				// �U�����f�t���O	 treu:�U����  false:���U��

	// �t���[���P�ʂ̔�e���̒���
	noDamegeCnt++;

	// �v���C���[�ɐ��e�������������̏��� 
	if (noDamegeCnt >= 60
		&& (PlayerHitCheck(startX + moveX - 40, startY + moveY + 0,
			startX + moveX + 40, startY + moveY - 20) == TRUE)) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 200) {
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}
	}

	// ���e����ʊO�ɏo���Ƃ��̏���
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		*boss_AttackFlg = FALSE;
		*coolTime = 120;
	}

	// ���e���؂�ꂽ���̏���
	if ((g_player.attackFlg == TRUE)
		&& (noDamegeCnt >= 30)
		&& (*SkillMove[g_player.skillFlg - 1])(startX + moveX - 40, startY + moveY - 20, 65, 55) == TRUE) {
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 20) {
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}

	}

	// ���e�̃A�j���[�V����
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// ���e�̕\��
	if (attackFlg == FALSE) {
	/*	moveX -= 7.5;
		moveY += 2.5;*/
		moveX -= 10.5;
		moveY += 4.5;
		/*moveX -= 3.0;
		moveY += 1.0;*/
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[anime], TRUE, FALSE);
		/*DrawBox(startX + moveX - 40, startY + moveY - 20,
			startX + moveX + 25, startY + moveY + 35, 0xFF0000, FALSE);*/
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
		*boss_AttackFlg = FALSE;
		*coolTime = 120;
	}
	// �f�o�b�O
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
}

// ���e�̓����I�ȓ���
void Last_Boss_Attack_WaterBullet_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

}
/****************************************************************************************************************************************************

* �{�X���ア�G���o���U��������֐�

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// �����ア�G���o��(�\��)

void Last_Boss_Attack_BossEnemyDrop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// ���ɏo�Ă���G�l�~�[�̍ő吔
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// �o�������G�l�~�[�̗v�f�ԍ�
	// �N�[���^�C��
	if (++stayTime > 60) {
		// �G�l�~�[�̏o���t���O���I���ɂ���

		if (g_enemy[enemy_cnt].walk.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].walk.flg = TRUE;
			stayTime = 0;

			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}

	// �G���G�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// �A�j���[�V�����̃J�E���g
		if (time++ % 8 == 0) {
			g_enemy[i].walk.anime++;

		}

		// �A�j���[�V�����̏�����
		if (g_enemy[i].walk.anime > animation_Max)g_enemy[i].walk.anime = 0;


		if (g_enemy[i].walk.flg == TRUE)        // �G���G�̕`��
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}


	// �G���G���|���ꂽ�����m�F
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].walk.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// �o�������G���G���S�ē|����Ă�����U���I��
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 320;

			enemyDropCnt = 0;                        // �G�l�~�[���o�����񐔂�������
			enemy_cnt = 0;							 // �G�l�~�[�̏o�������񐔂�������
			enemy_dispFlg_Buf[0] = { FALSE };        // �G�l�~�[�̏o���t���O�o�b�t�@�[��������
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// �G�̏����A�j���[�V����
	EnemyEvaporation();
}
// �ア�G���o��(����(�����蔻��Ȃ�))
void Last_Boss_Attack_BossEnemyDrop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // �����G���G�̍ő吔��


		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= (g_speedLevel - 3);		// �����G���G�̈ړ�

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].walk.x + ENEMY_WIDTH < 0) {			// ��ʊO�ւ����Ə�����

			g_enemy[i].walk.BossArea_WlakInit(bx, by);
			//g_enemy[i].walk.flg = TRUE;
		}


	}
}
/****************************************************************************************************************************************************

* �{�X���Ôg���o��

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//void Last_Boss_Attack_GenerateWave_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
//	const float gravity = 1;				// �W�����v�Ɋ|����d��
//	const int rise = 3;						// �W�����v���̏㏸��
//	static int animationMax[2] = { 0, 0 };	// �A�j���[�V�����Ō��	0:�{�X�W�����v	1:�Ôg
//	static int anime[2] = { 0, 0 };			// ���ݕ\�����Ă���摜	0:�W�����v  1:�Ôg
//	//static int g_noDamegeCnt = 60;			// �_���[�W���󂯕t���Ȃ�����
//	static int time = 0;					// �A�j���[�V�����p���ԕϐ�
//	static float moveY = 0;					// �d�͂̉��Z�p�ϐ�
//	static bool jumpFlg = FALSE;			// �{�X���W�����v�ς݂��̔��f�p�ϐ�	TRUE:�W�����v�ς� 
//
//	// �{�X���W�����v����A�j���[�V����
//	if (g_wave.dispFlg == FALSE) {
//
//		// �A�j���[�V�����̉��Z
//		if (time++ % 12 == 11)anime[0]++;
//		if (anime[0] > animationMax[0])anime[0] = 0;
//
//		if (anime[0] < 1
//			&& jumpFlg == FALSE) {
//			g_boss[BOSS_STAGE2].x -= g_speedLevel;
//		}
//		else {
//			jumpFlg = TRUE;
//		}
//
//		// �W�����v���̋���
//		if (jumpFlg == TRUE) {
//			moveY += gravity;
//
//			if (g_boss[BOSS_STAGE2].y <= 397) {
//				g_boss[BOSS_STAGE2].x += g_speedLevel;
//				g_boss[BOSS_STAGE2].y -= rise + moveY;
//			}
//			if (g_boss[BOSS_STAGE2].y > 397) {
//				g_boss[BOSS_STAGE2].y = 397;
//				g_wave.dispFlg = TRUE;			// �Ôg�𔭐�
//			}
//		}
//
//	}
//
//	// �Ôg�̃A�j���[�V����
//	if (g_wave.dispFlg == TRUE) {
//		g_wave.x -= g_speedLevel;
//
//		// �Ôg�̕`��
//		DrawBox(g_wave.x, g_wave.y,
//			g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT, 0x0000FF, TRUE);
//
//		// �Ôg���v���C���[�ɓ��������ۂ̏���
//		if (g_noDamageCnt >= 60
//			&& PlayerHitCheck(g_wave.x, g_wave.y,
//				g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT) == 1) {
//
//			g_noDamageCnt = 0;
//			if (g_player.barrierFlg == FALSE) --g_player.hp;
//			else g_player.barrierFlg = FALSE;
//			g_boss[BOSS_STAGE2].attackFlg = 0;
//		}
//
//		// �Ôg����ʊO�ɏo�鏈��
//		if (g_wave.x + BOSS_WAVE_WIDTH < 0) {
//			jumpFlg = FALSE;
//			g_wave.dispFlg = FALSE;
//			g_boss[BOSS_STAGE2].attackFlg = 0;
//		}
//	}
//
//}
//void Last_Boss_Attack_GenerateWave_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
//	
//}
/*********************************************

* �J�G���̃{�X�����L�΂��U��

*/////////////////////////////////////////////
void Last_Boss_Attack_BossLongTon_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int plas = 0;			// �������Ă���

	// �{�X�̐�̍��W�̏�����
	g_boss3_Ton.Boss3_TonInit(bx, by + g_boss_Yamatano[2].h / 2);
	// �{�X�̐�̕��ƍ����̏�����
	int tonW = g_boss3_Ton.x + plas;
	int tonH = g_boss3_Ton.y + BOSS_TON_HEIGHT;

	DrawFormatString(500, 500, 0x0000FF, "plas=%d\tonH=%d", plas, tonH);
	// ��̉摜
	DrawModiGraph(tonW, g_boss3_Ton.y,	// ����
		g_boss3_Ton.x, g_boss3_Ton.y,					// �E��
		g_boss3_Ton.x, tonH,			// �E��
		tonW, tonH,		// ����
		g_pic.bossTongue, TRUE);
	//DrawBox(g_boss3_Ton.x, g_boss3_Ton.y, tonW, tonH, 0xFFFF00, TRUE);

	static bool tonFlg = TRUE;	// ���L�΂��t���O

	// ��̉摜���������΂�����
	if (tonW > -100 && tonFlg == TRUE) {
		plas -= 5;							// ���L�΂�
	}
	else if(tonFlg == TRUE){

		tonW = 0;							// ����Œ�
		tonFlg = FALSE;
	}
	if (plas < 0 && tonFlg == FALSE) {
		plas += 10;							// ���߂�
	}
	else if(tonFlg == FALSE){
		*boss_AttackFlg = FALSE;		// attack�t���O��������
		*coolTime = 0;					// �N�[���^�C���̏�����
		plas = 0;
		tonFlg = TRUE;
	}

	if (BossDamageCheck(g_boss_Yamatano[2].hp) == TRUE) {		// �{�X���U�����ꂽ��U�����f���ăW�����v���ē�����
		*boss_AttackFlg = FALSE;		// attack�t���O��������
		*coolTime = 0;					// �N�[���^�C���̏�����
		plas = 0;
		tonFlg = TRUE;

		
	}														   // �{�X���v���C���[�ɓ���������A�_���[�W��^���ē�����
	//else if (PlayerHitCheck(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, BOSS_STAGE3_WIDTH, BOSS_STAGE3_HEIGHT) == TRUE) {
	//	if (g_player.barrierFlg == FALSE) --g_player.hp;
	//	else g_player.barrierFlg = FALSE;
	//	g_noDamageCnt = 0;
	//	g_boss[BOSS_STAGE3].attackFlg = 0;		// attack�t���O��������
	//	plas = 0;
	//}

	// �{�X�̐オ�v���C���[�ɓ���������A�_���[�W��^���ē�����		* ������ -10 ���Ă���̂̓v���C���[�ɓ�����Ȃ��ׂ̒���
	if (PlayerHitCheck(g_boss3_Ton.x + plas, g_boss3_Ton.y, (plas * -1), BOSS_TON_HEIGHT - 10) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		g_noDamageCnt = 0;
		*boss_AttackFlg = FALSE;		// attack�t���O��������
		*coolTime = 0;					// �N�[���^�C���̏�����
		plas = 0;
	}
}

void Last_Boss_Attack_BossLongTon_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	//g_boss[BOSS_STAGE3].x -= 2;

	//if (Boss_3_Jump(&coolTime, &boss_JumpFlg, 1) == TRUE) {
	//	g_boss[BOSS_STAGE3].attackFlg = 0;	// attack�t���O���I�t��
	//}
}

/*********************************************

* �~�j�w偂��o��

*/////////////////////////////////////////////
// �\��
void Last_Boss_Attack_MiniSpider_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// ���ɏo�Ă���G�l�~�[�̍ő吔
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// �o�������G�l�~�[�̗v�f�ԍ�
	// �N�[���^�C��
	if (++stayTime > 60) {
		// �G�l�~�[�̏o���t���O���I���ɂ���

		if (g_enemy[enemy_cnt].spider.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].spider.flg = TRUE;
			stayTime = 0;

			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}

	// �G���G�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// �A�j���[�V�����̃J�E���g
		if (time++ % 8 == 0) {
			g_enemy[i].spider.anime++;

		}

		// �A�j���[�V�����̏�����
		if (g_enemy[i].spider.anime > animation_Max)g_enemy[i].spider.anime = 0;


		if (g_enemy[i].spider.flg == TRUE)        // �G���G�̕`��
			DrawRotaGraph2(g_enemy[i].spider.x, g_enemy[i].spider.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].spider.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// �G���G���|���ꂽ�����m�F
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].spider.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// �o�������G���G���S�ē|����Ă�����U���I��
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 300;
			enemyDropCnt = 0;                        // �G�l�~�[���o�����񐔂�������
			enemy_cnt = 0;							 // �G�l�~�[�̏o�������񐔂�������
			enemy_dispFlg_Buf[0] = { FALSE };        // �G�l�~�[�̏o���t���O�o�b�t�@�[��������
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// �G�̏����A�j���[�V����
	EnemyEvaporation();
}

// ����
void Last_Boss_Attack_MiniSpider_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {


	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // �~�j�w偂̍ő吔��


		if (g_enemy[i].spider.flg == TRUE) {
			g_enemy[i].spider.x -= (g_speedLevel - 3);		// �~�j�w偂̈ړ�

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].spider.x + ENEMY_WIDTH < 0) {		// ��ʊO�ɂ����Ə�����

			g_enemy[i].spider.BossArea_SpiderInit(bx, by);
			//g_enemy[i].walk.flg = TRUE;
		}
	}
}
/*********************************************

* �~�j�_���o��

*/////////////////////////////////////////////
void Last_Boss_Attack_MiniCloud_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	static int stayTime = 0;
	static int enemyDropCnt = 0;
	const int LAST_AREA_ENEMY_MAX = 1;		// ���ɏo�Ă���G�l�~�[�̍ő吔
	static bool enemy_dispFlg_Buf[LAST_AREA_ENEMY_MAX] = { FALSE };/*{ FALSE, FALSE, FALSE };*/ // 
	static int enemy_cnt = 0;	// �o�������G�l�~�[�̗v�f�ԍ�
	// �N�[���^�C��
	if (++stayTime > 60) {
		// �G�l�~�[�̏o���t���O���I���ɂ���

		if (g_enemy[enemy_cnt].cloud.flg == FALSE && enemy_cnt < LAST_AREA_ENEMY_MAX) {
			g_enemy[enemy_cnt].cloud.flg = TRUE;
			stayTime = 0;

			enemy_dispFlg_Buf[enemy_cnt] = TRUE;
			enemy_cnt++;
		}

	}

	// �G���G�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// �A�j���[�V�����̃J�E���g
		if (time++ % 8 == 0) {
			g_enemy[i].cloud.anime++;

		}

		// �A�j���[�V�����̏�����
		if (g_enemy[i].cloud.anime > animation_Max)g_enemy[i].cloud.anime = 0;


		if (g_enemy[i].cloud.flg == TRUE)        // �G���G�̕`��
			DrawRotaGraph2(g_enemy[i].cloud.x, g_enemy[i].cloud.y,
				0, 0, 0.2, 0.0, g_pic.enemy_fly[g_enemy[i].cloud.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// �G���G���|���ꂽ�����m�F
	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
		if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].cloud.flg == FALSE) {
			enemyDropCnt++;
		}
	}

	// �o�������G���G���S�ē|����Ă�����U���I��
	if (enemyDropCnt >= LAST_AREA_ENEMY_MAX) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			*boss_AttackFlg = FALSE;
			*coolTime = 300;
			enemyDropCnt = 0;                        // �G�l�~�[���o�����񐔂�������
			enemy_cnt = 0;							 // �G�l�~�[�̏o�������񐔂�������
			enemy_dispFlg_Buf[0] = { FALSE };        // �G�l�~�[�̏o���t���O�o�b�t�@�[��������
			//enemy_dispFlg_Buf[1] = { FALSE };
			//enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// �G�̏����A�j���[�V����
	EnemyEvaporation();
}
// ����
void Last_Boss_Attack_MiniCloud_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        // �~�j�_�̍ő吔��


		if (g_enemy[i].cloud.flg == TRUE) {
			g_enemy[i].cloud.x -= (g_speedLevel - 3);	   // �~�j�_���ړ�
			g_enemy[i].cloud.y = (GROUND - ENEMY_HEIGHT) - 200;
			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}

		if (g_enemy[i].cloud.x + ENEMY_WIDTH < 0) {		// �~�j�_���͈͊O�܂ōs���Ə�����

			g_enemy[i].cloud.BossArea_CloudInit(bx, by);

		}
	}
}

/*********************************************

* �����ɂ��U��

*/////////////////////////////////////////////
void Last_Boss_Attack_Lightning_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	//static int stopCnt = 0;	// ������\�������鎞��


	//if (g_rightning.cnt <= 0) {
	//	DrawBox(g_rightning.x, g_rightning.y, g_rightning.x + 526, g_rightning.y + 488, 0x00FFFF, TRUE);
	//	g_rightning.cnt = 0;
	//	stopCnt++;
	//}

	//if (stopCnt >= 90) {
	//	g_rightning.cnt = 0;					 // �����܂ł̃J�E���g��������
	//	g_boss[g_select_Stage].attackFlg = 0;    // attack�t���O��������
	//	stopCnt = 0;							 // �����̕\���J�E���g��������
	//}
}

void Last_Boss_Attack_Lightning_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	/*g_rightning.cnt -= 50;*/
}

/*********************************************

* �~�j�N���Q�ɂ��U��

*/////////////////////////////////////////////
void Last_Boss_MiniKurage_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	// �G���G�̕`��
	for (int i = 0; i < ENEMY_MAX; i++) {

		const int animation_Max = 3;
		static int time = 0;

		// �A�j���[�V�����̃J�E���g
		if (time++ % 8 == 0) {
			g_enemy[i].kurage.anime++;

		}

		// �A�j���[�V�����̏�����
		if (g_enemy[i].kurage.anime > animation_Max)g_enemy[i].kurage.anime = 0;

		if (g_enemy[i].kurage.flg == TRUE) {
			// �G���G�̕`��
			DrawRotaGraph2(g_enemy[i].kurage.x, g_enemy[i].kurage.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].kurage.anime], TRUE);
		}
	}
	// �G�̏����A�j���[�V����
	EnemyEvaporation();
}

void Last_Boss_MiniKurage_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// �~�j�N���Q�̔z�u�����ʒu
	int cnt = 0;						// �G���G���|���ꂽ�����J�E���g
	for (int i = 0; i < KURAGE_MAX; i++) {
		
		if (g_enemy[i].kurage.flg == FALSE) {
			cnt++;						// �|���ꂽ�����J�E���g
			
		}
		if (cnt >= KURAGE_MAX) {		// �J�E���g����萔�ȏ�Ȃ�U���I��
			*boss_AttackFlg = FALSE;
			*coolTime = 120;
		}
	}
	
	// �\������Ă��āA�����|�W�V�����ɂ��Ȃ��G���G�������|�W�Ɉړ�������
	for (int i = 0; i < KURAGE_MAX; i++) {
		if (g_enemy[i].kurage.flg == TRUE) {
			//g_enemy[buf].kurage.x = position[buf].x;
			//g_enemy[buf].kurage.y = position[buf].y;
			float angle;
			angle = atan2((g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x));
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);


		}
	}


	static bool ataackFlg_AirKurage = FALSE;	// �󒆂Ŕ��ł���N���Q�̍U���t���O
	static bool attackFlg_GroundKurage = FALSE;	// �n��Ŕ��ł���N���Q�̍U���t���O
	static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// �N���Q���U���Ŏg���Ă��Ȃ��� TRUE:�g���Ă��� FALSE:�g���Ă��Ȃ�
	static int attackKurageBuf_Air;											// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�󒆍U���p)
	static int attackKurageBuf_Ground;											// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�n��U���p)

	
	// �N���Q�̍U�����Z�b�g
	int attckSet = InputRand(BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_AIR);

	for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
		if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
			ataackFlg_AirKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
			attackKurageCheck[attackKurageBuf_Air] == TRUE;										// �U�����̃t���O���I���ɂ���
			break;																				//�g����N���Q�̗v�f�ԍ���f���o��
		}
	}


	// �{�X���~�j�N���Q�ōU������Ɣ��f����(�n���)
	if ((attckSet == BOSSATTACK_MINIKURAGE_AIR)
		&& (ataackFlg_AirKurage != TRUE)) {	// �󒆂ł̍U�������ĂȂ���

		for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
			if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
				ataackFlg_AirKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
				attackKurageCheck[attackKurageBuf_Air] = TRUE;										// �U�����̃t���O���I���ɂ���
				break;																				//�g����N���Q�̗v�f�ԍ���f���o��
			}
		}
	}

	// �{�X���~�j�N���Q�ōU������Ɣ��f����(�󒆂�)
	if ((attckSet == BOSSATTACK_MINIKURAGE_GROUND)
		&& (attackFlg_GroundKurage != TRUE)) {	// �n��ł̍U�������ĂȂ���
		for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
			if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
				attackFlg_GroundKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
				attackKurageCheck[attackKurageBuf_Ground] = TRUE;										// �U�����̃t���O���I���ɂ���
				break;																				//�g����N���Q�̗v�f�ԍ���f���o��
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
	//	attackFlg_GroundKurage = FALSE;
	//}

	// �󒆂Ń~�j�N���Q���U��������
	if (ataackFlg_AirKurage) {
		Last_BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
	}

	if (attackFlg_GroundKurage) {
		Last_BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
	}

	// �~�j�N���Q�Ƃ̓����蔻��
	KurageHit();	// �q�b�g����ƃv���C���[��Hp����
}

// �~�j�N���Q�̋󒆍U��
void Last_BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage) {


	if (g_enemy[attackKurageBuf_Air].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Air].kurage.BossArea_KurageInit(g_boss_Yamatano[5].y);

		//g_boss_Yamatano[5].attackFlg = 0;
		*ataackFlg_AirKurage = 0;
	}
	else {
		if (g_enemy[attackKurageBuf_Air].kurage.y > (GROUND - ENEMY_HEIGHT) - 200) {
			g_enemy[attackKurageBuf_Air].kurage.y -= 5;
		}
		else {
			g_enemy[attackKurageBuf_Air].kurage.y = (GROUND - ENEMY_HEIGHT) - 200;
			g_enemy[attackKurageBuf_Air].kurage.x -= 10;
		}
	}
}
// �~�j�N���Q�̒n��U��
void Last_BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage) {

	if (g_enemy[attackKurageBuf_Ground].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Ground].kurage.BossArea_KurageInit(g_boss_Yamatano[5].y);
		//g_boss_Yamatano[5].attackFlg = 0;
		*attackFlg_GroundKurage = 0;
	}
	else {
		if (g_enemy[attackKurageBuf_Ground].kurage.y < GROUND - ENEMY_HEIGHT) {
			g_enemy[attackKurageBuf_Ground].kurage.y += 2;
		}
		else {
			g_enemy[attackKurageBuf_Ground].kurage.y = GROUND - ENEMY_HEIGHT;
			g_enemy[attackKurageBuf_Ground].kurage.x -= 10;
		}
	}
}

/*********************************************

* �e���g�ɂ��U��

*/////////////////////////////////////////////
void Last_Boss_Shadow_Attack_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {


	//static int anime = 0;							// �v���C���[�̉摜��ς���
	//static int time = 0;							// �摜��؂�ւ���^�C�~���O����


	//if (++time % 4 == 0) anime++;
	//if (anime < g_shadowMotionReset || anime > g_shadowMaxMotion) anime = g_shadowMotionReset;

	// �e
	//DrawRotaGraph2(g_boss_shadow.x, g_boss_shadow.y, 0, 0, PLAYER_REDUCTION, 0.0, g_pic.player[anime], TRUE, TRUE);
	DrawBox(g_boss_shadow.x, g_boss_shadow.y, g_boss_shadow.x + g_boss_shadow.w, g_boss_shadow.y + g_boss_shadow.h, 0x00F0F0, TRUE);
}

// 

void Last_Boss_Shadow_Attack_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	if (g_boss_shadow.x + g_boss_shadow.w <= 0) {
		*boss_AttackFlg = FALSE;
		*coolTime = 300;
	}
	else {
		g_boss_shadow.x -= 3;
	}
}

/*********************************************

* �������̍U��

*/////////////////////////////////////////////
struct flame : picInfo {
	void flameInit(int bx, int by) {
		x = bx;
		y = by;
		w = 100;
		h = 100;
		
	}
};

void Last_Boss_BrackFire_Disp() {
	
}

void Last_Boss_BrackFire_Move() {

}

/*********************************************

* �֐��|�C���^���킹(��)

*/////////////////////////////////////////////
// �U�������Ȃ�
void Last_Boss_Attack_Null_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	*boss_AttackFlg = 0;
	*coolTime = 300;
}
// �U�������Ȃ�
void Last_Boss_Attack_Null_Move(int bx, int by, int* boss_AttackFlg, int* coolTime) {
	*boss_AttackFlg = 0;
	*coolTime = 300;
}
