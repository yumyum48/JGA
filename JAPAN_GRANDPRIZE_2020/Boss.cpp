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
#include "Macro.h"
#define _USE_MATH_DEFINES
#include <math.h>


/*********************************************

* ステージ１のボス

*/////////////////////////////////////////////
// 描画
void BossDisp_Stage1() {
	//	水玉が遅い
	// 二次元配列の0番目は敵本体
	// １番目は水玉
	int bossAnime_MAX[2] = { 7, 15};	// アニメーションの最終尾
	int bossAnime_Start[2] = { 0, 8 };	// アニメーションの最初
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
	case BOSSMOVE_ATTACK:
		BossMoveMotion_Pattern1(coolTime, moveFlg);		// ボスがサインはで接近
		break;

	case BOSSMOVE_SPEEDDOWN:
		BossMoveMotion_Pattern2(coolTime, moveFlg);		// ボスのX軸が左に寄っていく
		break;
	default:
		break;
	}

}

void BossMoveMotion_Pattern1(int* coolTime, int* moveFlg) {
	static bool teleportFlg = FALSE;

	if (g_boss[g_select_Stage].x > -BOSS_WIDTH
		&& teleportFlg == FALSE) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// 横の振れ幅
		g_boss[g_select_Stage].y -= sin(angle) * 10;			// 縦の振れ幅
		g_boss[g_select_Stage].x -= 5;						// ボスの移動量
	}
	else if(g_boss[g_select_Stage].x <= -BOSS_WIDTH){
		g_boss[g_select_Stage].x = WINDOW_WIDTH + BOSS_WIDTH;
		g_boss[g_select_Stage].y = 160;
		teleportFlg = TRUE;
	}

	if (teleportFlg == TRUE
		&& g_boss[g_select_Stage].x > 700) {
		float angle;
		angle = DX_TWO_PI / 120 * g_boss[0].x;	// 横の振れ幅
		g_boss[g_select_Stage].y -= sin(angle) * 10 - 0.8;			// 縦の振れ幅
		g_boss[g_select_Stage].x -= 5;						// ボスの移動量
	}
	else if (teleportFlg == TRUE) {
		*coolTime = 0;
		*moveFlg = BOSSMOVE_NOMOTION;
		teleportFlg = FALSE;
	}
}

void BossMoveMotion_Pattern2(int* coolTime, int* moveFlg) {
	static int chanceTime = 0;
	static bool speedUpFlg = FALSE;
	// ボスの移動スピードをだんだんと落とす
	if (g_boss[g_select_Stage].x >= g_player.x + PLAYER_WIDTH && speedUpFlg == FALSE) {
		g_boss[g_select_Stage].x -= 2;
		if (BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE) {				// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない
			speedUpFlg = TRUE;
		}
	}
	else if(chanceTime++ >= 120 || BossDamageCheck(g_boss[g_select_Stage].hp) == TRUE){	// プレイヤーの目の前に来たら、攻撃できるようにチャンスタイムを作る
		speedUpFlg = TRUE;			// 二秒立ったら、またはプレイヤーが攻撃をしたらボス２がスピードアップして元の位置まで戻る
	}
	if (speedUpFlg == TRUE && g_boss[g_select_Stage].x < 823) {
		g_boss[BOSS_STAGE2].x += 2;	// ボスを最初の位置へと戻す
	}
	else if (g_boss[g_select_Stage].x >= 823) {
		g_boss[g_select_Stage].x = 823;	// 最初の場所に戻ったら座標を固定
		*coolTime = 0;					// クールタイム初期化
		*moveFlg = 0;					// moveFlg初期化
		speedUpFlg = FALSE;				// スピードアップフラグを初期化
	}
}
/*********************************************

* ボスの当たり判定	// 当たるとプレイヤーhp減少

*/////////////////////////////////////////////
void Boss_Knock_Down() {
	
	if (g_boss[g_select_Stage].hp <= 0) {
		g_gameScene = GAME_STAGE_CLEAR;
		g_select_MAX++;	// セレクトできるマップを増やす
	}
	
}
/*********************************************

* ボスの攻撃関係

*/////////////////////////////////////////////
// ボスの攻撃の全体管理(表示)
void BossAttackDisp() {
	
	
	switch (g_boss[g_select_Stage].attackFlg) {
		case ENEMY_DROP:
		
			BossEnemyDropDisp();	// 弱い敵を出す
			//DrawFormatString(100, 600, 0xFF00FF, "ボスが攻撃してますよ！");
			//g_boss[BOSS_STAGE1].attackFlg = 0;
			break;

		case WATER_BULLET:
			BossWaterBulletDisp();	// 水弾の発射
			break;

		default:
			break;
	}
	

	
}
// ボスの攻撃の全体管理(動き)
void BossAttackMove() {

	//DrawFormatString(100, 700, 0xFF00FF, "ボスが攻撃してますよ！");

	//if (g_keyInfo.keyFlg & PAD_INPUT_4) g_boss[0].attackFlg = 0;

	switch (g_boss[g_select_Stage].attackFlg) {
		case ENEMY_DROP:
			BossEnemyDropMove();	// 弱い敵を出す
			//g_boss[g_select_Stage].attackFlg = 0;
			break;

		case WATER_BULLET:
			BossWaterBulletMove();	// 水弾の発射
			break;

		default:
			break;
	}
	
}
/*********************************************

* ボスが弱い敵を出す攻撃をする関数

*/////////////////////////////////////////////
// 歩く弱い敵を出す(表示)
void BossEnemyDropDisp() {
	
	BossAreaEnemyDisp();
}
// 弱い敵を出す(動き(当たり判定など))
void BossEnemyDropMove() {

	BossAreaEnemyMove();
	
}
// ボスが出現しているときの雑魚の表示
void BossAreaEnemyDisp() {
	static int coolTime = 0;
	static int enemyDropCnt = 0;
	static bool enemy_dispFlg_Buf[BOSS_AREA_ENEMY_MAX] = { FALSE, FALSE, FALSE }; // フラグの前情報をバッファーに入れてTRUEからFALSEになった弱い敵をカウントして「３」だったら戻す
	// 敵を出現させる準備
	if (++coolTime > 30) {
		//地上の敵
		for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {
			if (g_enemy[i].walk.flg == FALSE && enemyDropCnt < 3) {
				g_enemy[i].walk.flg = TRUE;
				coolTime = 0;
				enemyDropCnt++;
				enemy_dispFlg_Buf[i] = TRUE;
				break;
			}
		}
	}

	// 弱い敵の表示
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// 雑魚敵たちのアニメーション
		if (time++ % 8 == 0) {
			g_enemy[i].walk.anime++;
			g_enemy[i].fly.anime++;
		}

		// アニメーションのループ
		if (g_enemy[i].walk.anime > animation_Max)g_enemy[i].walk.anime = 0;


		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 敵撃破時のアニメーション 
	EnemyEvaporation();
	if (enemyDropCnt >= 3) {
		static int waitTime = 0;
		if (waitTime++ >= 120) {
			g_boss[g_select_Stage].attackFlg = 0;	// 弱い敵が３体倒された、または避けられたことを確認したら攻撃フラグを0に戻す
			enemyDropCnt = 0;							// 倒された、または避けられたエネミーをカウントする変数を初期化
			enemy_dispFlg_Buf[0] = { FALSE };		// バッファー配列の初期化
			enemy_dispFlg_Buf[1] = { FALSE };
			enemy_dispFlg_Buf[2] = { FALSE };
			waitTime = 0;
		}
	}

}
// ボスが出現しているときの雑魚の動き
void BossAreaEnemyMove() {
	static int enemyCnt;		// 弱い敵を倒した、または避けた数をカウント
	

	for (int i = 0; i < BOSS_AREA_ENEMY_MAX; i++) {		//地上の敵の動き
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= g_speedLevel + 3;
				

		}
		/*if (enemy_dispFlg_Buf[i] == TRUE && g_enemy[i].walk.flg == FALSE) {
			enemyCnt++;
		}*/
		if (g_enemy[i].walk.x + ENEMY_WIDTH < 0) {

			g_enemy[i].walk.BossAreaWlakInit(g_boss[g_select_Stage].x, g_boss[g_select_Stage].y);
			//g_enemy[i].walk.flg = TRUE;
		}

	}
}
/*********************************************

* ボスが水弾で攻撃をする関数

*/////////////////////////////////////////////
// 水弾の描画
void BossWaterBulletDisp() {
	static int animationMax = 3;			// アニメーション
	static int anime = 0;				// アニメ推移
	static int time = 0;				// 経過時間
	static int startX = g_boss[BOSS_STAGE1].x + 100,
				startY = g_boss[BOSS_STAGE1].y + 200;	// 水弾の初期位置
	static float moveX = 0, moveY = 0;	// 水弾の移動量
	static int noDamegeCnt = 60;		// ダメージを受け付けない時間
	static bool attackFlg = FALSE;		// 攻撃判断フラグ	 treu:攻撃済  false:未攻撃

	// フレーム単位の被弾数の調整
	if (noDamegeCnt++ < 60);
	
	DrawBox(startX + moveX - 40, startY + moveY + 0,
		startX + moveX + 40, startY + moveY - 20, 0xFFFFFF, FALSE);
	// プレイヤーに水弾が当たった時の処理
	if (noDamegeCnt >= 60
		&& (PlayerHitCheck(startX + moveX - 40, startY + moveY + 0,
			startX + moveX + 40, startY + moveY - 20) == TRUE)) {
		g_player.hp--;
		noDamegeCnt = 0;
		anime = 4;
		animationMax++;
		attackFlg = TRUE;
		if (noDamegeCnt >= 200) {
			g_boss[BOSS_STAGE1].attackFlg = 0;
		}
	}

	// 水弾が画面外に出たときの処理
	if ((startY + moveY) / 2 > GROUND
		|| (startX + moveX - 60) < 0) {
		attackFlg = TRUE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}

	// 水弾のアニメーション
	if (anime < animationMax) {
		if (time++ % 15 == 14)anime++;
	}

	// 水弾の表示
	if (attackFlg == FALSE) {
		moveX -= 7.5;
		moveY += 2.5;
		/*moveX -= 3.0;
		moveY += 1.0;*/
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[anime], TRUE, FALSE);
	}
	else if (attackFlg == TRUE) {
		DrawRotaGraph(startX + moveX, startY + moveY,
			3.0f, DX_PI_F / 180 * 335, g_pic.waterBullet[animationMax], TRUE, FALSE);
	}

	// 座標とフラグの初期化
	if (attackFlg == TRUE
		&& noDamegeCnt >= 20) {
		moveX = 0;
		moveY = 0;
		anime = 0;
		animationMax = 3;
		attackFlg = FALSE;
		g_boss[BOSS_STAGE1].attackFlg = 0;
	}



	// デバッグ
	//DrawFormatString(300, 720, 0x00FF00, "%f", moveX);
	//DrawFormatString(300, 735, 0x00FF00, "%f", moveY);
	//DrawFormatString(320, 780, 0x00FFFF, "%d", g_boss[BOSS_STAGE1].attackFlg);
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

/***********************************************************

// 数字を引数として三つ取り、その中の一つをランダムで返す

***********************************************************/
int InputRand(int rand1, int rand2, int rand3) {
	int num = GetRand(3);
	switch (num)
	{
	case 0: return rand1; break;
	case 1: return rand2; break;
	case 2: return rand3; break;
	default: return 0;	  break;
	}

}
/***********************************************************

// ボスがダメージを受けたかどうかを調べる関数 TRUE: ボスがダメージを受けた FALSE: ボスはダメージを受けていない

***********************************************************/
bool BossDamageCheck(int bossHp) {
	static int bossHpBuf = bossHp;

	if (bossHp <= bossHpBuf) {
		if (bossHp < bossHpBuf) {
			bossHpBuf = bossHp;
			return TRUE;
		}
	}

	bossHpBuf = bossHp;
	return FALSE;
}
