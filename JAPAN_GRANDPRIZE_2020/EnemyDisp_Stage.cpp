#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"

/************************************************************
// 弱い敵の描画Stage1
************************************************************/
void EnemyDisp_stage1() {
	static  int coolTime = 0;

	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
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
		

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 敵撃破時のアニメーション 
	EnemyEvaporation();
}
/************************************************************
// 弱い敵の描画Stage2
************************************************************/
void EnemyDisp_stage2() {
	static  int coolTime = 0;

	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
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


		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// 敵撃破時のアニメーション 
	EnemyEvaporation();
}
/************************************************************
// 弱い敵の描画Stage3
************************************************************/
void EnemyDisp_stage3() {
	static  int coolTime = 0;
	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
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
void EnemyDisp_stage4() {
	static  int coolTime = 0;
	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
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
void EnemyDisp_stage5() {
	static  int coolTime = 0;
	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
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
void EnemyDisp_stage6() {
	static  int coolTime = 0;
	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
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
void EnemyDisp_stage7() {
	static  int coolTime = 0;
	// 敵を出現させる準備
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//地上の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//空中の敵
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
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
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//地上の敵描画
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
void EnemyDisp_stage8() {

}
