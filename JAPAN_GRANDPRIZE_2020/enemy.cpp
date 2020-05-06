#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"
int g_coolTime = 0;

// �ア�G�A�{�X�̕\��
void MonsterDisp() {
	if (g_enemybeat <= 1) {
		EnemyDisp();					// �ア�G�̕`��
	}
	else {
		BossDisp[0]();					// �{�X�̕\��
	}
}

// �ア�G�A�{�X�̓���
void MonsterMove() {
	if (g_enemybeat <= 1) {
		EnemyMove();					// �ア�G�̓���
	}
	else {
		BossMove[0]();					// �{�X�̓���
	}
}

// �ア�G�̕`��
void EnemyDisp() {

	
	// �G���o�������鏀��
	if (++g_coolTime > 10) {
		if (GetRand(80) == 1) {		//�n��̓G
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
						g_enemy[i].walk.flg = TRUE;
						g_coolTime = 0;
						break;
						//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//�󒆂̓G
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					g_coolTime = 0;
					break;
				}
			}
		}
	}

	// �ア�G�̕\��
	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)		//�n��̓G�`��
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//�󒆂̓G�`��
			//DrawRotaGraph2(g_enemy[i].fly.x, g_enemy[i].fly.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50,0x00ff00,TRUE);
	}
}

// �ア�G�̓���
void EnemyMove() {
	// �G�����Ȃ��Ƃ��{�X�̓������N��

	for (int i = 0; i < ENEMY_MAX; i++) {		//�n��̓G�̓���
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= g_speedLevel+3;
			//g_enemy[i].walk.y = GROUND;
		}

		if (g_enemy[i].walk.x+ENEMY_WIDTH < 0) {
			/*for (int j = 0; j < walkEnemy_pop - 1; j++) {
				g_enemy[i + j].walk = g_enemy[i + j + 1].walk;
			}
			walkEnemy_pop -= 1;*/

			//g_enemy[i].walk.flg = FALSE;

			g_enemy[i].walk.WalkInit();
		}

		//if (g_button.circleButton == true) g_enemy[i].walk.Init();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {		//�󒆂̓G�̓���
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= g_speedLevel+3;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.FlyInit();
		}

	}
}

// �ア�G�̏�����
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.WalkInit();
		g_enemy[i].fly.FlyInit();
	}
	
	g_coolTime = 0;
}

