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
const int KURAGE_MAX = 4;	// �o������N���Q�̍ő吔
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
	Boss_MiniKurage_Drop_Disp();
}

// ����
void BossMove_Stage5() {
	static int coolTime = 0;								// �d������
	//static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	//static int attackSelect = 0;							// �{�X�̍U���I��
	//static int attackFlgBuf = g_boss[BOSS_STAGE5].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������



	if (coolTime++ > 600) {		// �d������
		g_boss[BOSS_STAGE5].attackFlg = InputRand(BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND, BOSSATTACK_MINIKURAGE_GROUND);
	}

	Boss_MiniKurage_DropFlg();
	Boss_MiniKurage_Drop_Move();

	if (BossNoAttackCheck(g_boss[BOSS_STAGE5].attackFlg) == TRUE) {
		coolTime = 480;
	}
	//	&& (g_boss[BOSS_STAGE5].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
	//	&& (moveFlg == BOSSMOVE_NOMOTION)) {							// �{�X���ړ����Ă��Ȃ����


	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// �{�X���U�����Ȃ��Ƃ��ɏ�������G���G�̏�����
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}

	//	attackSelect = InputRand(0, 0, 0);			//�����ōU�����邩�ړ������邩������

	//	if (attackSelect != 0) {
	//		g_boss[BOSS_STAGE5].attackFlg = attackSelect;				// �U������ꍇ�A�t���O�ɑΉ���������������
	//		coolTime = 0;												// �N�[���^�C��������
	//	}
	//	else {	// �U�������Ȃ��Ƃ�
	//		

	//	}
	//}
	////// �g���b�v�𐶐����鎞�Ƀg���b�v��������
	////if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
	////	g_trap.WaveInit(g_boss[BOSS_STAGE5].x);
	////}
	//// �o�b�t�@�[�Ɣ�ׂĎG���G�������ĂȂ��Ƃ��͎G���G��������

	//// �o�b�t�@�[�Ɣ�ׂĎG���G�������鎞�G���G��������
	//if (BossDropAttackCheck(g_boss[BOSS_STAGE5].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// �U�������ōs��
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

	//	BossMoveMotion(&coolTime, &moveFlg);	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	//}

	//// �U��
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// �{�X���U�����Ă����

	//	BossAttackMove();	// �{�X�̍U��
	//}

	//Poison_Trap_Move();	// �ł̃g���b�v�̓���
	//if (g_boss4_Rightning_Cnt >= 1800) {		// �J�E���g���P�̍���Disp�̕����𐧌�
	//	g_boss4_Rightning_Cnt = 1799;
	//}

	
	Boss_Knock_Down();	// �{�X���|����Ă鏈��
}

/*********************************************

* �~�j�N���Q�����Ȃ�������t���O���I���ɂ��ăN���Q���[

*/////////////////////////////////////////////
void Boss_MiniKurage_DropFlg() {
	//static int coolTime = 0;
	//static int enemyDropCnt = 0;
	//static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // 
	//static int enemy_cnt = 0;	// �o�������G�l�~�[�̗v�f�ԍ�

	int cnt = 0;	// �g��ꂽ�~�j�N���Q�̐��𐔂���
	for (int i = 0; i < KURAGE_MAX; i++) {
		if(g_enemy[i].kurage.flg == FALSE) {	// �S�̂̃~�j�N���Q���S�Ă��Ȃ��Ȃ������ǂ����`�F�b�N
			cnt++;
		}
	
	}
	if (cnt >= KURAGE_MAX) {					// �S�̂̃~�j�N���Q���S�Ă��Ȃ��Ȃ��Ă�����~�j�N���Q���[ // �{���̓{�X���^�b�N���������Ƃɕ�[
		for (int i = 0; i < KURAGE_MAX; i++) {
			g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
			g_enemy[i].kurage.flg = TRUE;
		}
	}

}

void Boss_MiniKurage_Drop_Disp() {
	
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

void Boss_MiniKurage_Drop_Move() {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// �~�j�N���Q�̔z�u�����ʒu

	// �\������Ă��āA�����|�W�V�����ɂ��Ȃ��G���G�������|�W�Ɉړ�������
	for (int i = 0; i < KURAGE_MAX; i++) {
		if (g_enemy[i].kurage.flg == TRUE) {
			//g_enemy[buf].kurage.x = position[buf].x;
			//g_enemy[buf].kurage.y = position[buf].y;
			float angle;
			angle =  atan2( (g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x) );
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);

			
		}
	}


	static bool ataackFlg_AirKurage = FALSE;	// �󒆂Ŕ��ł���N���Q�̍U���t���O
	static bool attackFlg_GroundKurage = FALSE;	// �n��Ŕ��ł���N���Q�̍U���t���O
	static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// �N���Q���U���Ŏg���Ă��Ȃ��� TRUE:�g���Ă��� FALSE:�g���Ă��Ȃ�
	static int attackKurageBuf_Air;											// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�󒆍U���p)
	static int attackKurageBuf_Ground;											// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�n��U���p)

	// �{�X���~�j�N���Q�ōU������Ɣ��f����(�n���)
	if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)
	&&  (ataackFlg_AirKurage != TRUE) ){	// �󒆂ł̍U�������ĂȂ���
	
		for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
			if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
				ataackFlg_AirKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
				attackKurageCheck[attackKurageBuf_Air] == TRUE;										// �U�����̃t���O���I���ɂ���
				break;																				//�g����N���Q�̗v�f�ԍ���f���o��
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_AIR){
	//	ataackFlg_AirKurage = FALSE;
	//}

	// �{�X���~�j�N���Q�ōU������Ɣ��f����(�󒆂�)
	if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)
	&&  (attackFlg_GroundKurage != TRUE) ){	// �n��ł̍U�������ĂȂ���
		for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
			if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
				attackFlg_GroundKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
				attackKurageCheck[attackKurageBuf_Ground] == TRUE;										// �U�����̃t���O���I���ɂ���
				break;																				//�g����N���Q�̗v�f�ԍ���f���o��
			}
		}
	}
	//else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
	//	attackFlg_GroundKurage = FALSE;
	//}

	// �󒆂Ń~�j�N���Q���U��������
	if (ataackFlg_AirKurage) {
		BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
	}

	if (attackFlg_GroundKurage) {
		BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
	}

	// �~�j�N���Q�Ƃ̓����蔻��
	KurageHit();	// �q�b�g����ƃv���C���[��Hp����
}

// �~�j�N���Q�̋󒆍U��
void BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage) {

	
	if (g_enemy[attackKurageBuf_Air].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Air].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
		g_boss[g_select_Stage].attackFlg = 0;
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
void BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage) {

	if (g_enemy[attackKurageBuf_Ground].kurage.x <= 0) {
		g_enemy[attackKurageBuf_Ground].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
		g_boss[attackKurageBuf_Ground].attackFlg = 0;
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

void KurageHit() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if( (g_enemy[i].kurage.flg == TRUE)
		&&  (g_noDamageCnt > 60) ){		//�n��̓G�̓����蔻��
			if (PlayerHitCheck(g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {
				
				if (g_player.barrierFlg == FALSE) --g_player.hp;
				else g_player.barrierFlg = FALSE;
				g_noDamageCnt = 0;		// ���G���Ԕ���
			}
		}
	}
}