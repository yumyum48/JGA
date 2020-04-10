#include "DxLib.h"
#include "Struct.h"
#include "Map.h"
#include "Init.h"
#include "Player.h"
#include "enemy.h"
#include "Rain.h"

void GameInit() {
	MapInit();
	PlayerInit();
	EnemyInit();
	RainInit();
}
