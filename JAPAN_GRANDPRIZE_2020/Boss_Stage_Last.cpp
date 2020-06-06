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
/*********************************************

* �}�N���̐錾

*/////////////////////////////////////////////
#define BOSS_UPMAX		  (183)	// �{�X�̍ő卂�x��Y���W
#define LAST_BOSSDISP_MAX (2)	// �l��ʂɏo�Ă���ւ̍ő吔
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

/*********************************************

* ���X�{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage_Last() {
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

	// �{�X�{�̂̕\��
	//DrawBox(g_boss[BOSS_LASTBOSS].x, g_boss[BOSS_LASTBOSS].y, g_boss[BOSS_LASTBOSS].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_LASTBOSS].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);

	// �{�X�̖{�̂�������7�̂̕\��
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON) {
			DrawBox(g_boss_Yamatano[i].x, g_boss_Yamatano[i].y, g_boss_Yamatano[i].x + g_boss_Yamatano[i].w, g_boss_Yamatano[i].y + g_boss_Yamatano[i].h, 0x00FFFF, TRUE);

		}
	}

	// ���C���[�I�ȈӖ������Ń}�b�v���ĕ`��
	for (int i = 0; i < SCROLL_MAX; i++) {
		DrawRotaGraph2(g_map[i].x, g_map[i].y, 0, 0, 2.0, 0.0, g_pic.map[(SCROLL_MAX * g_select_Stage) + i], TRUE);
	}

	
}

// ����
void BossMove_Stage_Last() {

	//	0 �����E�O�E
	//	1 �G���ψ�
	//	3 �J�G��
	//	4 �w�
	//	5 �_
	//	6 �N���Q
	//	7 ���g
	//	8 ������

	// �ւ��|����鏈��
	Boss_Snake_Knockdown();
}
/*********************************************

* �ւ̏o���A�j���[�V����	// �Q�[���v���C�̍ŏヌ�C���[�Œu���Ă܂��I

*/////////////////////////////////////////////
void LastBossRightNingAnime() {
	if (g_select_Stage == BOSS_LASTBOSS) {
		static bool startFlg = TRUE;	// �o���A�j���[�V�����p�̃t���O�@TRUE:�o���A�j���[�V���������� FALSE:�o���A�j���[�V���������Ȃ�

		if (startFlg == TRUE) {
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
					startFlg = FALSE;	// �{�X���悭������悤�ɂȂ�����A�j���[�V�����I��

				}
			}
		}
		else {
			/*	if (g_boss[BOSS_LASTBOSS].hp <= 0) {	// �o���A�j���[�V����������
					startFlg = TRUE;
				}*/
		}
	}
}
/*********************************************

* �ւ��|����鏈��

*/////////////////////////////////////////////
void Boss_Snake_Knockdown() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		if (g_boss_Yamatano[i].popflg == LASTBOSS_ON) {
			if (g_boss_Yamatano[i].damageFlg == TRUE) {
				// ��e���[�V�����I�������t���O��FALSE
				g_boss_Yamatano[i].damageFlg = FALSE;
			}
			else if (g_boss_Yamatano[i].hp <= 0) {		// hp���O�������ꍇ�A�{�X�̎�𗎂Ƃ��Ď��ɓ���ւ��鏀��������
				if (g_boss_Yamatano[i].y < GROUND) {
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
void lasbossInfo::lasbossInit(int num) {// ���X�{�X�̖{�̈ȊO(7�̂̏�����)
		hp = 1;				  // Hp�̏�����
		attackFlg = 0;		  // �Ȃ�̍U�������Ă��邩�̃t���O
		popflg = LASTBOOS_OFF;       // ��ʂɂ��邩���Ȃ����A�Ƃǂ߂��h���邩�ǂ����̃t���O
		coolTime = 0;		  // �d������
		damageFlg = FALSE;	  // �_���[�W��H����Ă��邩�ǂ����̃t���O
		switch (num)
		{
		case 0:
			x = 998;		// X���W�̏����ʒu
			y = 183;		// Y���W�̏����ʒu
			//y = 0;			// Y���W�̏����ʒu
			w = 230;		// ���̏����ʒu
			h = 490;		// �����̏����ʒu
			//popflg = TRUE;	// �o���t���O���I��
			break;			// �u���C�N
		case 1:
			x = 718;		// X���W�̏����ʒu
			y = 183;		// Y���W�̏����ʒu
			//y = 0;			// Y���W�̏����ʒu
			w = 230;		// ���̏����ʒu
			h = 490;		// �����̏����ʒu
			//popflg = TRUE;	// �o���t���O���I��
			break;			// �u���C�N
		case 2:
			x = 438;		// X���W�̏����ʒu
			y = 183;		// Y���W�̏����ʒu
			//y = 0;			// Y���W�̏����ʒu
			w = 230;		// ���̏����ʒu
			h = 490;		// �����̏����ʒu
			//popflg = TRUE;	// �o���t���O���I��
			break;			// �u���C�N
		default:

			break;
		}
	
}
// ���X�{�X�̏�����
void LastBossInit() {
	for (int i = 0; i < YAMATANO_NECK; i++) {
		g_boss_Yamatano[i].lasbossInit(i);
	}
}