#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"
int g_coolTime = 0;

// é„Ç¢ìGÅAÉ{ÉXÇÃï\é¶
void MonsterDisp() {
	if (g_enemybeat <= 1) {
		EnemyDisp();					// é„Ç¢ìGÇÃï`âÊ
	}
	else {
		BossDisp[0]();					// É{ÉXÇÃï\é¶
	}
}

// é„Ç¢ìGÅAÉ{ÉXÇÃìÆÇ´
void MonsterMove() {
	if (g_enemybeat <= 1) {
		EnemyMove();					// é„Ç¢ìGÇÃìÆÇ´
	}
	else {
		BossMove[0]();					// É{ÉXÇÃìÆÇ´
	}
}

// é„Ç¢ìGÇÃï`âÊ
void EnemyDisp() {

	
	// ìGÇèoåªÇ≥ÇπÇÈèÄîı
	if (++g_coolTime > 10) {
		if (GetRand(80) == 1) {		//ínè„ÇÃìG
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
						g_enemy[i].walk.flg = TRUE;
						g_coolTime = 0;
						break;
						//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//ãÛíÜÇÃìG
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					g_coolTime = 0;
					break;
				}
			}
		}
	}

	// é„Ç¢ìGÇÃï\é¶
	for (int i = 0; i < ENEMY_MAX; i++) {
		if(g_enemy[i].walk.flg == TRUE)		//ínè„ÇÃìGï`âÊ
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//ãÛíÜÇÃìGï`âÊ
			//DrawRotaGraph2(g_enemy[i].fly.x, g_enemy[i].fly.y, 0, 0, 0.2, 0.0, g_pic.enemy, TRUE);
			DrawBox(g_enemy[i].fly.x, g_enemy[i].fly.y, g_enemy[i].fly.x + 50, g_enemy[i].fly.y + 50,0x00ff00,TRUE);
	}
}

// é„Ç¢ìGÇÃìÆÇ´
void EnemyMove() {
	// ìGÇ™Ç¢Ç»Ç¢Ç∆Ç´É{ÉXÇÃìÆÇ´ÇãNìÆ

	for (int i = 0; i < ENEMY_MAX; i++) {		//ínè„ÇÃìGÇÃìÆÇ´
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
	for (int i = 0; i < ENEMY_MAX; i++) {		//ãÛíÜÇÃìGÇÃìÆÇ´
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= g_speedLevel+3;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.FlyInit();
		}

	}
}

// é„Ç¢ìGÇÃèâä˙âª
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.WalkInit();
		g_enemy[i].fly.FlyInit();
	}
	
	g_coolTime = 0;
}

