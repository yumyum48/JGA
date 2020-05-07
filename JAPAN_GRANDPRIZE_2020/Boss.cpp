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

struct bossAttackInfo {	// ボスの攻撃の際に使う可能性あり
	int x, y;

};
/*********************************************

* ステージ１のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage1() {
	//	水玉が遅い
	// 二次元配列の0番目は敵本体
	// １番目は水玉
	int bossAnime_MAX[2] = { 3, 7};		// アニメーションの最終尾
	int bossAnime_Start[2] = { 0, 5 };	// アニメーションの最初
	static int anime[2] = { 0, 0 };		// 画像の切り替え
	static int time = 0;				// フレーム単位のカウント

	if (time++ % 4 == 0) anime[0]++;
	if (time % 6 == 0) anime[1]++;
	for (int i = 0; i < 2; i++) {
		if (anime[i] > bossAnime_MAX[i]) {
			anime[i] = bossAnime_Start[i];
		}
	}
		
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[1]], TRUE);
	DrawRotaGraph2(g_boss[0].x, g_boss[0].y, 0, 0, 2.0, 0.0, g_pic.boss_1_1[anime[0]], TRUE);

	if (g_boss[0].attackFlg != 0) {
		BossAttackDisp();	// ボスの攻撃
	}

}

// 動き
void BossMove_Stage1() {

	static int coolTime = 0;								// 硬直時間
	static int moveFlg = BOSSMOVE_NOMOTION;					// 敵が移動するだけのフラグ　0:移動しない 1:上下に移動しながらプレイヤーに寄ってくる


	if( (coolTime++ > 120 )									// 硬直時間
	&&  (g_boss[0].attackFlg == 0)							// ボスが攻撃していなければ
	&&  ( moveFlg == BOSSMOVE_NOMOTION) ){					// ボスが移動していなければ

		if (GetRand(2) == 1) {								//乱数で攻撃するか移動をするかを決定
			g_boss[0].attackFlg = ENEMY_DROP;				// 攻撃する場合、フラグに対応した数字を入れる
			coolTime = 0;
		}
		else {	// 攻撃をしないとき
			moveFlg = BOSSMOVE_SPEEDDOWN;
			
		}
	}

	if (moveFlg != BOSSMOVE_NOMOTION) {					// 行動パターン

		BossMoveMotion(&coolTime, &moveFlg);
	}


	if (g_boss[0].attackFlg != 0) {						// ボスが攻撃していれば
		g_boss[0].x = 700;
		g_boss[0].y = 160;
		BossAttackMove();	// ボスの攻撃
	}

}

void Boss_Neutral_Motion() {

}
/*********************************************

* ボスの動き達

*/////////////////////////////////////////////
// ボスの動きパターン
void BossMoveMotion(int *coolTime, int *moveFlg){

	switch (*moveFlg)
	{
	case BOSSMOVE_SPEEDDOWN:
		BossMoveMotion_Pattern1(coolTime, moveFlg);
		break;
	default:
		break;
	}

}

void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg) {
	if (g_boss[g_select_Stage].x > 0) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// 横の振れ幅
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// 縦の振れ幅
		g_boss[g_select_Stage].x -= 5;						// ボスの移動量
	}
	else {
		g_boss[g_select_Stage].x = 700;
		g_boss[g_select_Stage].y = 160;
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
	}
}
/*********************************************

* ボスの当たり判定	// 当たるとプレイヤーhp減少

*/////////////////////////////////////////////
void BossHit() {
	
	if (PlayerHitCheck(g_boss[0].x, g_boss[0].y, BOSS_WIDTH, BOSS_HEIGHT) == TRUE) {
		g_player.hp--;
	}
	
}
/*********************************************

* ボスの攻撃関係

*/////////////////////////////////////////////
// ボスの攻撃の全体管理(表示)
void BossAttackDisp() {
	
	
	switch (g_boss[0].attackFlg) {
		case ENEMY_DROP:
		
			BossEnemyDropDisp();	// 弱い敵を出す
			DrawFormatString(100, 600, 0xFF00FF, "ボスが攻撃してますよ！");
			break;

		default:
			break;
	}
	

	
}
// ボスの攻撃の全体管理(動き)
void BossAttackMove() {

	DrawFormatString(100, 700, 0xFF00FF, "ボスが攻撃してますよ！");

	if (g_keyInfo.keyFlg & PAD_INPUT_4) g_boss[0].attackFlg = 0;

	switch (g_boss[0].attackFlg) {
		case ENEMY_DROP:
			BossEnemyDropMove();	// 弱い敵を出す
			break;

		default:
			break;
	}
	
}
/*********************************************

* ボスが弱い敵を出す攻撃をする関数

*/////////////////////////////////////////////
// 弱い敵を出す(表示)
void BossEnemyDropDisp() {

	static int enemypop_MAX = 0;
		
	for (int i = 0; i < enemypop_MAX; i++) {
		DrawRotaGraph(g_enemy[i].walk.x, g_enemy[i].walk.y, 0.2, 0.0, g_pic.enemy, TRUE);
		
		
	}
}
// 弱い敵を出す(動き(当たり判定など))
void BossEnemyDropMove() {

}



/*********************************************

* ステージ３のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage3() {
	if (g_enemybeat >= 10) {
		DrawBox(600, 0, 1280, 768, 0x0FF000, TRUE);
	}
}
// 動き
void BossMove_Stage3() {

}

// ボスの初期化
void BossInit() {
	g_boss[BOSS_STAGE1].Init_Stage1();
	g_boss[BOSS_STAGE2].Init_Stage2();
	g_boss[BOSS_STAGE3].Init_Stage3();
	g_boss[BOSS_STAGE4].Init_Stage4();
	g_boss[BOSS_STAGE5].Init_Stage5();
	g_boss[BOSS_STAGE6].Init_Stage6();
	g_boss[BOSS_STAGE7].Init_Stage7();
	g_boss[BOSS_STAGE8].Init_Stage8();
}