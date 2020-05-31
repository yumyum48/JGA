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
#define BOSS_STAGE3_WIDTH  (128 * 3.5)// ボスの横幅
#define BOSS_STAGE3_HEIGHT (128 * 3.5)// ボスの縦幅
#define BOSS_STAGE4_WIDTH  (314)
#define BOSS_STAGE4_HEIGHT (286)

/***********************************************************

// 定数の宣言

***********************************************************/
const int BOSSFULL_WIDTH[MAP_MAX] = {BOSS_WIDTH, BOSS_STAGE2_WIDTH, BOSS_STAGE3_WIDTH, BOSS_STAGE4_WIDTH};
const int BOSSFULL_HEIGHT[MAP_MAX] = { BOSS_HEIGHT, BOSS_STAGE2_HEIGHT, BOSS_STAGE3_HEIGHT, BOSS_STAGE4_HEIGHT};
/***********************************************************

// 列挙体の宣言

***********************************************************/
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
	BOSSATTACK_ENEMY_DROP = 1,			// 雑魚敵の生成
	BOSSATTACK_WATER_BULLET,			// 水弾での攻撃
	BOSSATTACK_WAVE_ATTACK,				// 津波での攻撃
	BOSSATTACK_JUMPANDPOISON,			// カエルのジャンプと稀に毒を出す攻撃
	BOSSATTACK_LONGTON,					// 舌を伸ばす攻撃
	BOSSATTACK_MINISPIDER_DROP,			// ミニスパイダーをドロップする
	BOSSATTACK_MINICLOUD_DROP,			// ミニ雲をドロップする
	BOSSATTACK_LIGHTNING,				// 雷撃による攻撃
	BOSSATTACK_POISON_TRAP,				// 毒のトラップを設置
};

enum { // ボスの動きパターン
	BOSSMOVE_NOMOTION,		// ノーモーション
	BOSSMOVE_ATTACK,		// ボスがSin波で攻めてくる
	BOSSMOVE_SPEEDDOWN,		// ボスがプレイヤーに追いつかれる動き
};

enum {	// ボス３のジャンプフラグ操作
	BOSS_3_JUMPOFF,
	BOSS_3_JUMPON,
	BOSS_3_DOWN,
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
bool BossNoAttackCheck(int bossAttackFlg);		// ボスが攻撃を終えたかを調べる関数TRUE: ボスの攻撃終了 FALSE: ボスは攻撃中、または終了してしばらくたっている
bool BossDropAttackCheck(int bossAttackFlg);	// ボスがエネミーをドロップするかを調べる関数TRUE: ボスの攻撃開始 FALSE: ボスは攻撃中、または終了してしばらくたっている
void BossDisp_Stage1();					// ステージ１のボスの表示
void BossMove_Stage1();					// ステージ１のボスの動き
void BossDisp_Stage2();					// ステージ２のボスの表示
void BossMove_Stage2();					// ステージ２のボスの動き
void BossDisp_Stage3();					// ステージ３のボスの表示
void BossMove_Stage3();					// ステージ３のボスの動き
void BossDisp_Stage4();					// ステージ４のボスの表示
void BossMove_Stage4();					// ステージ４のボスの動き

void Boss_Knock_Down();					// ボスの当たり判定

void BossInit();						// ボスの初期化
void Boss_Stage4_Init();				// ボス４の雲の初期化

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
void BossLongTon_Disp();				// ボスが舌を伸ばして攻撃する攻撃の表示
void BossLongTon_Move();				// ボスが舌を伸ばして攻撃する動き
void Boss_MiniSpider_Drop_Disp();		// ミニ蜘蛛を出す攻撃の表示
void Boss_MiniSpider_Drop_Move();		// ミニ蜘蛛を出す攻撃の動き
void Boss_MiniCloud_Drop_Disp();		// ミニ雲を出す攻撃の表示
void Boss_MiniCloud_Drop_Move();		// ミニ雲を出す攻撃の動き
void Boss_Lightning_Disp();				// 雷撃の表示
void Boss_Lightning_Move();				// 雷撃の動き
void Poison_Trap_Disp();				// 毒のトラップの表示
void Poison_Trap_Move();				// 毒のトラップの動き
bool Boss_3_Jump(int* coolTime, int* boss_JumpFlg, int jumpType);	// TRUE: ジャンプ終了 FALSE: ジャンプ開始	// ボス３のジャンプ (jumpTypeは０を入れると通常ジャンプ、１を入れるとずれたX座標を修正しながらジャンプ)
void (* const BossDisp[4])() = {		// ボスの表示
	BossDisp_Stage1,
	BossDisp_Stage2,
	BossDisp_Stage3,
	BossDisp_Stage4,

};

void (* const BossMove[4])() = {		// ボスの動き
	BossMove_Stage1,
	BossMove_Stage2,
	BossMove_Stage3,
	BossMove_Stage4,
};

