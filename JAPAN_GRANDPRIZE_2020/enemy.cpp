#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

int walkEnemy_pop = 0;		// “G‚ÌÅ‘å”
int flyEnemy_pop = 0;

void EnemyDisp() {
	
	//static int cnt = 0;
	//if (cnt++ % 10 == 0) {
	if (walkEnemy_pop < ENEMY_MAX) {
		if (GetRand(10) == 5) walkEnemy_pop += 1;
	}
	//}
	// “G‚Ì”‚ğ”z—ñ‚É‹L‰¯
	//g_enemy = new enemyInfo[enemy_MAX];

	for (int i = 0; i < walkEnemy_pop; i++) {
		DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
	}
}

void EnemyMove() {

	for (int i = 0; i < walkEnemy_pop; i++) {
		g_enemy[i].walk.x -= 10;
		g_enemy[i].walk.y = GROUND;

		if (g_enemy[i].walk.x < 0) {
			for (int j = 0; j < ENEMY_MAX - 1; j++) {
				g_enemy[i + j].walk.x = g_enemy[i + j + 1].walk.x;
			}
			walkEnemy_pop -= 1;
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
