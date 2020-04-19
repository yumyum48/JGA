#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
int walkEnemy_pop = 0;		// 敵の最大数
int flyEnemy_pop = 0;

int g_coolTime = 0;

// 敵の描画
void EnemyDisp() {

	// ボスがいなければ敵を出す
	if (g_enemybeat < 10) {
		if (++g_coolTime > 10) {
			if (GetRand(80) == 1) {		//地上の敵
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (g_enemy[i].walk.flg == FALSE) {
						g_enemy[i].walk.flg = TRUE;
						g_coolTime = 0;
						break;
						//walkEnemy_pop += 1;
					}
				}
			}
			if (GetRand(150) == 1) {		//空中の敵
				for (int i = 0; i < ENEMY_MAX; i++) {
					if (g_enemy[i].fly.flg == FALSE) {
						g_enemy[i].fly.flg = TRUE;
						g_coolTime = 0;
						break;
					}
				}
			}
		}
	}
	else {
		BossDisp[0]();		// ボスの表示
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//空中の敵描画
			//DrawRotaGraph2(g_enemy[i].fly.x, g_enemy[i].fly.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50,0x00ff00,TRUE);
	}
}

// 敵の動き
void EnemyMove() {
	// 敵がいないときボスの動きを起動
	if (g_enemybeat >= 10) {
		BossMove[0]();		// ボスの動き
	}
	for (int i = 0; i < ENEMY_MAX; i++) {		//地上の敵の動き
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= 10;
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
	for (int i = 0; i < ENEMY_MAX; i++) {		//空中の敵の動き
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= 12;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.FlyInit();
		}

	}
}

// 敵の初期化
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.WalkInit();
		g_enemy[i].fly.FlyInit();
	}
	walkEnemy_pop = 0;
}

