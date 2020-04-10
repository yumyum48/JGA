#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int enemy_MAX = 0;		// “G‚ÌÅ‘å”
void EnemyDisp() {
	
	static int cnt = 0;
	if(cnt++ %  10 == 0)
		enemy_MAX += 1;

	// “G‚Ì”‚ğ”z—ñ‚É‹L‰¯
	g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < enemy_MAX; i++) {
		DrawRotaGraph(g_enemy[i].x, g_enemy[i].y, 0.2, 0.0, g_pic.enemy, TRUE);
	}
}

void EnemyMove() {

	
	for (int i = 0; i < enemy_MAX; i++) {
		g_enemy ->x = 100;
		if (i == 1) {
			g_enemy->x = 150;
		}
		g_enemy->y = 450;
		//g_enemy[i].x -= 10.0F;
		//if (g_enemy[i].x < 0) g_enemy[i].x = 1200;

		//if (g_button.circleButton == true) g_enemy[i].x = 1200;
	}
}

void EnemyInit() {
	for (int i = 0; i < enemy_MAX; i++)
		g_enemy[i].Init();
	enemy_MAX = 0;
}
