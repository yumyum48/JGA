#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"

enemyInfo g_enemy;

void EnemyDisp() {
	DrawRotaGraph(g_enemy.x, g_enemy.y, 0.2, 0.0, g_pic.enemy, TRUE);

}

void EnemyMove() {
	g_enemy.x -= 10.0F;
	if (g_enemy.x < 0) g_enemy.x = 1200;

	if (g_button.circleButton == true) g_enemy.x = 1200;
}

void EnemyInit() {
	g_enemy.Init();
}
