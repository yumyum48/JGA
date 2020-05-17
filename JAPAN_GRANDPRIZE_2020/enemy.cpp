#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"

enemyInfo g_enemyBuffer[ENEMY_MAX];	// 撃破した敵の情報を格納する変数

int g_coolTime = 0;

// 弱い敵、ボスの表示
void MonsterDisp() {
	if (g_enemybeat <= 1) {
		EnemyDisp();					// 弱い敵の描画
	}
	else {
		BossDisp[g_select_Stage]();					// ボスの表示
	}
}

// 弱い敵、ボスの動き
void MonsterMove() {
	if (g_enemybeat <= ENEMY_BEAT_MAX[g_select_Stage]) {
		EnemyMove();					// 弱い敵の動き
	}
	else {
		BossMove[g_select_Stage]();					// ボスの動き
	}
}

// 弱い敵の描画
void EnemyDisp() {

	
	// 敵を出現させる準備
	if (++g_coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
						g_enemy[i].walk.flg = TRUE;
						g_coolTime = 0;
						break;
						//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					g_coolTime = 0;
					break;
				}
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime   = 0;

		if(g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y, 
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//空中の敵描画
			DrawRotaGraph2(g_enemy[i].fly.x, g_enemy[i].fly.y, 
				0, 0, 0.2, 0.0, g_pic.enemy_fly[g_enemy[i].fly.anime], TRUE);
			//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 敵撃破時のアニメーション 
	EnemyEvaporation();
}

// 弱い敵の動き
void EnemyMove() {
	// 敵がいないときボスの動きを起動

	for (int i = 0; i < ENEMY_MAX; i++) {		//地上の敵の動き
		if (g_enemy[i].walk.flg == TRUE) {
			g_enemy[i].walk.x -= g_speedLevel+3;
			//g_enemy[i].walk.y = GROUND;
		}

		if (g_enemy[i].walk.x+ENEMY_WIDTH < 0) {
			/*for (int j = 0; j < walkEnemy_pop - 1; j++) {
				g_enemy[i + j].walk = g_enemy[i + j + 1].walk;
			}
			walkEnemy_pop -= 1;*/

			//g_enemy[i].walk.flg = FALSE;

			g_enemy[i].walk.WalkInit();
		}

		//if (g_button.circleButton == true) g_enemy[i].walk.Init();
	}
	for (int i = 0; i < ENEMY_MAX; i++) {		//空中の敵の動き
		if (g_enemy[i].fly.flg == TRUE) {
			g_enemy[i].fly.x -= g_speedLevel+3;
			g_enemy[i].fly.y = GROUND - 200;
		}

		if (g_enemy[i].fly.x + (574 * 0.2) < 0) {

			g_enemy[i].fly.FlyInit();
		}

	}
}

// 敵撃破時のアニメーション
void EnemyEvaporation(){
	const int animationMax = 5;
	// 0番目は水しぶきのアニメーション,1番目は蒸発のアニメーション
	static int anime[ENEMY_MAX][2] = { { 0, 0},	
										{ 0, 0},
										{ 0, 0},
										{ 0, 0},
										{ 0, 0} };
	static int time[ENEMY_MAX]  = { 60, 60, 60, 60, 60 };
	static float moveX[ENEMY_MAX] = { 0, 0, 0, 0, 0 },
				moveY[ENEMY_MAX] = { 0, 0, 0, 0, 0 };
	static int cntFlg[ENEMY_MAX] = { FALSE, FALSE, FALSE, FALSE, FALSE };

	// 空いてる変数に移動
	for (int i = 0; i < ENEMY_MAX - 2; i++) {
		for (int j = i; j < ENEMY_MAX - 1; j++) {
			if (g_enemyBuffer[j].flg == FALSE
				&& g_enemyBuffer[j].flg != g_enemyBuffer[j + 1].flg) {
				g_enemyBuffer[j].flg = TRUE;
				g_enemyBuffer[j].x = g_enemyBuffer[j + 1].x;
				g_enemyBuffer[j].y = g_enemyBuffer[j + 1].y;
				g_enemyBuffer[j + 1].flg = FALSE;
			}
		}
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		for(int j=0;j<ENEMY_MAX;j++){

			/*if (cntFlg[i] == FALSE
				&& g_enemyBuffer[i].flg == TRUE) {
				cntFlg[i] = TRUE;
			}*/

			// アニメーション
			if (g_enemyBuffer[i].flg == TRUE){
				if (anime[i][0] < animationMax) {
					if (time[i]++ % 24 == 23)anime[i][0]++;
				}
				else if (anime[i][1] < animationMax) {
					if (time[i]++ % 36 == 35)anime[i][1]++;
				}
			}

			// アニメーション終了時の初期化処理
			/*if (anime[i] >= animationMax
				&& g_enemyBuffer[i].flg == TRUE) {
				anime[i] = 0;
				g_enemyBuffer[i].flg = FALSE;
				cntFlg[i] = FALSE;
			}*/

			// フラグが 真の時アニメーションを表示
			if (g_enemyBuffer[i].flg == TRUE){
				if (anime[i][0] < animationMax) {
					moveX[i] -= g_speedLevel / 5;
					DrawRotaGraph(g_enemyBuffer[i].x + moveX[i], g_enemyBuffer[i].y,
						3.0f, /*DX_PI_F / 180 * 335*/0.0, g_pic.enemySplashes[anime[i][0]], TRUE, FALSE);
				}
				else if (anime[i][1] < animationMax) {
					moveX[i] -= g_speedLevel / 5;
					moveY[i] -= g_speedLevel / 10;
					DrawRotaGraph(g_enemyBuffer[i].x + 150 + moveX[i], g_enemyBuffer[i].y - 70 + moveY[i],
						1.0f, 0.0, g_pic.enemyVapour[anime[i][1]], TRUE, FALSE);
				}
			}
		}

	}

	// アニメーション終了時の初期化処理
	for (int i = 0; i < ENEMY_MAX; i++) {
		if (anime[i][1] >= animationMax
			&& g_enemyBuffer[i].flg == TRUE) {
			anime[i][0] = 0;
			anime[i][1] = 0;
			moveX[i] = 0;
			moveY[i] = 0;
			g_enemyBuffer[i].flg = FALSE;
			cntFlg[i] = FALSE;
			g_enemybeat++;			// エネミーを倒した数をカウント
		}
	}
}

// 弱い敵の初期化
void EnemyInit() {
	for (int i = 0; i < 3; i++) {
		g_enemy[i].walk.WalkInit();
		g_enemy[i].fly.FlyInit();
	}

	for (int i = 0; i < ENEMY_MAX; i++) {
		g_enemyBuffer[i].BufferInit();
	}
	
	g_coolTime = 0;
}