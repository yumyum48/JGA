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

#define BOSS_STAGE2_WIDTH (271)		// ボスの横幅
#define BOSS_STAGE2_HEIGHT (271)	// ボスの縦幅
/*********************************************

* ステージ２のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage2() {
	// ボスの大きさ測るメーター
	/*static int bw = 0;
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
	}*/
	//DrawFormatString(300, 300, 0xFF0000, "bw = %d \n bh = %d", bw, bh);
	//DrawBox(g_mouseInfo.mouseX, g_mouseInfo.monseY, g_mouseInfo.mouseX + bw, g_mouseInfo.monseY + bh, 0x00FF00, TRUE);

	//DrawRotaGraph(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, 0.9f, 0.0, g_pic.enemy_walk[0], FALSE, TRUE);
	DrawBox(g_boss[BOSS_STAGE2].x, g_boss[BOSS_STAGE2].y, g_boss[BOSS_STAGE2].x + BOSS_STAGE2_WIDTH, g_boss[BOSS_STAGE2].y + BOSS_STAGE2_HEIGHT, 0x00FF00, TRUE);
	
}

// 動き
void BossMove_Stage2() {
	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	static int attackSelect = 0;							// ボスの攻撃選択


	if ((coolTime++ > 120)									// 硬直時間
		&& (g_boss[BOSS_STAGE2].attackFlg == 0)							// ボスが攻撃していなければ
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// ボスが移動していなければ

		attackSelect = InputRand(0, 2, 3);								//乱数で攻撃するか移動をするかを決定

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE2].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;
		}
		else {	// 攻撃をしないとき
			//moveFlg = BOSSMOVE_SPEEDDOWN;

		}
	}

	//if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

	//	BossMoveMotion(&coolTime, &moveFlg);
	//}


	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// ボスが攻撃していれば
		g_boss[BOSS_STAGE2].x = 700;
		g_boss[BOSS_STAGE2].y = 160;
		BossAttackMove();	// ボスの攻撃
	}

	Boss_Knock_Down();
}


