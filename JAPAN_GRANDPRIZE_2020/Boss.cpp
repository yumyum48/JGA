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
#include "Macro.h"
#include "HP.h"
#define _USE_MATH_DEFINES
#include <math.h>


/*********************************************

* �X�e�[�W�P�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage1() {
	//	���ʂ��x��
	// �񎟌��z���0�Ԗڂ͓G�{��
	// �P�Ԗڂ͐���
	int bossAnime_MAX[2] = { 7, 15};	// �A�j���[�V�����̍ŏI��
	int bossAnime_Start[2] = { 0, 8 };	// �A�j���[�V�����̍ŏ�
	static int anime[2] = { 0, 0 };		// �摜�̐؂�ւ�
	static int time = 0;				// �t���[���P�ʂ̃J�E���g

	if (time++ % 4 == 0) anime[0]++;
	if (time % 6 == 0) anime[1]++;
	for (int i = 0; i < 2; i++) {
		if (anime[i] > bossAnime_MAX[i]) {
			anime[i] = bossAnime_Start[i];
		}
	}
		
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[1]], TRUE);
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[0]], TRUE);

	if (g_boss[0].attackFlg != 0) {
		BossAttackDisp();	// �{�X�̍U��
	}

}


/*********************************************

* �{�X�̓����B

*/////////////////////////////////////////////
// �{�X�̓����p�^�[��
void BossMoveMotion(int *coolTime, int *moveFlg){

	switch (*moveFlg)
	{
	case BOSSMOVE_ATTACK:
		BossMoveMotion_Pattern1(coolTime, moveFlg);		// �{�X���T�C���͂Őڋ�
		break;

	case BOSSMOVE_SPEEDDOWN:
		BossMoveMotion_Pattern2(coolTime, moveFlg);		// �{�X��X�������Ɋ���Ă���
		break;
		
	default:
		break;
	}

}

void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg) {
	static bool teleportFlg = FALSE;

	if (g_boss[g_select_Stage].x > -BOSS_WIDTH
		&& teleportFlg == FALSE) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// �c�̐U�ꕝ
		g_boss[g_select_Stage].x -= 5;						// �{�X�̈ړ���
	}
	else if(g_boss[g_select_Stage].x <= -BOSS_WIDTH){
		g_boss[g_select_Stage].x = WINDOW_WIDTH + BOSS_WIDTH;
		g_boss[g_select_Stage].y = 160;
		teleportFlg = TRUE;
	}

	if (teleportFlg == TRUE
		&& g_boss[g_select_Stage].x > 700) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
		g_boss[g_select_Stage].y -= sin(angle) * 10 - 0.8;			// �c�̐U�ꕝ
		g_boss[g_select_Stage].x -= 5;						// �{�X�̈ړ���
	}
	else if (teleportFlg == TRUE) {
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
		teleportFlg = FALSE;
	}
}

void BossMoveMotion_Pattern2(int* coolTime, int* moveFlg) {
	static int chanceTime = 0;
	static bool speedUpFlg = FALSE;
	// �{�X�̈ړ��X�s�[�h�����񂾂�Ɨ��Ƃ�
	if (g_boss[g_select_Stage].x >= g_player.x + PLAYER_WIDTH && speedUpFlg == FALSE) {
		g_boss[g_select_Stage].x -= 2;
		if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {				// �{�X���_���[�W���󂯂����ǂ����𒲂ׂ�֐� TRUE: �{�X���_���[�W���󂯂� FALSE: �{�X�̓_���[�W���󂯂Ă��Ȃ�
			speedUpFlg = TRUE;
		}
	}
	else if(chanceTime++ >= 120 || BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE){	// �v���C���[�̖ڂ̑O�ɗ�����A�U���ł���悤�Ƀ`�����X�^�C�������
		speedUpFlg = TRUE;			// ��b��������A�܂��̓v���C���[���U����������{�X�Q���X�s�[�h�A�b�v���Č��̈ʒu�܂Ŗ߂�
	}
	if (speedUpFlg == TRUE && g_boss[g_select_Stage].x < 823) {
		g_boss[g_select_Stage].x += 2;	// �{�X���ŏ��̈ʒu�ւƖ߂�
	}
	else if (g_boss[g_select_Stage].x >= 823) {
		g_boss[g_select_Stage].x = 823;	// �ŏ��̏ꏊ�ɖ߂�������W���Œ�
		*coolTime = 0;					// �N�[���^�C��������
		*moveFlg = 0;					// moveFlg������
		speedUpFlg = FALSE;				// �X�s�[�h�A�b�v�t���O��������
	}
}
/*********************************************

* �{�X�̓����蔻��	// ������ƃv���C���[hp����

*/////////////////////////////////////////////
void Boss_Knock_Down() {
	
	if (g_boss[g_select_Stage].hp <= 0) {
		g_gameScene = GAME_STAGE_CLEAR;
		g_select_MAX++;	// �Z���N�g�ł���}�b�v�𑝂₷
	}
	
}
/*********************************************

* �{�X�̍U���֌W

*/////////////////////////////////////////////
// �{�X�̍U���̑S�̊Ǘ�(�\��)
void BossAttackDisp() {
	
	
	switch (g_boss[g_select_Stage].attackFlg) {
		case BOSSATTACK_ENEMY_DROP:
		
			BossEnemyDropDisp();	// �ア�G���o��
			//DrawFormatString(100, 600, 0xFF00FF, "�{�X���U�����Ă܂���I");
			//g_boss[BOSS_STAGE1].attackFlg = 0;
			break;

		case BOSSATTACK_WATER_BULLET:
			BossWaterBulletDisp();	// ���e�̔���
			break;

		case BOSSATTACK_WAVE_ATTACK:
			BossGenerateWave();		// �Ôg�̔���
			break;
		case BOSSATTACK_JUMPANDPOISON:
			BossJumpOrPoison_Disp();// �{�X���W�����v���ċH�ɓł��o���\��
			break;

		case BOSSATTACK_LONGTON:
			BossLongTon_Disp();		// �{�X�����L�΂��U��
			break;
		default:
			break;
	}
	

	
}
// �{�X�̍U���̑S�̊Ǘ�(����)
void BossAttackMove() {

	switch (g_boss[g_select_Stage].attackFlg) {
		case BOSSATTACK_ENEMY_DROP:
			BossEnemyDropMove();	// �ア�G���o��
			//g_boss[g_select_Stage].attackFlg = 0;
			break;

		case BOSSATTACK_WATER_BULLET:
			BossWaterBulletMove();	// ���e�̔���
			break;

		case BOSSATTACK_WAVE_ATTACK:
			BossGenerateWave();		// �Ôg�̔���
			break;

		case BOSSATTACK_JUMPANDPOISON:
			BossJumpOrPoison_Move();// �{�X���W�����v���ċH�ɓł��o������
			break;

		case BOSSATTACK_LONGTON:
			BossLongTon_Move();
			break;
		default:
			break;
	}
	
}

picInfo g_boss3_Ton;	// �{�X�R�̐�̏��
void BossLongTon_Disp() {
	static int plas = 0;			// �������Ă���
	int tonW = g_boss3_Ton.x + plas;
	int tonH = g_boss3_Ton.y + 100;

	//DrawFormatString(500, 500, 0x0000FF, "tonX=%d\ntonW=%d", tonX, tonW);
	DrawBox(g_boss3_Ton.x, g_boss3_Ton.y, tonW, tonH, 0xFFFF00, TRUE);
	if (tonW > 0) {
		plas -= 5;
	}
	else {
		tonW = 0;
	}
	// �\���Ő�͓�����

	DrawBox(822, 97, 822+10, 97+10, 0x00FF00, TRUE);


	if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {		// �{�X���U�����ꂽ��U�����f���ăW�����v���ē�����
		g_boss[BOSS_STAGE3].attackFlg = 0;		// attack�t���O��������
		plas = 0;

		//boss_JumpFlg = BOSS_3_JUMPON;
	}															   // �{�X���v���C���[�ɓ���������A�_���[�W��^���ē�����
	else if (PlayerHitCheck(g_boss[BOSS_STAGE3].x, g_boss[BOSS_STAGE3].y, BOSS_STAGE3_WIDTH, BOSS_STAGE3_HEIGHT) == TRUE) {
		if (g_player.barrierFlg == FALSE) --g_player.hp;
		else g_player.barrierFlg = FALSE;
		g_noDamageCnt = 0;
		g_boss[BOSS_STAGE3].attackFlg = 0;		// attack�t���O��������
		plas = 0;
	}
}

void BossLongTon_Move() {

	g_boss[BOSS_STAGE3].x -= 2;

	//if (Boss_3_Jump(&coolTime, &boss_JumpFlg, 1) == TRUE) {
	//	g_boss[BOSS_STAGE3].attackFlg = 0;	// attack�t���O���I�t��
	//}
}

bool Boss_3_Jump(int *coolTime, int *boss_JumpFlg, int jumpType) {
	int boss_MaxUp = 97;							// �{�X�R���W�����v���Ă�����Y���W�ō��x
	int boss_MaxDown = 290;							// �{�X�R�̗��������ۂ�Y�n�_
	int boss_startX = 822;							// �{�X�R��X���W�̏����l


	if (*boss_JumpFlg == BOSS_3_JUMPON) {	// �㏸
		if (g_boss[BOSS_STAGE3].y >= boss_MaxUp) {		// �{�X�����n�_�܂ŏ�ɏグ��
			
			if (jumpType == 1) {	// �󂯂��W�����v�t���O���U�����Ȃ̂��ǂ������m�F���ĂP�Ȃ牡�ɔ�΂�
				if (g_boss[BOSS_STAGE3].x < boss_startX) {
					g_boss[BOSS_STAGE3].x += 6;	// �{�X�����ɐ������
					g_boss[BOSS_STAGE3].y -= 2;	// �኱��ɏオ��Ȃ���
				}
				else {
					*boss_JumpFlg = BOSS_3_DOWN;	// ���~������
				}
			}
			else {

				g_boss[BOSS_STAGE3].y -= 2;	// �^��ɃW�����v����
			}
		}
		else if (g_boss[BOSS_STAGE3].y < boss_MaxUp) {	// ����n�_�܂ŗ�������W���Œ�
			g_boss[BOSS_STAGE3].y = boss_MaxUp;			
			*boss_JumpFlg = BOSS_3_DOWN;	// ���~������

		}
	}
	else if (*boss_JumpFlg == BOSS_3_DOWN) {	// ���~
		if (g_boss[BOSS_STAGE3].y < boss_MaxDown) {		// �{�X�����n�_�܂ŏ�ɏグ��
			g_boss[BOSS_STAGE3].y += 2;
		}
		else if (g_boss[BOSS_STAGE3].y >= boss_MaxDown) {	// ����n�_�܂ŗ�������W���Œ�
			//g_boss[BOSS_STAGE3].x = boss_startX;
			g_boss[BOSS_STAGE3].y = boss_MaxDown;
			
			*boss_JumpFlg = BOSS_3_JUMPOFF;	// �W�����v�t���O���I�t��
			*coolTime = 0;		// �N�[���^�C����������
			return TRUE;
		}


	}

	return FALSE;


}
/*********************************************

* �{�X���W�����v���ċH�ɓł��o������

*/////////////////////////////////////////////
void BossJumpOrPoison_Disp() {

}

void BossJumpOrPoison_Move() {

}
/*********************************************

* �{�X���ア�G���o���U��������֐�

*/////////////////////////////////////////////
// �����ア�G���o��(�\��)
void BossEnemyDropDisp() {
	
	BossAreaEnemyDisp();
}
// �ア�G���o��(����(�����蔻��Ȃ�))
void BossEnemyDropMove() {

	BossAreaEnemyMove();
}
// 
void BossAreaEnemyDisp() {
	static int coolTime = 0;
	static int enemyDropCnt = 0;
	static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // 
	static int enemy_cnt = 0;	// �o�������G�l�~�[�̗v�f�ԍ�
	// �N�[���^�C��
	if (++coolTime > 60) {
		// �G�l�~�[�̏o���t���O���I���ɂ���
		
		if (g_enemy[enemy_cnt].walk.flg == FALSE && enemy_cnt < 3) {
			g_enemy[enemy_cnt].walk.flg = TRUE;
			coolTime = 0;
				
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
			g_enemy[i].fly.anime++;
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
	if (enemyDropCnt >= 3) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			g_boss[g_select_Stage].attackFlg = 0;    // attack�t���O��������
			enemyDropCnt = 0;                        // �G�l�~�[���o�����񐔂�������
			enemy_cnt = 0;							 // �G�l�~�[�̏o�������񐔂�������
			enemy_dispFlg_Buf[0] = { FALSE };        // �G�l�~�[�̏o���t���O�o�b�t�@�[��������
			enemy_dispFlg_Buf[1] = { FALSE };
			enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

	// �G�̏����A�j���[�V����
	EnemyEvaporation();
}
// 
void BossAreaEnemyMove() {
	static int enemyCnt;        // 


	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {        //
		
		
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= (g_speedLevel - 3);

			//g_enemy[i].walk.x -= g_boss[g_select_Stage].x;

		}
			
		if (g_enemy[i].walk.x + ENEMY_WIDTH < 0) {

			g_enemy[i].walk.BossAreaWlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
				//g_enemy[i].walk.flg = TRUE;
		}

		
	}
}

/*********************************************

* �{�X�����e�ōU��������֐�

*/////////////////////////////////////////////
// ���e�̕`��
void BossWaterBulletDisp() {
	static int animationMax = 3;			// �A�j���[�V����
	static int anime = 0;				// �A�j������
	static int time = 0;				// �o�ߎ���
	static int startX = g_boss[BOSS_STAGE1].x + 100,
				startY = g_boss[BOSS_STAGE1].y + 200;	// ���e�̏����ʒu
	static float moveX = 0, moveY = 0;	// ���e�̈ړ���
	static int noDamegeCnt = 60;		// �_���[�W���󂯕t���Ȃ�����
	static bool attackFlg = FALSE;		// �U�����f�t���O	 treu:�U����  false:���U��

	// �t���[���P�ʂ̔�e���̒���
	if (noDamegeCnt++ < 60);

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
			g_boss[BOSS_STAGE1].attackFlg = 0;
		}
	}

	// ���e����ʊO�ɏo���Ƃ��̏���
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}

	// ���e�̃A�j���[�V����
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// ���e�̕\��
	if (attackFlg == FALSE) {
		moveX -= 7.5;
		moveY += 2.5;
		/*moveX -= 3.0;
		moveY += 1.0;*/
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[anime], TRUE, FALSE);
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
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}



	// �f�o�b�O
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
}
// ���e�̓����I�ȓ���
void BossWaterBulletMove() {

}


/***********************************************************

// �����������Ƃ��ĎO���A���̒��̈�������_���ŕԂ�

***********************************************************/
int InputRand(int rand1, int rand2, int rand3) {
	int num = GetRand(3);
	switch (num)
	{
	case 0: return rand1; break;
	case 1: return rand2; break;
	case 2: return rand3; break;
	default: return 0;	  break;
	}

}
/***********************************************************

// �{�X���_���[�W���󂯂����ǂ����𒲂ׂ�֐� TRUE: �{�X���_���[�W���󂯂� FALSE: �{�X�̓_���[�W���󂯂Ă��Ȃ�

***********************************************************/
bool BossDamageCheck(int bossHp) {
	static int bossHpBuf = bossHp;

	if (bossHp <= bossHpBuf) {
		if (bossHp < bossHpBuf) {
			bossHpBuf = bossHp;
			return TRUE;
		}
	}

	bossHpBuf = bossHp;
	return FALSE;
}
/***********************************************************

// �{�X���U�����I�������𒲂ׂ�֐�TRUE: �{�X�̍U���I�� FALSE: �{�X�͍U�����A�܂��͏I�����Ă��΂炭�����Ă���

***********************************************************/
bool BossAttackCheck(int bossAttackFlg) {
	static int bossAttackBuf = bossAttackFlg;

	if (bossAttackFlg == 0 && bossAttackBuf != 0) {		
		bossAttackBuf = bossAttackFlg;
		return TRUE;
	}

	bossAttackBuf = bossAttackFlg;
	return FALSE;
}

/***********************************************************

// �{�X�̏�����

***********************************************************/
void BossInit() {
	for (int i = BOSS_STAGE1; i < BOSS_MAX; i++) {
		g_boss[i].Init_Stage(i);		// �S�X�e�[�W�̃{�X�̏�����
	}
	g_boss3_Ton.Boss3_TonInit();	// �X�e�[�W�R�̃{�X�̐�̏�����
	Boss_Stage4_Init();	// �{�X�X�e�[�W�S�̉_�̏�����
}