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
/*********************************************

* グローバル変数の宣言

*/////////////////////////////////////////////
picInfo g_boss4_Cloud;	// ボス４の雲の情報
picInfo g_boss4_Thread;	// ボス４の糸の情報
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
	

	// 雲の表示
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	// 糸の表示
	DrawBox(g_boss4_Thread.x, g_boss4_Thread.y, g_boss4_Thread.w, g_boss4_Thread.h, 0xFFFFFF, TRUE);
	// 蜘蛛の表示
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば
		BossAttackDisp();	// ボスの攻撃
	}
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

		attackSelect = InputRand(BOSSATTACK_MINISPIDER_DROP, BOSSATTACK_MINISPIDER_DROP, BOSSATTACK_MINISPIDER_DROP);			//乱数で攻撃するか移動をするかを決定

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE4].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;												// クールタイム初期化
		}
		//else {	// 攻撃をしないとき
		//	moveFlg = BOSSMOVE_SPEEDDOWN;

		//}
	}

	// バッファーと比べて雑魚敵生成してないときは雑魚敵を初期化
	if (BossAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE) {
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			g_enemy[i].cloud.BossArea_CloudInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, g_pic.enemy_fly[0]);
			g_enemy[i].spider.BossArea_SpiderInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y, g_pic.enemy_walk[0]);
		}
	}

	//// 攻撃無しで行動
	//if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	//	BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	//}

	// 攻撃
	if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば

		BossAttackMove();	// ボスの攻撃
	}

	Boss_Knock_Down();	// ボスが倒されてる処理
}
// ボス４の必要な情報の初期化
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
	g_boss4_Thread.Boss4_Thread();
}