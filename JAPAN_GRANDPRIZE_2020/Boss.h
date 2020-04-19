#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"

extern bossInfo g_boss[MAP_MAX];		// ボスの情報

#define BOSS_WIDTH	(200)				// ボスの横幅
#define BOSS_HEIGHT	(200)				// ボスの縦幅

void BossDisp_Stage1();					// ステージ１のボスの表示
void BossMove_Stage1();					// ステージ１のボスの動き

void BossHit();							// ボスの当たり判定
void BossAttack();						// ボスの攻撃

void BossInit();

void (* const BossDisp[1])() = {		// ボスの表示
	BossDisp_Stage1,
};

void (* const BossMove[1])() = {		// ボスの動き
	BossMove_Stage1,
};

