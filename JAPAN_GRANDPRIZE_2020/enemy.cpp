#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int walkEnemy_pop = 0;		// �G�̍ő吔
int flyEnemy_pop = 0;

int g_coolTime = 0;

// �G�̕`��
void EnemyDisp() {
	
	// �����G�l�~�[��(�o���ő吔-��ԃG�l�~�[)��菬������Ε����G�l�~�[���o��
	//if (walkEnemy_pop < ENEMY_MAX - flyEnemy_pop) {
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
	//}
	// �G�̐���z��ɋL��
	//g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)		//�n��̓G�`��
			DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//�󒆂̓G�`��
			//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 0.2, 0.0, g_pic.enemy, TRUE);
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50,0x00ff00,TRUE);
	}
}

// �G�̓���
void EnemyMove() {

	for (int i = 0; i < ENEMY_MAX; i++) {		//�n��̓G
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= 10;
			g_enemy[i].walk.y = GROUND;
		}

		if (g_enemy[i].walk.x+(574*0.2) < 0) {
			/*for (int j = 0; j < walkEnemy_pop - 1; j++) {
				g_enemy[i + j].walk = g_enemy[i + j + 1].walk;
			}
			walkEnemy_pop -= 1;*/

			//g_enemy[i].walk.flg = FALSE;

			g_enemy[i].walk.Init();
		}

		//if (g_button.circleButton == true) g_enemy[i].walk.Init();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {		//�󒆂̓G
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= 12;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.Init();
		}

	}
}

// �G�̏�����
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.Init();
	}
	walkEnemy_pop = 0;
}

// �{�X�̕`��
void BossDisp() {
	// ���u��
	//DrawBox()
	
}

// �{�X�̓���
void BossMove () {

}
