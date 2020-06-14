#pragma once
#include "DxLib.h"
#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Map.h"
#include "Player.h"

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
#define	BOSS_THREAD_WIDTH	(6)			// 糸の横幅
#define	BOSS_CLOUD_HEIGHT  (134)		// 雲の高さ
#define BOSS_STAGE5_WIDTH  (324)		// ボス５の幅
#define BOSS_STAGE5_HEIGHT (415)		// ボス５の縦
#define BOSS_STAGE6_WIDTH  (89.6 + 179.2)		//ボス６の横 (PLAYER_WIDTH * PLAYER_REDUCTION) + (PLAYER_WIDTH * PLAYER_REDUCTION)
#define BOSS_STAGE6_HEIGHT (PLAYER_HEIGHT + 70)	// ボス６の縦
#define BOSS_STAGELAST_WIDTH  (537)		// ラスボスの幅
#define BOSS_STAGELAST_HEIGHT (660)		// ラスボスの縦

#define YAMATANO_NECK        (7)        // ラスボス前の７体の蛇

#define BOSS_WAVE_WIDTH      (200)		// 波の横幅
#define BOSS_WAVE_HEIGHT     (150)      // 波の高さ

#define BOSS_TON_HEIGHT      (70)		// 舌の高さ

#define BOSS_WAVE_WIDTH		 (200)		// 津波の横幅
#define BOSS_WAVE_HEIGHT	 (150)		// 津波の縦幅
/***********************************************************

// 定数の宣言

***********************************************************/
const int BOSSFULL_WIDTH[MAP_MAX] = {BOSS_WIDTH, BOSS_STAGE2_WIDTH, BOSS_STAGE3_WIDTH, BOSS_STAGE4_WIDTH, BOSS_STAGE5_WIDTH, BOSS_STAGE6_WIDTH, BOSS_STAGELAST_WIDTH };
const int BOSSFULL_HEIGHT[MAP_MAX] = { BOSS_HEIGHT, BOSS_STAGE2_HEIGHT, BOSS_STAGE3_HEIGHT, BOSS_STAGE4_HEIGHT, BOSS_STAGE5_HEIGHT, BOSS_STAGE6_HEIGHT, BOSS_STAGELAST_HEIGHT };
const int KURAGE_MAX = 4;	// クラゲの最大数
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
	BOSS_LASTBOSS,
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
	BOSSATTACK_MINIKURAGE_AIR,			// 空中のミニクラゲの攻撃(Boss_MiniKurage_Drop関数をボスに入れないと使えない)
	BOSSATTACK_MINIKURAGE_GROUND,		// 地上のミニクラゲの攻撃(Boss_MiniKurage_Drop関数をボスに入れないと使えない)
	BOSSATTACK_TACKLE,					// ボスのタックル攻撃
	BOSSATTACK_RUSH,					// ボスの突進攻撃
	BOSSATTACK_LONG_RANGE,				// ボスの遠距離攻撃
	BOSSATTACK_MAX,                     // ボスの攻撃の最大数
};

enum {    // ラスボスの攻撃判断

	LAST_BOSSATTACK_WATER_BULLET,            // ラスボス用の水弾
	LAST_BOSSATTACK_ENEMY_DROP,              // ラスボス用の歩く雑魚敵
	LAST_BOSSATTACK_LONGTON,                 // ラスボス用の舌
	LAST_BOSSATTACK_MINISPIDER_DROP,         // ラスボス用のミニ蜘蛛
	LAST_BOSSATTACK_MINICLOUD_DROP,          // ラスボス用のミニ雲
	LAST_BOSSATTACK_LIGHTNING,               // ラスボス用の雷撃
	LAST_BOSSATTACK_MINIKURAGE,				 // ラスボス用のミニクラゲ攻撃
	LAST_BOSSATTACK_SHADOW,					 // ラスボス用の影による攻撃
	LAST_BOSSATTACK_MAX,                     // ラスボスの攻撃の最大数
};

enum { // ボスの動きパターン
	BOSSMOVE_NOMOTION,		// ノーモーション
	BOSSMOVE_ATTACK,		// ボスがSin波で攻めてくる
	BOSSMOVE_SPEEDDOWN,		// ボスがプレイヤーに追いつかれる動き
	BOSSMOVE_DOWN,			// 攻撃、移動ができない状態
};

enum {	// ボス３のジャンプフラグ操作
	BOSS_3_JUMPOFF,
	BOSS_3_JUMPON,
	BOSS_3_DOWN,
};
enum {	// ラスボス前の７体の蛇
	LASTBOOS_OFF,        // 出現していない
	LASTBOSS_ON,         // 出現している
	LASTBOSS_MINIKILL,   // 倒しているけど画面にいる
	LASTBOSS_KILL,       // 倒した
	LASTBOSS_MINION,     // 出現しているけど、攻撃できない
};

enum {    // ラスボス前の７体の蛇の出現している場所のタグ
	TAG_BOSS_LEFT,        // 左にいる
	TAG_BOSS_RIGHT,       // 右にいる
};
struct lasbossInfo : public bossInfo {    // ラスボス前の７体の蛇の情報
	int w;		// X座標
	int h;		// Y座標
	int tag;	// 右にいるか左にいるかのタグ
	int sevenAttackFlg;    // 攻撃しているかどうかを真か偽で判断する TRUE:攻撃する FALSE: 攻撃していない
	int anima;	// アニメーション用のメンバ
	int animaMax;	// アニメーション用最大数
	int animaMin;	// アニメーション用最小数
	void lasbossInit(int num);// 初期化
};

struct shadow : picInfo {				// ラスボス前の最後の敵の影の情報

	bool shadowDispFlg;		// 影の表示に使用するフラグ	TRUE:表示	FALSE:非表示
	bool attackDispFlg;		// 影の遠距離攻撃表示に使用するフラグ	TRUE:表示	FALSE:非表示
	int preparationCnt;		// 予備動作時間
	int attackx;
	int attacky;
	int attackw;
	int attackh;

	void ShadowInit(int bx, int by = (GROUND - PLAYER_HEIGHT), bool randFlg = FALSE) {	// 影の位置を初期化

		shadowDispFlg = FALSE;
		attackDispFlg = FALSE;
		preparationCnt = 0;
		x = bx - PLAYER_WIDTH / 2;
		y = GROUND - 280 * PLAYER_REDUCTION;
		w = PLAYER_WIDTH * PLAYER_REDUCTION;
		h = PLAYER_HEIGHT;
		/*w = 490;
		h = 230;*/
		//if (randFlg == TRUE) {
		//	y = by - 
		//}
	}
	void LongRangeInit(int bx, int by = (GROUND - 40/*PLAYER_HEIGHT*/), bool randFlg = FALSE) {

		shadowDispFlg = FALSE;
		attackDispFlg = FALSE;
		preparationCnt = 0;
		attackx = bx - 200;
		attacky = GROUND - 80;
		attackw = 150;
		attackh = PLAYER_HEIGHT / 2;
	}
};

struct boss4_parts :public picInfo {	//ボス４の雲と糸の情報 
	int hp;					// 糸のｈｐ
	bool dispFlg;			// 糸を表示判断するフラグ
	void ThreadInit() {
		Boss4_ThreadInit();	// 糸の初期化
		hp = 2;
		dispFlg = TRUE;
	}
	void ThreadReSet(int cloudX, int cloudY) {		// くもの糸を雷雲に合わせて再セット
		x = cloudX - (BOSS_THREAD_WIDTH / 2) + 265 / 2;
		y = cloudY + (BOSS_CLOUD_HEIGHT / 2);
		w = cloudX + (BOSS_THREAD_WIDTH / 2) + 265 / 2;
	}

};
struct bossAttackInfo {	// ボスの攻撃の際に使う可能性あり
	int x, y;

};
struct boss5_extension :public bossInfo {	// ボス５の変数拡張 
	int anime;
	bool attackFlg;
	bool animeFlg;
	void AnimtionInit() {
		anime = 0;
		attackFlg == FALSE;
	}
};

struct rightningInfo {        // 雷撃の情報
	int x = 419;                // X座標の初期化
	int y = 180;                // Y座標の初期化
	int cnt;					//
	float exRate;				// 

};
//struct barrier : public picInfo {
//	bool flg;	// 出現フラグ
//	int cnt;	// 出現カウント
//
//	// barriarを初期化するメソッド
//	void barrierInit() {
//		x = g_boss[g_select_Stage].x - 100;	// X座標の初期位置
//		y = g_boss[g_select_Stage].y + 10;	// Y座標の初期位置
//
//		flg = FALSE;	// 出現フラグを初期化	
//		cnt = 0;		// 出現カウントを初期化
//	}
//};
/***********************************************************

// グローバル変数の宣言

***********************************************************/
extern bossInfo g_boss[MAP_MAX];		// ボスの情報
extern boss4_parts g_boss4_Cloud;		// ボス４の雲の情報
extern boss4_parts g_boss4_Thread;		// ボス４の糸の情報
extern trapInfo g_wave;                 // 波の情報
extern picInfo g_boss3_Ton;             // 舌の情報
extern lasbossInfo g_boss_Yamatano[YAMATANO_NECK];    // ラスボス前の７体の蛇
extern bool g_lastBoss_StartAnimeFlg;    // ラスボス前の出現アニメーションを行うフラグ TRUE:アニメーションを行う FALSE:行わない
extern boss5_extension g_boss5_Ex;		// ボス５の変数拡張
//extern barrier g_barrier;				// バリアの情報
extern rightningInfo g_rightning;		// 雷撃の情報
extern shadow g_boss_shadow;			// 影の攻撃の情報
extern int g_boss4_JumpAnime;			// カエルのジャンプするアニメーション
/***********************************************************

// 関数の宣言

***********************************************************/
int InputRand(int rand1, int rand2, int rand3);	// 数字を引数として三つ取り、その中の一つをランダムで返す
int InputHyperRand(int rand1, int rand2, int rand3 = 0, int rand4 = 0, int rand5 = 0, int rand6 = 0, int rand7 = 0, int rand8 = 0);
bool BossDamageCheck(int bossHp);				// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない
void Boss_Damage_Disp(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// ボスがダメージを食らったモーションをする
void Boss_Damage_Disp2(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// ボスがダメージを食らったモーションをする2
void Boss_Damage_Disp3(bool* boss_damage, int bx, int by, int GrHandle, double magnification);	// ボスがダメージを食らったモーションをする3
bool BossNoAttackCheck(int bossAttackFlg);		// ボスが攻撃を終えたかを調べる関数TRUE: ボスの攻撃終了 FALSE: ボスは攻撃中、または終了してしばらくたっている
bool BossDropAttackCheck(int bossAttackFlg);	// ボスがエネミーをドロップするかを調べる関数TRUE: ボスの攻撃開始 FALSE: ボスは攻撃中、または終了してしばらくたっている
void Boss_MiniKurage_DropFlg();					// ミニクラゲを出すフラグ管理
void KurageHit();								// プレイヤーがクラゲに当たるとダメージを受ける

void LastBossRightNingAnime();            // 
void Last_Boss_SnakeDispFlg_Managar();    // 

void BossDisp_Stage1();					// ステージ１のボスの表示
void BossMove_Stage1();					// ステージ１のボスの動き
void BossDisp_Stage2();					// ステージ２のボスの表示
void BossMove_Stage2();					// ステージ２のボスの動き
void BossDisp_Stage3();					// ステージ３のボスの表示
void BossMove_Stage3();					// ステージ３のボスの動き
void BossDisp_Stage4();					// ステージ４のボスの表示
void BossMove_Stage4();					// ステージ４のボスの動き
void BossDisp_Stage5();					// ステージ５のボスの表示
void BossMove_Stage5();					// ステージ５のボスの動き
void BossDisp_Stage6();					// ステージ６のボスの表示
void BossMove_Stage6();					// ステージ６のボスの動き
void BossDisp_Stage_Last();				// ラスボス表示
void BossMove_Stage_Last();				// ラスボス動き

void Boss_Knock_Down();					// ボスが倒される処理
void Boss_Snake_Knockdown();            // ラスボス前の７体の蛇が倒される処理
void Snake_Add_To_Anime();				// 蛇の追加アニメーション

void BossInit();						// ボスの初期化
void Boss_Stage4_Init();				// ボス４の雲の初期化
void LastBossInit();                    // ラスボス前の７体の蛇の初期化
void Boss5_Init();						// ボス５の初期化
void Boss6_Init();						// ボス６の初期化

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
void Boss_MiniKurage_Drop_Disp();		// ボスエリアのミニクラゲの表示
void Boss_MiniKurage_Drop_Move();		// ボスエリアのミニクラゲの動き
void BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage);		// ミニクラゲの空中突撃！
void BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage);	// ミニクラゲの地上攻撃！
void Boss_Tackle_Disp();				// ボスがタックルする表示
void Boss_Tackle_Move();				// ボスがタックルする動き
void ThreadMove(int* moveFlg);          // くもの糸の内部処理
void SpiderNoThreadMove(int* moveFlg);  // くもの糸が切れた時の動き
void Boss_Rush_Disp();					// 影の突進攻撃
void Boss_Rush_Move();					// 影の突進攻撃
void Boss_LongRange_Disp();				// 影の遠距離攻撃
void Boss_LongRange_Move();				// 影の遠距離攻撃

void (* const BossDisp[MAP_MAX])() = {		// ボスの表示
	BossDisp_Stage1,
	BossDisp_Stage2,
	BossDisp_Stage3,
	BossDisp_Stage4,
	BossDisp_Stage5,
	BossDisp_Stage6,
	BossDisp_Stage_Last,
};

void (* const BossMove[MAP_MAX])() = {		// ボスの動き
	BossMove_Stage1,
	BossMove_Stage2,
	BossMove_Stage3,
	BossMove_Stage4,
	BossMove_Stage5,
	BossMove_Stage6,
	BossMove_Stage_Last,
};


void YmatanoSeven_Disp();	// ラスボス前の７体の蛇の描画(攻撃系のみ)
void YmatanoSeven_Move();	// ラスボス前の７体の蛇の動き
void LastBoss_Disp();		// ラスボス
void LastBoss_Move();

// ミニクラゲの空中攻撃
void Last_BossMiniKurage_Attack_Air(int attackKurageBuf_Air, bool* ataackFlg_AirKurage);
// ミニクラゲの地上攻撃
void Last_BossMiniKurage_Attack_Ground(int attackKurageBuf_Ground, bool* attackFlg_GroundKurage);

void Last_Boss_Attack_WaterBullet_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ラスボス用の水弾表示
void Last_Boss_Attack_WaterBullet_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ラスボス用の水弾動き
void Last_Boss_Attack_BossEnemyDrop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);  // ラスボス用の歩く雑魚敵の表示
void Last_Boss_Attack_BossEnemyDrop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);  // ラスボス用の歩く雑魚敵の動き
void Last_Boss_Attack_BossLongTon_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ラスボス用の舌表示
void Last_Boss_Attack_BossLongTon_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);    // ラスボス用の舌動き
void Last_Boss_Attack_MiniSpider_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);// ラスボス用のミニ蜘蛛表示
void Last_Boss_Attack_MiniSpider_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);// ラスボス用のミニ蜘蛛動き
void Last_Boss_Attack_MiniCloud_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);	// ラスボス用のミニ雲の表示
void Last_Boss_Attack_MiniCloud_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);	// ラスボス用のミニ雲の動き
void Last_Boss_Attack_Lightning_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ラスボス用の雷撃の表示
void Last_Boss_Attack_Lightning_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ラスボス用の雷撃の表示
void Last_Boss_MiniKurage_Drop_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ラスボス用のミニクラゲのの表示
void Last_Boss_MiniKurage_Drop_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);		// ラスボス用のミニクラゲのの表示
void Last_Boss_Shadow_Attack_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);			// ラスボス用の影の表示
void Last_Boss_Shadow_Attack_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);			// ラスボス用の影の表示



/***********************************************************

// ラスボス前の７体の蛇の攻撃

***********************************************************/
// 表示
void (* const Last_Yamatano_Boss_Attack_Disp[LAST_BOSSATTACK_MAX])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ラスボス用の攻撃表示管理

		Last_Boss_Attack_WaterBullet_Disp,
		Last_Boss_Attack_BossEnemyDrop_Disp,
		Last_Boss_Attack_BossLongTon_Disp,
		Last_Boss_Attack_MiniSpider_Drop_Disp,
		Last_Boss_Attack_MiniCloud_Drop_Disp,
		Last_Boss_Attack_Lightning_Disp,
		Last_Boss_MiniKurage_Drop_Disp,
		Last_Boss_Shadow_Attack_Disp,
};
// 動き
void (* const Last_Yamatano_Boss_Attack_Move[LAST_BOSSATTACK_MAX])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ラスボス用の攻撃動き管理

		Last_Boss_Attack_WaterBullet_Move,
		Last_Boss_Attack_BossEnemyDrop_Move,
		Last_Boss_Attack_BossLongTon_Move,
		Last_Boss_Attack_MiniSpider_Drop_Move,
		Last_Boss_Attack_MiniCloud_Drop_Move,
		Last_Boss_Attack_Lightning_Move,
		Last_Boss_MiniKurage_Drop_Move,
		Last_Boss_Shadow_Attack_Move,
};

/***********************************************************

// ラスボスの本体の攻撃

***********************************************************/
void Last_Boss_Attack_Null_Disp(int bx, int by, int* boss_AttackFlg, int* coolTime);	// 攻撃をしない
void Last_Boss_Attack_Null_Move(int bx, int by, int* boss_AttackFlg, int* coolTime);	// 攻撃をしない
void (* const Last_Boss_Attack_Disp[LAST_BOSSATTACK_MAX + 1])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ラスボス用の攻撃表示管理
		Last_Boss_Attack_Null_Disp,
		Last_Boss_Attack_WaterBullet_Disp,
		Last_Boss_Attack_BossEnemyDrop_Disp,
		Last_Boss_Attack_BossLongTon_Disp,
		Last_Boss_Attack_MiniSpider_Drop_Disp,
		Last_Boss_Attack_MiniCloud_Drop_Disp,
		Last_Boss_Attack_Lightning_Disp,
		Last_Boss_MiniKurage_Drop_Disp,
		Last_Boss_Shadow_Attack_Disp,
};
// 動き
void (* const Last_Boss_Attack_Move[LAST_BOSSATTACK_MAX + 1])(int bx, int by, int* boss_AttackFlg, int* coolTime) {    // ラスボス用の攻撃動き管理
		Last_Boss_Attack_Null_Move,
		Last_Boss_Attack_WaterBullet_Move,
		Last_Boss_Attack_BossEnemyDrop_Move,
		Last_Boss_Attack_BossLongTon_Move,
		Last_Boss_Attack_MiniSpider_Drop_Move,
		Last_Boss_Attack_MiniCloud_Drop_Move,
		Last_Boss_Attack_Lightning_Move,
		Last_Boss_MiniKurage_Drop_Move,
		Last_Boss_Shadow_Attack_Move,
};


