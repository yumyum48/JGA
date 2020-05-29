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
#include "HP.h"

#define BOSS_WAVE_WIDTH		200		// 津波の横幅
#define BOSS_WAVE_HEIGHT	150		// 津波の縦幅

trapInfo g_wave;
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
	
	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// ボスが攻撃していれば
		//g_boss[BOSS_STAGE2].x = 700;
		//g_boss[BOSS_STAGE2].y = 160;
		BossAttackDisp();	// ボスの攻撃
	}


}

// 動き
void BossMove_Stage2() {
	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる
	static int attackSelect = 0;							// ボスの攻撃選択
	static int attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;// １フレーム前のボスのattackフラグを記憶する

	if ((coolTime++ > 60)									// 硬直時間
		&& (g_boss[BOSS_STAGE2].attackFlg == 0)							// ボスが攻撃していなければ
		&& (moveFlg == BOSSMOVE_NOMOTION)) {					// ボスが移動していなければ
		
		attackSelect = InputRand(0, BOSSATTACK_ENEMY_DROP, BOSSATTACK_ENEMY_DROP);								//乱数で攻撃するか移動をするかを決定

		if (attackSelect != 0) {
			g_boss[BOSS_STAGE2].attackFlg = attackSelect;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;
		}
		else {	// 攻撃をしないとき
			moveFlg = BOSSMOVE_SPEEDDOWN;

		}
	}

	if (attackFlgBuf == 0 && g_boss[BOSS_STAGE2].attackFlg == BOSSATTACK_ENEMY_DROP) {
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			g_enemy[i].walk.BossAreaWlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
		}
	}
	if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

		BossMoveMotion(&coolTime, &moveFlg);	// ボスの移動スピードをだんだんと落とす
	}

	
	if (g_boss[BOSS_STAGE2].attackFlg != 0) {						// ボスが攻撃していれば
		//g_boss[BOSS_STAGE2].x = 700;
		//g_boss[BOSS_STAGE2].y = 160;
		BossAttackMove();	// ボスの攻撃
	}


	// バッファーにボスのattackフラグを格納
	attackFlgBuf = g_boss[BOSS_STAGE2].attackFlg;
	Boss_Knock_Down();
}

// ボスがジャンプして津波を発生
void BossGenerateWave() {
	const float gravity = 1;				// ジャンプに掛かる重力
	const int rise = 3;						// ジャンプ時の上昇力
	static int animationMax[2] = { 0, 0 };	// アニメーション最後尾	0:ボスジャンプ	1:津波
	static int anime[2] = { 0, 0 };			// 現在表示している画像	0:ジャンプ  1:津波
	//static int g_noDamegeCnt = 60;			// ダメージを受け付けない時間
	static int time = 0;					// アニメーション用時間変数
	static float moveY = 0;					// 重力の加算用変数
	static bool jumpFlg = FALSE;			// ボスがジャンプ済みかの判断用変数	TRUE:ジャンプ済み 

	// ボスがジャンプするアニメーション
	if (g_wave.dispFlg == FALSE) {

		// アニメーションの加算
		if (time++ % 12 == 11)anime[0]++;
		if (anime[0] > animationMax[0])anime[0] = 0;

		if (anime[0] < 1
			&& jumpFlg == FALSE) {
			g_boss[BOSS_STAGE2].x -= g_speedLevel;
		}
		else {
			jumpFlg = TRUE;
		}

		// ジャンプ中の挙動
		if (jumpFlg == TRUE) {
			moveY += gravity;

			if (g_boss[BOSS_STAGE2].y <= 397) {
				g_boss[BOSS_STAGE2].x += g_speedLevel;
				g_boss[BOSS_STAGE2].y -= rise + moveY;
			}
			if (g_boss[BOSS_STAGE2].y > 397) {
				g_boss[BOSS_STAGE2].y = 397;
				g_wave.dispFlg = TRUE;			// 津波を発生
			}
		}

	}

	// 津波のアニメーション
	if (g_wave.dispFlg == TRUE) {
		g_wave.x -= g_speedLevel;

		// 津波の描画
		DrawBox(g_wave.x, g_wave.y,
			g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT, 0x0000FF, TRUE);

		// 津波がプレイヤーに当たった際の処理
		if (g_noDamageCnt >= 60
			&& PlayerHitCheck(g_wave.x, g_wave.y,
				g_wave.x + BOSS_WAVE_WIDTH, g_wave.y + BOSS_WAVE_HEIGHT) == 1) {

			g_noDamageCnt = 0;
			if (g_player.barrierFlg == FALSE) --g_player.hp;
			else g_player.barrierFlg = FALSE;
			g_boss[BOSS_STAGE2].attackFlg = 0;
		}

		// 津波が画面外に出る処理
		if (g_wave.x + BOSS_WAVE_WIDTH < 0) {
			jumpFlg = FALSE;
			g_wave.dispFlg = FALSE;
			g_boss[BOSS_STAGE2].attackFlg = 0;
		}
	}

}

