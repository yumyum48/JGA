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
struct barrier : public picInfo {
	bool flg;	// �o���t���O
	int cnt;	// �o���J�E���g

	// barriar�����������郁�\�b�h
	void barrierInit() {
		x = 654;	// X���W�̏����ʒu
		y = g_boss[g_select_Stage].y + 10;	// Y���W�̏����ʒu

		flg = FALSE;	// �o���t���O��������	
		cnt = 0;		// �o���J�E���g��������
	}
};
//
barrier g_barrier;		// �o���A�̏��
/*********************************************

* �O���[�o���ϐ��̐錾

*/////////////////////////////////////////////
/*********************************************

* �X�e�[�W�T�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage5() {
	// 0,3:�{�X�̃j���[�g�������[�V�����̍ŏ��ƍŌ�	4,7:�{�X�̍U�����[�V�����̍ŏ��ƍŌ�	8,9:�{�X�̍U���\������̍ŏ��ƍŌ�
	const int bossAnime[6] = { 0, 3, 4, 7, 8, 9 };
	static int animationStart = bossAnime[0];	// �A�j���[�V�����J�n�ʒu�̏�����
	static int animationLast = bossAnime[1];	// �A�j���[�V�������[�v�̏�����
	static int animecnt = 0;					// �A�j���[�V����������ׂ̃J�E���g

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

	if (g_boss[g_select_Stage].attackFlg != BOSSATTACK_TACKLE) {
		if (animecnt++ % 10 == 0)g_boss5_Ex.anime++;					// �A�j���[�V�����̐i�s
		if (g_boss5_Ex.anime > animationLast)g_boss5_Ex.anime = animationStart;	// �A�j���[�V�����̃��[�v
	}


	// �{�X�̕\��
	//DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	DrawRotaGraph2(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, 0, 0, 1.0f, 0, g_pic.boss_5_1[g_boss5_Ex.anime], TRUE, FALSE);

	if (g_barrier.cnt++ >= 300 && g_barrier.flg == TRUE) {
		// �V�[���h
		DrawGraph(g_barrier.x, g_barrier.y, g_pic.boss6_sield, TRUE);
		//DrawBox(g_barrier.x, g_barrier.y, g_barrier.x + 30, g_barrier.y + BOSS_STAGE5_HEIGHT, 0x000000, TRUE);
	}

	// �~�j�N���Q�̕\��
	Boss_MiniKurage_Drop_Disp();

	// �U���\��
	if (g_boss[BOSS_STAGE5].attackFlg == BOSSATTACK_TACKLE) {						// �{�X���U�����Ă����
		BossAttackDisp();	// �{�X�̍U��
	}
}

// ����
void BossMove_Stage5() {
	//static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���
	//static int attackSelect = 0;							// �{�X�̍U���I��
	//static int attackFlgBuf = g_boss[BOSS_STAGE5].attackFlg;// �P�t���[���O�̃{�X��attack�t���O���L������


	Boss_MiniKurage_DropFlg();		// �~�j�N���Q���o���t���O�Ǘ�
	Boss_MiniKurage_Drop_Move();	// �~�j�N���Q�̓�����U��


	if (g_boss[BOSS_STAGE5].coolTime++ > 600 && g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {		// �d������
		g_boss[BOSS_STAGE5].attackFlg = InputRand(BOSSATTACK_MINIKURAGE_AIR, BOSSATTACK_MINIKURAGE_AIR, BOSSATTACK_MINIKURAGE_AIR);
	}
	else if (g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {
		g_boss[BOSS_STAGE5].attackFlg = 0;
	}

	// �U��
	if (g_boss[BOSS_STAGE5].attackFlg == BOSSATTACK_TACKLE) {						// �{�X���U�����Ă����

		BossAttackMove();	// �{�X�̍U��
	}

	if (g_boss[BOSS_STAGE5].attackFlg != BOSSATTACK_TACKLE) {
		g_barrier.flg = TRUE;
		if (BossDamageCheck(g_boss[BOSS_STAGE5].hp) == TRUE && g_barrier.cnt >= 300) {
			g_boss[BOSS_STAGE5].hp++;
			g_barrier.cnt = 0;
		}
	}
	else {
		g_barrier.flg = FALSE;
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
		if (g_enemy[i].kurage.flg == FALSE) {	// �S�̂̃~�j�N���Q���S�Ă��Ȃ��Ȃ������ǂ����`�F�b�N
			cnt++;
		}

	}
	if (cnt >= KURAGE_MAX) {


		if (g_boss[g_select_Stage].attackFlg != BOSSATTACK_TACKLE) {	// �^�b�N�����I�������~�j�N���Q���[
			for (int i = 0; i < KURAGE_MAX; i++) {
				g_enemy[i].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);
				g_enemy[i].kurage.flg = TRUE;
				g_boss[BOSS_STAGE5].coolTime = 0;
			}
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
	/*for (int i = 0; i < KURAGE_MAX; i++) {
		DrawBox(g_enemy[i].kurage.x, g_enemy[i].kurage.y, g_enemy[i].kurage.x + ENEMY_WIDTH, g_enemy[i].kurage.y + ENEMY_HEIGHT, 0x00FF00, TRUE);
	}*/
}

void Boss_MiniKurage_Drop_Move() {

	bossAttackInfo position[KURAGE_MAX] = { {787, 55}, {1059, 28}, {1130, 191}, {1095, 380} };	// �~�j�N���Q�̔z�u�����ʒu
	static bool ataackFlg_AirKurage = FALSE;									// �󒆂Ŕ��ł���N���Q�̍U���t���O TRUE:�U������ FALSE:�U�����Ȃ�
	static bool attackFlg_GroundKurage = FALSE;									// �n��Ŕ��ł���N���Q�̍U���t���O TRUE:�U������ FALSE:�U�����Ȃ�
	// �\������Ă��āA�����|�W�V�����ɂ��Ȃ��G���G�������|�W�Ɉړ�������
	for (int i = 0; i < KURAGE_MAX; i++) {
		if ((g_enemy[i].kurage.flg == TRUE)			// �G�̏o���t���O���I���̎�
			&& (ataackFlg_AirKurage == FALSE)			// �N���Q���U�����Ă��Ȃ��Ƃ�
			&& (attackFlg_GroundKurage == FALSE)) {

			float angle;
			angle = atan2((g_enemy[i].kurage.y - position[i].y), (g_enemy[i].kurage.x - position[i].x));
			g_enemy[i].kurage.x -= cos(angle);
			g_enemy[i].kurage.y -= sin(angle);


		}
	}


	int cnt = 0;			// �N���Q�̔z��𐧌䂷��p�̃J�E���g(�U���������Ƃ̃N���Q�͏���������̂ł��̎��̃N���Q���Z�b�g���鏈�������邽��)
	static int cntBuf_Air;		// �󒆃N���Q�Ɍ��肳�ꂽ�v�f�ԍ����i�[����
	static int cntBuf_Ground;	// �n��N���Q�Ɍ��肳�ꂽ�v�f�ԍ����i�[����


	for (cnt = 0; cnt < KURAGE_MAX; cnt++) {	// �o�����Ă���z��ԍ������������œY������break���ēn��
		if (g_enemy[cnt].kurage.flg == TRUE)
			break;
	}
	if ((g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)	// �~�j�N���Q���󒆍U�������鎞
		&& (ataackFlg_AirKurage != TRUE)) {	// �󒆂ł̍U�������ĂȂ���
		ataackFlg_AirKurage = TRUE;		// �󒆃N���Q�̍U���t���O���I����
		cntBuf_Air = cnt;				// �z��̗v�f�ԍ����i�[���ăJ�E���g�Ƀv���X�P������
	}

	for (cnt = 0; cnt < KURAGE_MAX; cnt++) {	// �o�����Ă���z��ԍ������������œY������break���ēn��
		if (g_enemy[cnt].kurage.flg == TRUE)
			break;
	}
	if ((g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)	// �~�j�N���Q���n��ōU�������鎞
		&& (attackFlg_GroundKurage != TRUE)) {	// �n��ł̍U�������ĂȂ���
		attackFlg_GroundKurage = TRUE;			// �n��N���Q�̍U���t���O���I����
		cntBuf_Ground = cnt;					// �z��̗v�f�ԍ����i�[���ăJ�E���g�Ƀv���X�P������
	}


	static int flgcnt = 0;
	if (ataackFlg_AirKurage == TRUE && cntBuf_Air < KURAGE_MAX) {
		BossMiniKurage_Attack_Air(cntBuf_Air, &ataackFlg_AirKurage);
		if (ataackFlg_AirKurage == FALSE) {
			flgcnt++;
		}

	}

	if (attackFlg_GroundKurage == TRUE && cntBuf_Ground < KURAGE_MAX) {
		BossMiniKurage_Attack_Ground(cntBuf_Ground, &attackFlg_GroundKurage);
		if (attackFlg_GroundKurage == FALSE) {
			flgcnt++;
		}
	}

	if (flgcnt >= 4) {
		g_boss[g_select_Stage].attackFlg = BOSSATTACK_TACKLE;	// �S�̂̃N���Q�����Ȃ��Ȃ��Ă�����{�X�{�̂��^�b�N�����s
	}
	if (g_boss[g_select_Stage].attackFlg == BOSSATTACK_TACKLE) {
		flgcnt = 0;
	}

	/*
		//static bool ataackFlg_AirKurage = FALSE;									// �󒆂Ŕ��ł���N���Q�̍U���t���O
		//static bool attackFlg_GroundKurage = FALSE;									// �n��Ŕ��ł���N���Q�̍U���t���O
		//static bool attackKurageCheck[KURAGE_MAX] = { FALSE, FALSE, FALSE, FALSE };	// �N���Q���U���Ŏg���Ă��Ȃ��� TRUE:�g���Ă��� FALSE:�g���Ă��Ȃ�
		//static int attackKurageBuf_Air;												// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�󒆍U���p)
		//static int attackKurageBuf_Ground;											// �U���Ŏg���Ă��ȃN���Q�̗v�f�ԍ����L��������(�n��U���p)

		//// �{�X���~�j�N���Q�ōU������Ɣ��f����(�n���)
		//if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_AIR)
		//&&  (ataackFlg_AirKurage != TRUE) ){	// �󒆂ł̍U�������ĂȂ���
		//
		//	for (attackKurageBuf_Air = 0; attackKurageBuf_Air < KURAGE_MAX; attackKurageBuf_Air++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
		//		if (g_enemy[attackKurageBuf_Air].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Air] == FALSE) {
		//			ataackFlg_AirKurage = TRUE;															// �U�����s����Ȃ�t���O���I���ɂ���
		//			attackKurageCheck[attackKurageBuf_Air] = TRUE;										// �U�����̃t���O���I���ɂ���
		//			break;																				//�g����N���Q�̗v�f�ԍ���f���o��
		//		}
		//	}
		//}
		////else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_AIR){
		////	ataackFlg_AirKurage = FALSE;
		////}

		//// �{�X���~�j�N���Q�ōU������Ɣ��f����(�󒆂�)
		//if( (g_boss[g_select_Stage].attackFlg == BOSSATTACK_MINIKURAGE_GROUND)
		//&&  (attackFlg_GroundKurage != TRUE) ){	// �n��ł̍U�������ĂȂ���
		//	for (attackKurageBuf_Ground = 0; attackKurageBuf_Ground < KURAGE_MAX; attackKurageBuf_Ground++) {	// �~�j�N���Q���U�����s���邩�`�F�b�N
		//		if (g_enemy[attackKurageBuf_Ground].kurage.flg == TRUE && attackKurageCheck[attackKurageBuf_Ground] == FALSE) {
		//			attackFlg_GroundKurage = TRUE;														// �U�����s����Ȃ�t���O���I���ɂ���
		//			attackKurageCheck[attackKurageBuf_Ground] = TRUE;									// �U�����̃t���O���I���ɂ���
		//			break;																				//�g����N���Q�̗v�f�ԍ���f���o��
		//		}
		//	}
		//}
		////else if(g_boss[g_select_Stage].attackFlg != BOSSATTACK_MINIKURAGE_GROUND){
		////	attackFlg_GroundKurage = FALSE;
		////}
		//static int attackCnt = 0;	// �U�����I�������񐔂𐔂���

		//// �󒆂Ń~�j�N���Q���U��������
		//if (ataackFlg_AirKurage) {
		//	BossMiniKurage_Attack_Air(attackKurageBuf_Air, &ataackFlg_AirKurage);
		//	if (ataackFlg_AirKurage == FALSE) {
		//		attackCnt++;
		//	}
		//}

		//if (attackFlg_GroundKurage) {
		//	BossMiniKurage_Attack_Ground(attackKurageBuf_Ground, &attackFlg_GroundKurage);
		//	if (attackFlg_GroundKurage == FALSE) {
		//		attackCnt++;
		//	}
		//}

		//if (attackCnt >= 4) {	// �l��U�������Ă�����A�N���Q�A�^�b�N�`�F�b�N���S���I���ɂȂ��Ă���̂ŏ�����
		//	for (int i = 0; i < KURAGE_MAX; i++) {
		//		attackKurageCheck[i] = FALSE;
		//	}
		//}
		//

	*/
	// �~�j�N���Q�Ƃ̓����蔻��
	KurageHit();	// �q�b�g����ƃv���C���[��Hp����
}

// �~�j�N���Q�̋󒆍U��
void BossMiniKurage_Attack_Air(int cntBuf_Air, bool* ataackFlg_AirKurage) {
	int moveY = 5, moveX = 16;

	if (g_enemy[cntBuf_Air].kurage.x <= 0) {
		g_enemy[cntBuf_Air].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);	// �~�j�N���Q�̏�����
		//g_boss[g_select_Stage].attackFlg = 0;										// �{�X�̍U���t���O���I�t��
		g_boss[g_select_Stage].coolTime = 500;										// �{�X�̃N�[���^�C��������
		*ataackFlg_AirKurage = FALSE;												// �{�X�̍U���t���O�o�b�t�@�[��������
	}
	else {
		if (g_enemy[cntBuf_Air].kurage.y < (GROUND - ENEMY_HEIGHT) - 200) {
			g_enemy[cntBuf_Air].kurage.y += moveY;
		}
		else {
			g_enemy[cntBuf_Air].kurage.y = (GROUND - ENEMY_HEIGHT) - 200;
			g_enemy[cntBuf_Air].kurage.x -= moveX;
		}
	}
}
// �~�j�N���Q�̒n��U��
void BossMiniKurage_Attack_Ground(int cntBuf_Ground, bool* attackFlg_GroundKurage) {
	int moveY = 5, moveX = 16;
	if (g_enemy[cntBuf_Ground].kurage.x <= 0) {
		g_enemy[cntBuf_Ground].kurage.BossArea_KurageInit(g_boss[g_select_Stage].y);// �~�j�N���Q�̏�����
		//g_boss[g_select_Stage].attackFlg = 0;										// �{�X�̍U���t���O���I�t��
		g_boss[cntBuf_Ground].coolTime = 500;										// �{�X�̃N�[���^�C��������
		*attackFlg_GroundKurage = FALSE;											// �{�X�̍U���t���O�o�b�t�@�[��������
	}
	else {
		if (g_enemy[cntBuf_Ground].kurage.y < GROUND - ENEMY_HEIGHT) {
			g_enemy[cntBuf_Ground].kurage.y += moveY;
		}
		else {
			g_enemy[cntBuf_Ground].kurage.y = GROUND - ENEMY_HEIGHT;
			g_enemy[cntBuf_Ground].kurage.x -= moveX;
		}
	}
}

void KurageHit() {
	for (int i = 0; i < ENEMY_MAX; i++) {
		if ((g_enemy[i].kurage.flg == TRUE)
			&& (g_noDamageCnt > 60)) {		//�n��̓G�̓����蔻��
			if (PlayerHitCheck(g_enemy[i].kurage.x, g_enemy[i].kurage.y, ENEMY_WIDTH, ENEMY_HEIGHT) == TRUE) {

				if (g_player.barrierFlg == FALSE) --g_player.hp;
				else g_player.barrierFlg = FALSE;
				g_noDamageCnt = 0;		// ���G���Ԕ���
			}
		}
	}
}

void Boss5_Init() {

	g_barrier.barrierInit();
	g_boss5_Ex.AnimtionInit();
}