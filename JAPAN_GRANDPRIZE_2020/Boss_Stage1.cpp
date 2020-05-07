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

// ����
void BossMove_Stage1() {

	static int coolTime = 0;								// �d������
	static int moveFlg = BOSSMOVE_NOMOTION;					// �G���ړ����邾���̃t���O�@0:�ړ����Ȃ� 1:�㉺�Ɉړ����Ȃ���v���C���[�Ɋ���Ă���


	if ((coolTime++ > 120)									// �d������
		&& (g_boss[0].attackFlg == 0)							// �{�X���U�����Ă��Ȃ����
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// �{�X���ړ����Ă��Ȃ����

		if (GetRand(2) == 1) {								//�����ōU�����邩�ړ������邩������
			g_boss[0].attackFlg = ENEMY_DROP;				// �U������ꍇ�A�t���O�ɑΉ���������������
			coolTime = 0;
		}
		else {	// �U�������Ȃ��Ƃ�
			moveFlg = BOSSMOVE_SPEEDDOWN;

		}
	}

	if (moveFlg != BOSSMOVE_NOMOTION) {					// �s���p�^�[��

		BossMoveMotion(&coolTime, &moveFlg);
	}


	if (g_boss[0].attackFlg != 0) {						// �{�X���U�����Ă����
		g_boss[0].x = 700;
		g_boss[0].y = 160;
		BossAttackMove();	// �{�X�̍U��
	}

}

void Boss_Neutral_Motion() {

}