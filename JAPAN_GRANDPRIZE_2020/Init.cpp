#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"

void GameInit() {
	MapInit();
	PlayerInit();
	EnemyInit();
}
