#include "Boss.h"
#include "DxLib.h"
#include "Struct.h"
#include "Picture.h"
#include "enemy.h"
#include "GamePlay.h"
#include "Player.h"
#include "control.h"
#include "Controler.h"
#include "Select.h"
#include "GameScene.h"
#include "Init.h"
#include "Trap.h"


/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////

/*********************************************

* ステージ５のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage5() {
	//// ボスの大きさ測るメーター
	//static int bw = 0;
	//static int bh = 0;
	//if (g_keyInfo.nowKey & PAD_INPUT_UP) {
	//	bh--;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
	//	bw++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
	//	bh++;
	//}
	//else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
	//	bw--;
	//}

	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);


	DrawBox(g_boss[BOSS_STAGE5].x, g_boss[BOSS_STAGE5].y, g_boss[BOSS_STAGE5].x + BOSS_STAGE5_WIDTH, g_boss[BOSS_STAGE5].y + BOSS_STAGE5_HEIGHT, 0x00FFFF, TRUE);
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// ボスが攻撃していれば
	//	BossAttackDisp();	// ボスの攻撃
	//}
	
}

// 動き(これクラスのがよくね？?ね？)メモ：ブラッシュアップでボスが円を描くようにジャンプさせる
void BossMove_Stage5() {
	//static int coolTime = 0;								// 硬直時間
	//static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	//static int attackSelect = 0;							// ボスの攻撃選択
	//static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// １フレーム前のボスのattackフラグを記憶する

	//if ((coolTime++ > 60)												// 硬直時間
	//	&& (g_boss[BOSS_STAGE4].attackFlg == 0)							// ボスが攻撃していなければ
	//	&& (moveFlg == BOSSMOVE_NOMOTION)) {							// ボスが移動していなければ


	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// ボスが攻撃しないときに召喚する雑魚敵の初期化
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}

	//	attackSelect = InputRand(0, 0, 0);			//乱数で攻撃するか移動をするかを決定

	//	if (attackSelect != 0) {
	//		g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
	//		coolTime = 0;												// クールタイム初期化
	//	}
	//	else {	// 攻撃をしないとき
	//		g_trap.dispFlg = TRUE;	// トラップを出す

	//	}
	//}
	//// トラップを生成する時にトラップを初期化
	//if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
	//	g_trap.WaveInit(g_boss[BOSS_STAGE4].x);
	//}
	////// バッファーと比べて雑魚敵生成してないときは雑魚敵を初期化
	////if (BossNoAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	////	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	////		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////	}
	////}
	////// バッファーと比べて雑魚敵生成する時雑魚敵を初期化
	////if (BossDropAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	////	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	////		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	////	}
	////}
	////// 攻撃無しで行動
	////if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	////	BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	////}

	//// 攻撃
	//if (g_boss[BOSS_STAGE5].attackFlg != 0) {						// ボスが攻撃していれば

	//	BossAttackMove();	// ボスの攻撃
	//}

	////Poison_Trap_Move();	// 毒のトラップの動き
	////if (g_boss4_Rightning_Cnt >= 1800) {		// カウントを１の差でDispの部分を制御
	////	g_boss4_Rightning_Cnt = 1799;
	////}

	//
	//Boss_Knock_Down();	// ボスが倒されてる処理
}
