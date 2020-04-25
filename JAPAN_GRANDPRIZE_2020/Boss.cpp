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
#define _USE_MATH_DEFINES
#include <math.h>

struct bossAttackInfo {	// �{�X�̍U���̍ۂɎg���\������
	int x, y;

};

enum {	// �{�X�̍U�����f
	ENEMY_DROP = 1
};
/*********************************************

* �X�e�[�W�P�̃{�X

*/////////////////////////////////////////////
// �`��
void BossDisp_Stage1() {
	
	DrawBox(g_boss[0].x, g_boss[0].y, g_boss[0].x + BOSS_WIDTH, g_boss[0].y + BOSS_HEIGHT, 0x0FF000, TRUE);

	if (g_boss[0].attackFlg != 0) {
		BossAttackDisp();	// �{�X�̍U��
	}

}

// ����
void BossMove_Stage1() {
	if (g_boss[0].attackFlg != 0) {
		BossAttackMove();	// �{�X�̍U��
	}
	// �U�������Ă��Ȃ��Ȃ瓮��
	else {
		if (g_boss[0].x > 0) {
			float angle;
			angle = DX_TWO_PI / 120 * g_boss[0].x;	// ���̐U�ꕝ
			g_boss[0].y -= sin(angle) * 10;	// �c�̐U�ꕝ
			g_boss[0].x -= 5;	// �{�X�̈ړ���
		}
		else {
			g_boss[0].x = 700;
			g_boss[0].y = 160;
		}
	}

	BossHit();	// �v���C���[�ƃ{�X�̓����蔻�蓖����ƃv���C���[��hp����
}
/*********************************************

* �{�X�̓����蔻��	// ������ƃv���C���[hp����

*/////////////////////////////////////////////
// �{�X�̓����蔻��
void BossHit() {
	
	if (PlayerHitCheck(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == TRUE) {
		g_player.hp--;
	}
	
}
/*********************************************

* �{�X�̍U���֌W

*/////////////////////////////////////////////
// �{�X�̍U���̑S�̊Ǘ�(�\��)
void BossAttackDisp() {
	switch (g_boss[0].attackFlg)
	{
	case ENEMY_DROP:
		BossEnemyDropDisp();	// �ア�G���o��
		break;

	default:
		break;
	}
	

	
}
// �{�X�̍U���̑S�̊Ǘ�(����)
void BossAttackMove() {
	switch (g_boss[0].attackFlg)
	{
	case ENEMY_DROP:
		BossEnemyDropMove();	// �ア�G���o��
		break;

	default:
		break;
	}
	
}
/*********************************************

* �{�X���ア�G���o���U��������֐�

*/////////////////////////////////////////////
// �ア�G���o��(�\��)
void BossEnemyDropDisp() {

	static int enemypop_MAX = 0;
		
	for (int i = 0; i < enemypop_MAX; i++) {
		DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
		
		
	}
}
// �ア�G���o��(����(�����蔻��Ȃ�))
void BossEnemyDropMove() {

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