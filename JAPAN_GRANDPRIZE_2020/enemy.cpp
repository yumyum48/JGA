#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

void EnemyDisp() {
	int enemy_MAX;	// ìGÇÃêî
	DrawRotaGraph(g_enemy[0].x, g_enemy[0].y, 0.2, 0.0, g_pic.enemy, TRUE);

}

void EnemyMove() {
	g_enemy[0].x -= 10.0F;
	if (g_enemy[0].x < 0) g_enemy[0].x = 1200;

	if (g_button.circleButton == true) g_enemy[0].x = 1200;
}

void EnemyInit() {
	g_enemy[0].Init();
}
