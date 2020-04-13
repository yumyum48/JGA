#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int enemy_pop = 0;		// “G‚ÌÅ‘å”

void EnemyDisp() {
	
	static int cnt = 0;
	if (cnt++ % 10 == 0) {
		if(enemy_pop < ENEMY_MAX) enemy_pop += 1;
		//if (enemy_pop >= ENEMY_MAX) enemy_pop = ENEMY_MAX;
	}
	
	// “G‚Ì”‚ğ”z—ñ‚É‹L‰¯
	//g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < enemy_pop; i++) {
		DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 0.2, 0.0, g_pic.enemy, TRUE);
		DrawFormatString(100 * i, 0, 0xff0000, "%d", g_enemy[0].x);
	}
}

void EnemyMove() {

	for (int i = 0; i < enemy_pop; i++) {
		g_enemy[i].x -= 10;
		/*if (i == 1) {
			g_enemy[i].x = 150;
		}*/
		g_enemy[i].y = 600;
		//g_enemy[i].x -= 10.0F;
		if (g_enemy[i].x < 0) g_enemy[i].x = 1280;

		if (g_button.circleButton == true) g_enemy[i].x = 1280;
	}
}

void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].Init();
	}
	enemy_pop = 0;
}
