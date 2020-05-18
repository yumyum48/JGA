#include "DxLib.h"
#include "Struct.h"
#include "GamePlay.h"
#include "Picture.h"
#include "Controler.h"
#include "enemy.h"
#include "Boss.h"
#include "Select.h"

/************************************************************
// ã‚¢“G‚Ì•`‰æStage1
************************************************************/
void EnemyDisp_stage1() {
	static  int coolTime = 0;

	// “G‚ğoŒ»‚³‚¹‚é€”õ
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//’nã‚Ì“G
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

	// ã‚¢“G‚Ì•\¦
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// G‹›“G‚½‚¿‚ÌƒAƒjƒ[ƒVƒ‡ƒ“
		if (time++ % 8 == 0) {
			g_enemy[i].walk.anime++;
			g_enemy[i].fly.anime++;
		}

		// ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìƒ‹[ƒv
		if (g_enemy[i].walk.anime > animation_Max)g_enemy[i].walk.anime = 0;
		

		if (g_enemy[i].walk.flg == TRUE)		//’nã‚Ì“G•`‰æ
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// “GŒ‚”j‚ÌƒAƒjƒ[ƒVƒ‡ƒ“ 
	EnemyEvaporation();
}
/************************************************************
// ã‚¢“G‚Ì•`‰æStage1
************************************************************/
void EnemyDisp_stage2() {

	static  int coolTime = 0;
	// “G‚ğoŒ»‚³‚¹‚é€”õ
	if (++coolTime > 10) {
		if (GetRand(80) == 1) {		//’nã‚Ì“G
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].walk.flg == FALSE) {
					g_enemy[i].walk.flg = TRUE;
					coolTime = 0;
					break;
					//walkEnemy_pop += 1;
				}
			}
		}
		if (GetRand(150) == 1) {		//‹ó’†‚Ì“G
			for (int i = 0; i < ENEMY_MAX; i++) {
				if (g_enemy[i].fly.flg == FALSE) {
					g_enemy[i].fly.flg = TRUE;
					coolTime = 0;
					break;
				}
			}
		}
	}

	// ã‚¢“G‚Ì•\¦
	for (int i = 0; i < ENEMY_MAX; i++) {
		const int animation_Max = 3;
		static int time = 0;

		// G‹›“G‚½‚¿‚ÌƒAƒjƒ[ƒVƒ‡ƒ“
		if (time++ % 8 == 0) {
			g_enemy[i].walk.anime++;
			g_enemy[i].fly.anime++;
		}

		// ƒAƒjƒ[ƒVƒ‡ƒ“‚Ìƒ‹[ƒv
		if (g_enemy[i].walk.anime > animation_Max)g_enemy[i].walk.anime = 0;
		if (g_enemy[i].fly.anime > animation_Max)g_enemy[i].fly.anime = 0;

		if (g_enemy[i].walk.flg == TRUE)		//’nã‚Ì“G•`‰æ
			DrawRotaGraph2(g_enemy[i].walk.x, g_enemy[i].walk.y,
				0, 0, 1.0, 0.0, g_pic.enemy_walk[g_enemy[i].walk.anime], TRUE);
		if (g_enemy[i].fly.flg == TRUE)		//‹ó’†‚Ì“G•`‰æ
			DrawRotaGraph2(g_enemy[i].fly.x, g_enemy[i].fly.y,
				0, 0, 0.2, 0.0, g_pic.enemy_fly[g_enemy[i].fly.anime], TRUE);
		//DrawRotaGraph(g_enemy[i].fly.x, g_enemy[i].fly.y, 1.0f, 0.0, g_pic.flyEnemy[0], TRUE, FALSE);
	}

	// “GŒ‚”j‚ÌƒAƒjƒ[ƒVƒ‡ƒ“ 
	EnemyEvaporation();
}
void EnemyDisp_stage3() {

}
void EnemyDisp_stage4() {

}
void EnemyDisp_stage5() {

}
void EnemyDisp_stage6() {

}
void EnemyDisp_stage7() {

}
void EnemyDisp_stage8() {

}
