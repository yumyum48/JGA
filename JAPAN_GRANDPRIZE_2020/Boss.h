#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"

enum {	// ボスの配列
	BOSS_STAGE1,
	BOSS_STAGE2,
	BOSS_STAGE3,
	BOSS_STAGE4,
	BOSS_STAGE5,
	BOSS_STAGE6,
	BOSS_STAGE7,
	BOSS_STAGE8,
	BOSS_MAX,
};

enum {	// ボスの攻撃判断
	ENEMY_DROP = 1,			// 雑魚敵の生成
	WATER_BULLET,			// 水弾での攻撃
};

enum { // ボスの動きパターン
	BOSSMOVE_NOMOTION,		// ノーモーション
	BOSSMOVE_SPEEDDOWN,		// ボスが追い付かれる動き
};

extern bossInfo g_boss[MAP_MAX];		// ボスの情報

#define BOSS_WIDTH	(280 * 2)				// ボスの横幅
#define BOSS_HEIGHT	(200 * 2)				// ボスの縦幅

void BossDisp_Stage1();					// ステージ１のボスの表示
void BossMove_Stage1();					// ステージ１のボスの動き
void BossDisp_Stage2();					// ステージ２のボスの表示
void BossMove_Stage2();					// ステージ２のボスの動き

void Boss_Knock_Down();					// ボスの当たり判定

void BossInit();						// ボスの初期化

void BossAttackDisp();					// ボスの攻撃
void BossAttackMove();					// ボスの攻撃

// ボスのスキルの表示
void BossEnemyDropDisp();				// 弱い敵を出すボス専用の技の関数
void BossWaterBulletDisp();				// 水弾で攻撃するボス専用の技の関数
// ボスのスキルの動き
void BossEnemyDropMove();				// 弱い敵を出すボス専用の技の関数
void BossMoveMotion(int *coolTime, int *moveFlg);		//
void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg);
void BossWaterBulletMove();				// 水弾で攻撃するボス専用の技の関数
void (* const BossDisp[2])() = {		// ボスの表示
	BossDisp_Stage1,
	BossDisp_Stage2,
};

void (* const BossMove[2])() = {		// ボスの動き
	BossMove_Stage1,
	BossMove_Stage2,
};

