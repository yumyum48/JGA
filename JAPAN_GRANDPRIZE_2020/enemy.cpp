#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int walkEnemy_pop = 0;		// 敵の最大数
int flyEnemy_pop = 0;

void EnemyDisp() {
	
	// 歩くエネミーが(出現最大数-飛ぶエネミー)より小さければ歩くエネミーを出す
	//if (walkEnemy_pop < ENEMY_MAX - flyEnemy_pop) {
	if (GetRand(100) == 5) {
		for (int i = 0; i < ENEMY_MAX; i++) {
			if (g_enemy[i].walk.flg == FALSE) {
				g_enemy[i].walk.flg = TRUE;
				//walkEnemy_pop += 1;
			}
		}
	}
	//}
	//}
	// 敵の数を配列に記憶
	//g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)
			DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
	}
}

void EnemyMove() {

	for (int i = 0; i < walkEnemy_pop; i++) {
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= 10;
			g_enemy[i].walk.y = GROUND;
		}

		if (g_enemy[i].walk.x+(574*0.2) < 0) {
			/*for (int j = 0; j < walkEnemy_pop - 1; j++) {
				g_enemy[i + j].walk = g_enemy[i + j + 1].walk;
			}
			walkEnemy_pop -= 1;*/

			g_enemy[i].walk.flg = FALSE;

			g_enemy[i].walk.Init();
		}

		if (g_button.circleButton == true) g_enemy[i].walk.x = 1280;
	}
}

void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.Init();
	}
	walkEnemy_pop = 0;
}
