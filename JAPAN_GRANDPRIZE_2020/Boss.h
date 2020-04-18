#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
	
void BossDisp_Stage1();						// ステージ１のボスの表示
void BossMove_Stage1();						// ステージ１のボスの動き
void (* const BossDisp[1])() = {		// ボスの表示
	BossDisp_Stage1,
};

void (* const BossMove[1])() = {		// ボスの動き
	BossMove_Stage1,
};
