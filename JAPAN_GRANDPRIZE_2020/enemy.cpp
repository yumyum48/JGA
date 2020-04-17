#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int walkEnemy_pop = 0;		// 敵の最大数
int flyEnemy_pop = 0;

int g_coolTime = 0;

// 敵の描画
void EnemyDisp() {
	
	// 歩くエネミーが(出現最大数-飛ぶエネミー)より小さければ歩くエネミーを出す
	//if (walkEnemy_pop < ENEMY_MAX - flyEnemy_pop) {
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
	//}
	// 敵の数を配列に記憶
	//g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//空中の敵描画
			//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 0.2, 0.0, g_pic.enemy, TRUE);
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50,0x00ff00,TRUE);
	}
}

// 敵の動き
void EnemyMove() {

	for (int i = 0; i < ENEMY_MAX; i++) {		//地上の敵
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
	for (int i = 0; i < ENEMY_MAX; i++) {		//空中の敵
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= 12;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.Init();
		}

	}
}

// 敵の初期化
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.Init();
	}
	walkEnemy_pop = 0;
}

// ボスの描画
void BossDisp() {
	// 仮置き
	//DrawBox()
	
}

// ボスの動き
void BossMove () {

}
