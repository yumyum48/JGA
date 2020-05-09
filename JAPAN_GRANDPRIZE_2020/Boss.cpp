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
void Boss_Knock_Down() {
	
	if (g_boss[g_select_Stage].hp <= 0) {
		g_gameScene = GAME_STAGE_CLEAR;
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

* ボスが水弾で攻撃をする関数

*/////////////////////////////////////////////
// 水弾の描画
void BossWaterBulletDisp() {
	const int animationMax = 4;
	static int anime = 0;
	static int time = 0;

	if (anime >= animationMax)anime = 0;

	if (anime < animationMax) {
		if (time++ % 300 == 299)anime++;
	}

	//DrawGraph(500, 250, g_pic.waterBullet[anime], TRUE);
	DrawRotaGraph(g_boss[0].x, g_boss[0].y, 3.0f, DX_PI_F / 180 * 340, g_pic.waterBullet[anime], TRUE, FALSE);

}
// 水弾の内部的な動き
void BossWaterBulletMove() {

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
	for (int i = BOSS_STAGE1; i < BOSS_MAX; i++) {
		g_boss[i].Init_Stage(i);
	}
	
}