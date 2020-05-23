#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"

/***********************************************************

// マクロの定義

***********************************************************/
#define BOSS_WIDTH			(280 * 2)		// ボスの横幅
#define BOSS_HEIGHT			(200 * 2)		// ボスの縦幅
#define BOSS_AREA_ENEMY_MAX (3)				// ボス戦のエネミーが出現する最大数
#define BOSS_STAGE2_WIDTH (271)		// ボスの横幅
#define BOSS_STAGE2_HEIGHT (271)	// ボスの縦幅
#define BOSS_STAGE3_WIDTH (380)
#define BOSS_STAGE3_HEIGHT (380)

/***********************************************************

// 定数の宣言

***********************************************************/
const int BOSSFULL_WIDTH[MAP_MAX] = {BOSS_WIDTH, BOSS_STAGE2_WIDTH, BOSS_STAGE3_WIDTH};
const int BOSSFULL_HEIGHT[MAP_MAX] = { BOSS_HEIGHT, BOSS_STAGE2_HEIGHT, BOSS_STAGE3_HEIGHT };
/***********************************************************

// 列挙体の宣言

***********************************************************/
enum {	// ボスの配列
	BOSS_STAGE1
	
	,
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
	BOSSATTACK_ENEMY_DROP = 1,			// 雑魚敵の生成
	BOSSATTACK_WATER_BULLET,			// 水弾での攻撃
	BOSSATTACK_WAVE_ATTACK,			// 津波での攻撃
	BOSSATTACK_JUMPANDPOISON,			// カエルのジャンプと稀に毒を出す攻撃
	BOSSATTACK_LONGTON,					// 舌を伸ばす攻撃
};

enum { // ボスの動きパターン
	BOSSMOVE_NOMOTION,		// ノーモーション
	BOSSMOVE_ATTACK,		// ボスがSin波で攻めてくる
	BOSSMOVE_SPEEDDOWN,		// ボスがプレイヤーに追いつかれる動き
};

struct bossAttackInfo {	// ボスの攻撃の際に使う可能性あり
	int x, y;

};
/***********************************************************

// グローバル変数の宣言

***********************************************************/
extern bossInfo g_boss[MAP_MAX];		// ボスの情報

/***********************************************************

// 関数の宣言

***********************************************************/
int InputRand(int rand1, int rand2, int rand3);	// 数字を引数として三つ取り、その中の一つをランダムで返す
bool BossDamageCheck(int bossHp);				// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない
void BossDisp_Stage1();					// ステージ１のボスの表示
void BossMove_Stage1();					// ステージ１のボスの動き
void BossDisp_Stage2();					// ステージ２のボスの表示
void BossMove_Stage2();					// ステージ２のボスの動き
void BossDisp_Stage3();					// ステージ３のボスの表示
void BossMove_Stage3();					// ステージ３のボスの動き

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
void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg);	// ボス１の隙モーション
void BossMoveMotion_Pattern2(int* coolTime, int* moveFlg);	// ボス２の隙モーション
void BossWaterBulletMove();				// 水弾で攻撃するボス専用の技の関数
void BossAreaEnemyMove();				// ボスが出現しているときの雑魚の動き
void BossAreaEnemyDisp();				// ボスが出現しているときの雑魚の表示
void BossGenerateWave();				// ボスが津波を発生させて攻撃
void BossJumpOrPoison_Disp();			// ボスがジャンプして稀に毒を出す表示		
void BossJumpOrPoison_Move();			// ボスがジャンプして稀に毒を出す動き

void (* const BossDisp[3])() = {		// ボスの表示
	BossDisp_Stage1,
	BossDisp_Stage2,
	BossDisp_Stage3,
};

void (* const BossMove[3])() = {		// ボスの動き
	BossMove_Stage1,
	BossMove_Stage2,
	BossMove_Stage3,
};

