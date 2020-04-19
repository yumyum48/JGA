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
/*********************************************

* �X�e�[�W�P�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage1() {
	if (g_enemybeat >= 10) {
		DrawBox(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT, 0x0FF000, TRUE);
	}

}
// ����
void BossMove_Stage1() {
	//BossAttack();	// �{�X�̍U��
	BossHit();
}
// �{�X�̓����蔻��
void BossHit() {
	
	//if (g_player.attackFlg == TRUE) {	// �v���C���[���U�������Ă�����
	if(g_player.attackFlg == TRUE) {
		if (PicHitCheck(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == 1 && g_boss[0].hp > 0) {
			g_boss[0].hp--;
		}
	}

	if (g_boss[0].hp <= 0) {
		g_gameScene = GAME_STAGE_CLEAR;
	}
}
// �{�X�̍U��
void BossAttack() {
	static int enemypop_Cnt = 0;	// �{�X���U��(�G���I���o���Ă���)�܂ł̃J�E���g
	static int enemypop_MAX = 1;	// �G�l�~�[�̍ő吔
	if (enemypop_Cnt++ > 50) {
		enemypop_MAX++;
		enemypop_Cnt = 0;

	}

	static enemyInfo enemy;	// �G�̏��(�G��)
	for (int i = 0; i < enemypop_MAX; i++) {
		//DrawRotaGraph(enemy[i].x, enemy[i].y, 0.2, 0.0, g_pic.enemy, TRUE);
		DrawBox(enemy.x + (ENEMY_WIDTH * i), 700, ENEMY_WIDTH, ENEMY_HEIGHT, 0xFF0000, TRUE);
		enemy.x -= 5;

		if (enemy.x + ENEMY_WIDTH <= 0) {	// �G����ʊO�ɓ������ꍇ�̏�������
			enemy.WalkInit();
			enemypop_MAX--;
		}
	}

	
}
/*********************************************

* �X�e�[�W�Q�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage2() {
	if (g_enemybeat >= 10) {
		DrawBox(g_boss[0].x, g_boss[0].y, 1280, 768, 0x0FF000, TRUE);
	}
}
// ����
void BossMove_Stage2() {

}

/*********************************************

* �X�e�[�W�R�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage3() {
	if (g_enemybeat >= 10) {
		DrawBox(600, 0, 1280, 768, 0x0FF000, TRUE);
	}
}
// ����
void BossMove_Stage3() {

}

void BossInit() {
	for (int i = 0; i < MAP_MAX; i++) {
		g_boss[i].Init_Stage1();
	}
}