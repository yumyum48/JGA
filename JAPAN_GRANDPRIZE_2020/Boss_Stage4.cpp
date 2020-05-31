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

struct rightningInfo {		// 雷撃の情報
	int x = 419;				// X座標
	int y = 180;				// Y座標
	int cnt;	// ボス４の雷撃が来るまでのカウント
	float exRate;		// 拡大率

};

/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
rightningInfo g_rightning;	// 雷撃の情報
/*********************************************

* ステージ３のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage4() {
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
	//g_boss4_Cloud.x = g_mouseInfo.mouseX;
	//g_boss4_Cloud.y = g_mouseInfo.mouseY;
	//g_boss4_Cloud.w = g_boss4_Cloud.x + bw;
	//g_boss4_Cloud.h = g_boss4_Cloud.y + bh;
	

	g_rightning.exRate = (float)g_rightning.cnt / 500.0F;
	
	// 雲の表示
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	// 雷撃の充電
	DrawRotaGraph(g_boss4_Cloud.x + ((g_boss4_Cloud.w - g_boss4_Cloud.x )/ 2), g_boss4_Cloud.y + ((g_boss4_Cloud.h - g_boss4_Cloud.y) / 2), g_rightning.exRate, 0.0, g_pic.enemy_walk[0], TRUE);
	// 糸の表示
	DrawBox(g_boss4_Thread.x, g_boss4_Thread.y, g_boss4_Thread.w, g_boss4_Thread.h, 0xFFFFFF, TRUE);
	// 蜘蛛の表示
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

	//Poison_Trap_Disp();	// 毒のトラップの表示

	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば
		BossAttackDisp();	// ボスの攻撃
	}
	DrawFormatString(600, 200, 0xFFFFFF, "cnt = %d", g_rightning.cnt);
}


// 動き(これクラスのがよくね？?ね？)メモ：ブラッシュアップでボスが円を描くようにジャンプさせる
void BossMove_Stage4() {
	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	static int attackSelect = 0;							// ボスの攻撃選択
	static int attackFlgBuf = g_boss[BOSS_STAGE4].attackFlg;// １フレーム前のボスのattackフラグを記憶する

	if ((coolTime++ > 60)												// 硬直時間
		&& (g_boss[BOSS_STAGE4].attackFlg == 0)							// ボスが攻撃していなければ
		&& (moveFlg == BOSSMOVE_NOMOTION)) {							// ボスが移動していなければ


		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {					// ボスが攻撃しないときに召喚する雑魚敵の初期化
			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);	
		}
						
		int enumSet = BOSSATTACK_MINICLOUD_DROP;
		if (g_rightning.cnt >= 1800)									// 雷撃のカウントが30秒以上なら雷撃を落とさせる準備をする
			enumSet = BOSSATTACK_LIGHTNING;

		attackSelect = InputRand(BOSSATTACK_MINISPIDER_DROP, enumSet, 0);			//乱数で攻撃するか移動をするかを決定

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;												// クールタイム初期化
		}
		else {	// 攻撃をしないとき
			g_trap.dispFlg = TRUE;	// トラップを出す

		}
	}
	// トラップを生成する時にトラップを初期化
	if (BossDropAttackCheck(g_trap.dispFlg) == TRUE) {
		g_trap.WaveInit(g_boss[BOSS_STAGE4].x);
	}
	//// バッファーと比べて雑魚敵生成してないときは雑魚敵を初期化
	//if (BossNoAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// バッファーと比べて雑魚敵生成する時雑魚敵を初期化
	//if (BossDropAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
	//	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
	//		g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//		g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
	//	}
	//}
	//// 攻撃無しで行動
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	//	BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	//}

	// 攻撃
	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば

		BossAttackMove();	// ボスの攻撃
	}

	//Poison_Trap_Move();	// 毒のトラップの動き
	//if (g_boss4_Rightning_Cnt >= 1800) {		// カウントを１の差でDispの部分を制御
	//	g_boss4_Rightning_Cnt = 1799;
	//}

	// 雷撃を落とすカウントボスが雷撃を落としていなければカウント
	if(g_boss[BOSS_STAGE4].attackFlg != BOSSATTACK_LIGHTNING)
		g_rightning.cnt++;
	if (g_rightning.cnt > 1800 && g_boss[BOSS_STAGE4].attackFlg != BOSSATTACK_LIGHTNING) {
		g_rightning.cnt = 1800;
	}
	Boss_Knock_Down();	// ボスが倒されてる処理
}

void Boss_Lightning_Disp() {
	
	static int stopCnt = 0;	// 雷撃を表示させる時間


	if (g_rightning.cnt <= 0) {
		DrawBox(g_rightning.x, g_rightning.y, g_rightning.x + 526, g_rightning.y + 488, 0x00FFFF, TRUE);
		g_rightning.cnt = 0;
		stopCnt++;
	}
	
	if (stopCnt >= 90) {
		g_rightning.cnt = 0;					 // 雷撃までのカウントを初期化
		g_boss[g_select_Stage].attackFlg = 0;    // attackフラグを初期化
		stopCnt = 0;							 // 雷撃の表示カウントを初期化
	}
}
void Boss_Lightning_Move() {

	g_rightning.cnt-= 50;


}
// ボス４の必要な情報の初期化
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
	g_boss4_Thread.ThreadInit();
}