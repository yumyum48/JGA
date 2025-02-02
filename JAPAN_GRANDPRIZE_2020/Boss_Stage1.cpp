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
#define _USE_MATH_DEFINES
#include <math.h>

// 動き
void BossMove_Stage1() {

	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	static int attackSelect = 0;							// ボスの攻撃選択


	if ((coolTime++ > 120)									// 硬直時間
		&& (g_boss[0].attackFlg == 0)							// ボスが攻撃していなければ
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// ボスが移動していなければ

		attackSelect = InputRand(0, 0, BOSSATTACK_WATER_BULLET);								//乱数で攻撃するか移動をするかを決定

		if (attackSelect != 0) {
			g_boss[0].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;
		}
		else {	// 攻撃をしないとき
			moveFlg = BOSSMOVE_ATTACK;

		}
	}

	if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

		BossMoveMotion(&coolTime, &moveFlg);
	}


	if (g_boss[0].attackFlg != 0) {						// ボスが攻撃していれば
		//g_boss[0].x = 700;
		//g_boss[0].y = 160;
		BossAttackMove();	// ボスの攻撃
	}

	// ボスがダメージを受けた瞬間DrawBoxを出す
	/*if (BossDamageCheck(g_boss[BOSS_STAGE1].hp) == 1) {
		DrawBox(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, 0x0000FF, TRUE);
	}*/
	Boss_Knock_Down();
}

void Boss_Neutral_Motion1() {

}