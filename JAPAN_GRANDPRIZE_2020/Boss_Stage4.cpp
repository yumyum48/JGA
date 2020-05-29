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
	// ボスの大きさ測るメーター
	static int bw = 0;
	static int bh = 0;
	if (g_keyInfo.nowKey & PAD_INPUT_UP) {
		bh--;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_RIGHT) {
		bw++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_DOWN) {
		bh++;
	}
	else if (g_keyInfo.nowKey & PAD_INPUT_LEFT) {
		bw--;
	}

	DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	
	DrawBox(g_mouseInfo.mouseX, g_mouseInfo.mouseY, g_mouseInfo.mouseX + bw, g_mouseInfo.mouseY + bh, 0x00FF00, TRUE);
	//g_boss4_Cloud.x = g_mouseInfo.mouseX;
	//g_boss4_Cloud.y = g_mouseInfo.mouseY;
	//g_boss4_Cloud.w = g_boss4_Cloud.x + bw;
	//g_boss4_Cloud.h = g_boss4_Cloud.y + bh;
	DrawBox(g_boss4_Cloud.x, g_boss4_Cloud.y, g_boss4_Cloud.w, g_boss4_Cloud.h, 0xFFFFFF, TRUE);
	DrawBox(g_boss[BOSS_STAGE4].x, g_boss[BOSS_STAGE4].y, g_boss[BOSS_STAGE4].x + BOSS_STAGE4_WIDTH, g_boss[BOSS_STAGE4].y + BOSS_STAGE4_HEIGHT, 0x00FF00, TRUE);

	//if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば
	//	BossAttackDisp();	// ボスの攻撃
	//}
}


// 動き(これクラスのがよくね？?ね？)メモ：ブラッシュアップでボスが円を描くようにジャンプさせる
void BossMove_Stage4() {
	////static int coolTime = 0;								// 硬直時間
	////static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	////static int attackSelect = 0;							// ボスの攻撃選択
	////static int attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;// １フレーム前のボスのattackフラグを記憶する

	//static int coolTime = 0;						// 硬直時間
	//int boss_MaxDown = 290;							// ボス３の落下した際のY地点
	//static int boss_JumpFlg = BOSS_3_JUMPOFF;		// ボスのジャンプをするフラグ0: 下降する地面なら座標変わらずそのまま　1:ジャンプする 2: 下降する
	//int boss_startX = 822;							// ボス３のX座標の初期値


	//int num = GetRand(2);
	//if (BossAttackCheck(g_boss[BOSS_STAGE4].attackFlg) == TRUE)	// ボスが前フレームで攻撃をしていたかを確認
	//	num = 1;	// していれば、座標調整のため強制ジャンプ

	////	ボスがジャンプをするのか攻撃をするのかを判断する(乱数で決定)
	//if ((g_boss[BOSS_STAGE4].y >= boss_MaxDown)
	//	&& (coolTime++ >= 15)
	//	&& (boss_JumpFlg == BOSS_3_JUMPOFF)
	//	&& (g_boss[BOSS_STAGE4].attackFlg == 0)) {	// 地面にいるとき クールタイムが一定時間たっているとき ボスがジャンプしている時　ボスが攻撃していないとき

	//	if (num == 0) {
	//		g_boss[BOSS_STAGE4].attackFlg = BOSSATTACK_LONGTON;	// 舌を伸ばす攻撃
	//	}
	//	else {
	//		boss_JumpFlg = BOSS_3_JUMPON;
	//	}

	//}
	////coolTime = 0;
	//int jumpTypeflg = 0;	// 0なら真上 1ならX座標を修正しながら戻る
	//if (g_boss[BOSS_STAGE4].x < boss_startX) {
	//	jumpTypeflg = 1;
	//}
	//else {
	//	g_boss[BOSS_STAGE4].x = boss_startX;
	//	jumpTypeflg = 0;
	//}
	//Boss_3_Jump(&coolTime, &boss_JumpFlg, jumpTypeflg);

	//if (g_boss[BOSS_STAGE4].attackFlg != 0) {						// ボスが攻撃していれば
	//	BossAttackMove();	// ボスの攻撃

	//}

	//Boss_Knock_Down();
}
// ボス４の必要な情報の初期化
void Boss_Stage4_Init() {
	g_boss4_Cloud.Boss4_CloudInit();
}